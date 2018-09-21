#include "iohandler.h"

#include <QtCore/QFile>

#include <QDebug>

QString IOHandler::readFile(const QString &filePath) {
    QString input;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Couldn't open the file";
    } else {
        QTextStream out(&file);
        out << input;
    }

    return QString();
}


