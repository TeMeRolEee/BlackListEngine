#include <iostream>

#include <QtCore/QDirIterator>
#include <QtCore/QVector>
#include <QtCore/QFileInfo>

#include "core.h"
#include "jsonprinter.h"

Core::Core() {
    engine = new Engine;
    utils = new Utils;
    QString dbPath;
    dbPath.append(QDir::currentPath()).append("/hashes.db");
    dbManager = new DBManager(dbPath);
}

Core::~Core() {
    delete engine;
    delete utils;
    delete dbManager;
}

int Core::generateHashes(const QString &filePath) {
    QStringList hashes = engine->hashFile(filePath);
    if (!hashes.isEmpty()) {
        utils->printHashes(hashes);
        return 0;
    }
    return 1;
}

int Core::folderScanner(const QString &directoryPath) {
    QDirIterator directoryIterator(directoryPath);
    QMap<QString, QStringList> hashesArray;

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

    for (const auto &fileHashes : hashesArray) {
        if (!fileHashes.isEmpty() && dbManager->findHashesInDB(fileHashes)) {
            jsonHash.insert(hashesArray.key(fileHashes), "Blocked");
        } else {
            jsonHash.insert(hashesArray.key(fileHashes), "No threat detected");
        }
    }

    QJsonDocument jsonDocument(jsonHash);

    std::cout << jsonDocument.toJson().toStdString();

    return 0;
}

int Core::lookUp(const QString &inputHash) {
    auto *printer = new JsonPrinter();

    if (inputHash.isEmpty()) {
        return 1;
    }

    if (dbManager->findHashInDB(inputHash)) {

        QStringList tempList = dbManager->getHashes(inputHash);
        printer->addResultLookup(inputHash, 1, "Blocked", tempList);
    } else {
        QStringList tempList;
        tempList.push_back("");
        tempList.push_back("");
        tempList.push_back("");

        printer->addResultLookup(inputHash, 0, "No threat detected", tempList);
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
        printer->addResultScan(filepath, 1, "Blocked");
    } else {
        printer->addResultScan(filepath, 0, "No threat detected");
    }

    printer->printResult();

    delete printer;

    return 0;
}


