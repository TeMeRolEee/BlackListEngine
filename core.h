#pragma once

#include <QtCore/QStringList>


#include "engine.h"
#include "utils.h"
#include "dbmanager.h"

class Core {
public:
    Core();

    ~Core();

    int generateHashes(const QString &filePath);

    int folderScanner(const QString &directoryPath);

    int lookUp(const QString &inputHash);

    int scanFile(const QString &filePath);

private:
    Engine *engine;
    Utils *utils;
    DBManager *dbManager;
};


