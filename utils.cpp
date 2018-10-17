#include <iostream>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include "utils.h"

void Utils::printHashes(const QStringList &hashes) {
    QJsonObject jsonHash = QJsonObject();
    jsonHash.insert("MD5", hashes.at(0));
    jsonHash.insert("SHA1:", hashes.at(1));
    jsonHash.insert("SHA256", hashes.at(2));

    QJsonDocument hashDocument(jsonHash);

    std::cout << hashDocument.toJson().toStdString();
}
