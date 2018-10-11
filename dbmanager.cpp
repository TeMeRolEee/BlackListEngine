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

bool DBManager::findHashesInDB(const QStringList &hashes) {
    QSqlQuery qSqlQuery;
    qSqlQuery.prepare(
            "SELECT MD5, SHA1, SHA256 FROM hashTable WHERE MD5 = (:MD5) OR SHA1 = (:SHA1) OR SHA256 = (:SHA256)");
    qSqlQuery.bindValue(":MD5", hashes.at(0));
    qSqlQuery.bindValue(":SHA1", hashes.at(1));
    qSqlQuery.bindValue(":SHA256", hashes.at(2));

    return qSqlQuery.exec() && qSqlQuery.next();
}

bool DBManager::findHashInDB(const QString &hash) {
    QSqlQuery qSqlQuery;

    qSqlQuery.prepare("SELECT * FROM hashTable WHERE MD5 = (:HASH) OR SHA1 = (:HASH) OR SHA256 = (:HASH)");
    qSqlQuery.bindValue(":HASH", hash);

    return qSqlQuery.exec() && qSqlQuery.next();
}
