#include <iostream>

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>

#include <QDebug>
#include <memory>

#include "engine.h"
#include "core.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("BlackListEngine");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Hashes the given files or directory");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption helpOption(QStringList() << "h" << "help", "Writing out the help");
    parser.addOption(helpOption);

    QCommandLineOption scanOption(QStringList() << "s" << "scan",
                                  "Hashes the given file (MD5, SHA1, SHA256) and searches"
                                  "for the result in the database. If there is a match: Result:Blocked,"
                                  "otherwise Result: No threat detected.", "scan");
    parser.addOption(scanOption);

    QCommandLineOption lookupOption(QStringList() << "l" << "lookup",
                                    "Searches for results via the given hash (MD5, SHA1, SHA256) in the database. "
                                    "Same result as the scan mode.", "lookup");
    parser.addOption(lookupOption);

    QCommandLineOption generateOption(QStringList() << "g" << "generate",
                                      "Generates a hashes from the given file.\n"
                                      "MD5: <MD5_hash_of_file>\n"
                                      "SHA1: <SHA1_hash_of_file>\n"
                                      "SHA256: <SHA256_hash_of_file>", "generate");
    parser.addOption(generateOption);

    QCommandLineOption folderOption(QStringList() << "f" << "folder",
                                    "Iterates through the given folder non-recursively and scans them.", "folder");
    parser.addOption(folderOption);

    parser.process(app);

    auto core = std::make_unique<Core>();

    if (parser.isSet(scanOption)) {
        return core->scanFile(parser.value(scanOption));
    } else if (parser.isSet(lookupOption)) {
        return core->lookUp(parser.value(lookupOption));
    } else if (parser.isSet(generateOption)) {
        return core->generateHashes(parser.value(generateOption));
    } else if (parser.isSet(folderOption)) {
        return core->folderScanner(parser.value(folderOption));
    }

    parser.showHelp();
}