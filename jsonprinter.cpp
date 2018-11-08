#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <iostream>
#include <QtCore/QFileInfo>
#include "jsonprinter.h"

JsonPrinter::JsonPrinter() {
	jsonObject = new QJsonObject();
    jsonArray = new QJsonArray();
}

JsonPrinter::~JsonPrinter() {
	delete jsonObject;
	delete jsonArray;
}

void JsonPrinter::addScanResult(const QString &filename, int result, const QString &description) {
	QFile file(filename);
	QFileInfo fileInfo(file.fileName());

	auto *newResult = new QJsonObject;

	newResult->insert("filename", fileInfo.fileName());
	newResult->insert("verdict", result);
	newResult->insert("description", description);

	jsonArray->push_back(*newResult);
}

void JsonPrinter::printResult() {
    jsonObject->insert("scan_result", *jsonArray);
	std::cout << QJsonDocument(*jsonObject).toJson().toStdString();
}

void JsonPrinter::addLookupResult(const QString &hash, int result, const QString &description,
								  const QStringList &hashes) {
	QJsonObject hashesObject;

	hashesObject.insert("md5", hashes.at(0));
	hashesObject.insert("sha1", hashes.at(1));
	hashesObject.insert("sha256", hashes.at(2));

	jsonObject->insert("search", hash);
	jsonObject->insert("verdict", result);
	jsonObject->insert("description", description);

	jsonObject->insert("hashes", hashesObject);
}

void JsonPrinter::printHashes(const QStringList &hashes) {
	QJsonObject jsonHash = QJsonObject();
	jsonHash.insert("MD5", hashes.at(0));
	jsonHash.insert("SHA1:", hashes.at(1));
	jsonHash.insert("SHA256", hashes.at(2));

	QJsonDocument hashDocument(jsonHash);

	std::cout << hashDocument.toJson().toStdString();
}



