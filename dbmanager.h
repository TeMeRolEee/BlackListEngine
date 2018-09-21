#pragma once
#include <QtSql>

class DBManager {
public:
    DBManager(const QString &path);
    bool addHash(const QString)

private:
    QSqlDatabase qSqlDatabase;
};

