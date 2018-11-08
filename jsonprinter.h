#pragma once

#include <QtCore/QString>
#include <QtCore/QJsonObject>

class JsonPrinter {
public:
	JsonPrinter();

	~JsonPrinter();

	void addScanResult(const QString &filename, int result, const QString &description);

	void addLookupResult(const QString &hash, int result, const QString &description, const QStringList &hashes);

    void printHashes(const QStringList &hashes);

	void printResult();

private:
	QJsonObject *jsonObject;
    QJsonArray *jsonArray;
};


