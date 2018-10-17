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
    QJsonObject jsonHash = QJsonObject();

    if (inputHash.isEmpty()) {
        return 1;
    }

    if (dbManager->findHashInDB(inputHash)) {
        jsonHash.insert(inputHash, "Blocked");
    } else {
        jsonHash.insert(inputHash, "No threat detected");
    }

    QJsonDocument jsonDocument(jsonHash);

    std::cout << jsonDocument.toJson().toStdString();

    return 0;
}

int Core::scanFile(const QString &filepath) {
    QStringList hashes = engine->hashFile(filepath);
    QJsonObject jsonHash = QJsonObject();

    if (hashes.isEmpty()) {
        return 1;
    }

    if (dbManager->findHashesInDB(hashes)) {
        jsonHash.insert(filepath, "Blocked");
    } else {
        jsonHash.insert(filepath, "No threat detected");
    }

    QJsonDocument jsonDocument(jsonHash);

    std::cout << jsonDocument.toJson().toStdString();

    return 0;
}


