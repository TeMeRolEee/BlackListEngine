#pragma once

#include <QtCore/QStringList>

#include "engine.h"
#include "utils.h"

class Core {
public:
    ~Core();
    QStringList getHashes(const QString &filePath);
    void generateHashes(const QString &filePath);
    void folderScanner(const QString &directoryPath);
    void lookUp(const QString &inputHash);

private:
    Engine *engine;
    Utils *utils;
};


