#include <QtCore/QCryptographicHash>
#include <QtCore/QTextStream>
#include <QtCore/QFile>

#include <QDebug>
#include <QtCore/QFileInfo>

#include "engine.h"

QStringList Engine::hashFile(const QString &filePath) {
    QStringList hashes;
    QFile qFile(filePath);

    if (qFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray fileContent = qFile.readAll();
        qFile.close();

        QCryptographicHash md5Hash(QCryptographicHash::Algorithm::Md5);
        md5Hash.addData(fileContent);

        QCryptographicHash sha1Hash(QCryptographicHash::Algorithm::Sha1);
        sha1Hash.addData(fileContent);

        QCryptographicHash sha256Hash(QCryptographicHash::Algorithm::Sha256);
        sha256Hash.addData(fileContent);

        hashes.append(md5Hash.result().toHex());
        hashes.append(sha1Hash.result().toHex());
        hashes.append(sha256Hash.result().toHex());

        return hashes;
    }

    qDebug() << "Error, couldn't hash the file, probably not exists or don't have permission to read it!";

    return QStringList();
}
