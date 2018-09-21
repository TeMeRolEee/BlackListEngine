#include <iostream>
#include "utils.h"

void Utils::printHashes(const QStringList &hashes) {
    std::cout << "MD5: " << hashes.at(0).toStdString() << std::endl
              << "SHA1: " << hashes.at(1).toStdString() << std::endl
              << "SHA256: " << hashes.at(2).toStdString() << std::endl;
}
