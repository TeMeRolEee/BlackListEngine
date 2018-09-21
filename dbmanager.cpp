//
// Created by temerole on 2018.09.21..
//

#include "dbmanager.h"

DBManager::DBManager(const QString &path) {
    qSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    qSqlDatabase.setDatabaseName(path);

    if (!qSqlDatabase.open()) {
        qDebug() << "Error: no connection with the database";
    } else {
        qDebug() << "Database: connection ok";
    }
}
