#pragma once

#include <QtCore/QStringList>


#include "engine.h"
#include "utils.h"
#include "dbmanager.h"

class Core {
public:
    Core();

    ~Core();

    QStringList getHashes(const QString &filePath);

    void generateHashes(const QString &filePath);

    void folderScanner(const QString &directoryPath);

    void lookUp(const QString &inputHash);

    void scanFile(const QString &filePath);

private:
    Engine *engine;
    Utils *utils;
    DBManager *dbManager;
};


