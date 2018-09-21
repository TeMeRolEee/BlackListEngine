#include <iostream>

#include <QtCore/QDirIterator>
#include <QtCore/QVector>

#include "core.h"

Core::~Core() {
    delete engine;
    delete utils;
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
        if (!hash.isEmpty()) {
            utils->printHashes(hash);
        }
    }
}

void Core::lookUp(const QString &inputHash) {

}
