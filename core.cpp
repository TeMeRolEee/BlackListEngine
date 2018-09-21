#include <iostream>

#include <QtCore/QDirIterator>
#include <QtCore/QVector>

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

QStringList Core::getHashes(const QString &filePath) {

    QStringList hashes = engine->hashFile(filePath);

    if (!hashes.isEmpty()) {
        return hashes;
    }

    return QStringList();
}

void Core::generateHashes(const QString &filePath) {
    QStringList hashes = getHashes(filePath);
    utils->printHashes(hashes);
}

void Core::folderScanner(const QString &directoryPath) {
    QDirIterator directoryIterator(directoryPath);
    QVector<QStringList> hashes;

    while (directoryIterator.hasNext()) {
        hashes.append(getHashes(directoryIterator.next()));
    }

    for (auto hash : hashes) {
        dbManager->findHashInDB(hash);
    }
}

void Core::lookUp(const QString &inputHash) {
    if (dbManager->findHashInDB(inputHash)) {
        std::cout << "Result: Blocked" << std::endl;
    } else {
        std::cout << "Result: No threat detected" << std::endl;
    }
}

void Core::scanFile(const QString &filepath) {
    QStringList hashes = getHashes(filepath);

    if (dbManager->findHashInDB(hashes)) {
        std::cout << "Result: Blocked" << std::endl;
    } else {
        std::cout << "Result: No threat detected" << std::endl;
    }
}


