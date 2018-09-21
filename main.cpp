#include <iostream>

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("En_Decoder");
    QCoreApplication::setApplicationVersion("0.9.5");

    QCommandLineParser parser;
    parser.setApplicationDescription("Encodes and decodes text via a given dictionary");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption helpOption(QStringList() << "h" << "help", "Writing out the help");
    parser.addOption(helpOption);

    QCommandLineOption scanOption(QStringList() << "s" << "scan",
                                  "Hashes the given file (MD5, SHA1, SHA256) and searches"
                                  "for the result in the database. If there is a match: Result:Blocked,"
                                  "otherwise Result: No threat detected.");

    QCommandLineOption lookupOption(QStringList() << "l" << "lookup",
                                    "Searches for results via the given hash (MD5, SHA1, SHA256) in the database. "
                                    "Same result as the scan mode.");

    QCommandLineOption generateOption(QStringList() << "g" << "generate",
                                      "Generates a hashes from the given file.\n"
                                      "MD5: <MD5_hash_of_file>\n"
                                      "SHA1: <SHA1_hash_of_file>\n"
                                      "SHA256: <SHA256_hash_of_file>");

    QCommandLineOption folderOption(QStringList() << "f" << "folder",
                                    "Iterates through the given folder non-recursively and scans them.");

    parser.process(app);

    parser.showHelp();
}