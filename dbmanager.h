#pragma once
#include <QtSql>

class DBManager {
public:
    DBManager(const QString &path);
    bool findHashInDB(const QStringList &hashes);
    bool findHashInDB(const QString &hash);

private:
    QSqlDatabase qSqlDatabase;
};

