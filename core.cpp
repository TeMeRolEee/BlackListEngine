#include <iostream>

#include <QtCore/QDirIterator>
#include <QtCore/QVector>
#include <QtCore/QFileInfo>

#include "core.h"
#include "jsonprinter.h"

Core::Core() {
    engine = new Engine;
    QString dbPath;
    dbPath.append(QDir::currentPath()).append("/hashes.db");
    dbManager = new DBManager(dbPath);
}

Core::~Core() {
    delete engine;
    delete dbManager;
}

int Core::generateHashes(const QString &filePath) {
    QStringList hashes = engine->hashFile(filePath);
    if (!hashes.isEmpty()) {
        auto *printer = new JsonPrinter();
        printer->printHashes(hashes);
        return 0;
    }
    return 1;
}

int Core::folderScanner(const QString &directoryPath) {
    QDirIterator directoryIterator(directoryPath);
    QMap<QString, QStringList> hashesArray;

    auto *printer = new JsonPrinter();

    QJsonObject jsonHash = QJsonObject();

    if (!directoryIterator.hasNext()) {
        qDebug() << "No files in the directory to hash!";
        return 1;
    }

    while (directoryIterator.hasNext()) {
        directoryIterator.next();
        if (QFileInfo(directoryIterator.filePath()).isFile()){
            hashesArray.insert(directoryIterator.fileName(), engine->hashFile(directoryIterator.filePath()));
        }
    }

    for (const auto &fileHashes : hashesArray.keys()) {
        if (!fileHashes.isEmpty() && dbManager->findHashesInDB(hashesArray.value(fileHashes))) {
            printer->addScanResult(fileHashes, 1, "Blocked");
        } else {
            printer->addScanResult(fileHashes, 0, "No threat detected");
        }
    }

    printer->printResult();

    return 0;
}

int Core::lookUp(const QString &inputHash) {
    auto *printer = new JsonPrinter();

    if (inputHash.isEmpty()) {
        return 1;
    }

    if (dbManager->findHashInDB(inputHash)) {

        QStringList tempList = dbManager->getHashes(inputHash);
        printer->addLookupResult(inputHash, 1, "Blocked", tempList);
    } else {
        QStringList tempList;
        tempList.push_back("");
        tempList.push_back("");
        tempList.push_back("");

        printer->addLookupResult(inputHash, 0, "No threat detected", tempList);
    }

    printer->printResult();


    return 0;
}

int Core::scanFile(const QString &filepath) {
    QStringList hashes = engine->hashFile(filepath);

    auto *printer = new JsonPrinter();

    if (hashes.isEmpty()) {
        return 1;
    }

    if (dbManager->findHashesInDB(hashes)) {
        printer->addScanResult(filepath, 1, "Blocked");
    } else {
        printer->addScanResult(filepath, 0, "No threat detected");
    }

    printer->printResult();

    delete printer;

    return 0;
}


