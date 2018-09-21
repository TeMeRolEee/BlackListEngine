#include <QtCore/QCryptographicHash>
#include <QtCore/QTextStream>
#include <QtCore/QFile>

#include <QDebug>

#include "engine.h"

QStringList Engine::hashFile(const QString &filePath) {
    QStringList qStringList;
    QFile qFile(filePath);

    if (qFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QCryptographicHash md5Hash(QCryptographicHash::Algorithm::Md5);
        md5Hash.addData(qFile.readAll());

        QCryptographicHash sha1Hash(QCryptographicHash::Algorithm::Sha1);
        sha1Hash.addData(qFile.readAll());

        QCryptographicHash sha256Hash(QCryptographicHash::Algorithm::Sha256);
        sha256Hash.addData(qFile.readAll());

        qFile.close();

        qStringList.append(md5Hash.result().toHex());
        qStringList.append(sha1Hash.result().toHex());
        qStringList.append(sha256Hash.result().toHex());

        return qStringList;
    }
    return QStringList();
}
