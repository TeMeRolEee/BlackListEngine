#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <iostream>
#include <QtCore/QFileInfo>
#include "jsonprinter.h"

JsonPrinter::JsonPrinter() {
	jsonObject = new QJsonObject();
}

JsonPrinter::~JsonPrinter() {
	delete jsonObject;
}

void JsonPrinter::addResultScan(const QString &filename, int result, const QString &description) {
	QFile file(filename);
	QFileInfo fileInfo(file.fileName());

	QJsonArray resultArray;
	QJsonObject newResult;

	newResult.insert("filename", fileInfo.fileName());
	newResult.insert("verdict", result);
	newResult.insert("description", description);

	resultArray.push_back(newResult);

	jsonObject->insert("scan_result", resultArray);
}

void JsonPrinter::printResult() {
	std::cout << QJsonDocument(*jsonObject).toJson().toStdString();
}

void JsonPrinter::addResultLookup(const QString &hash, int result, const QString &description, const QStringList &hashes) {
	QJsonObject hashesObject;

	hashesObject.insert("md5", hashes.at(0));
	hashesObject.insert("sha1", hashes.at(1));
	hashesObject.insert("sha256", hashes.at(2));

	jsonObject->insert("search", hash);
	jsonObject->insert("verdict", result);
	jsonObject->insert("description", description);

	jsonObject->insert("hashes", hashesObject);
}



