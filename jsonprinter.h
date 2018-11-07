#pragma once

#include <QtCore/QString>
#include <QtCore/QJsonObject>

class JsonPrinter {
public:
	JsonPrinter();
	~JsonPrinter();
	void addResultScan(const QString &filename, int result, const QString &description);

	void addResultLookup(const QString &hash, int result, const QString &description, const QStringList &hashes);

	void printResult();

private:
	QJsonObject *jsonObject;
};


