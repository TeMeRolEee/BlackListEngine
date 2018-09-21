#pragma once

#include <QtCore/QString>

class IOHandler {
public:
    QString readFile(const QString &filePath);
};

