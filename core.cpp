#include <iostream>

#include <QtCore/QDirIterator>
#include <QtCore/QVector>
#include <QtCore/QFileInfo>

#include "core.h"

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
            std::cout << "\t Filename: " << hashesArray.key(fileHashes).toStdString() << "\n" << "Result: Blocked" << std::endl;
        } else {
            std::cout << "\t Filename: " << hashesArray.key(fileHashes).toStdString() << "\n" << "Result: No threat detected" << std::endl;
        }
    }

    return 0;
}

int Core::lookUp(const QString &inputHash) {
    if (inputHash.isEmpty()) {
        return 1;
    }

    if (dbManager->findHashInDB(inputHash)) {
        std::cout << "Result: Blocked" << std::endl;
    } else {
        std::cout << "Result: No threat detected" << std::endl;
    }

    return 0;
}

int Core::scanFile(const QString &filepath) {
    QStringList hashes = engine->hashFile(filepath);

    if (hashes.isEmpty()) {
        return 1;
    }

    if (dbManager->findHashesInDB(hashes)) {
        std::cout << "Result: Blocked" << std::endl;
    } else {
        std::cout << "Result: No threat detected" << std::endl;
    }

    return 0;
}


