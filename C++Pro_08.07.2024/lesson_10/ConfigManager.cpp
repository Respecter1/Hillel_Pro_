#include "ConfigManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

ConfigManager::ConfigManager() {
    // Можлива початкова ініціалізація
}

void ConfigManager::copyConfigFile(const QString &source, const QString &destination) {
    if (!QFile::exists(destination)) {
        if (QFile::copy(source, destination)) {
            qDebug() << "Config file copied to:" << destination;
        } else {
            qWarning() << "Failed to copy config file to:" << destination;
        }
    }
}

void ConfigManager::loadConfig(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open config file.");
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Error parsing JSON:" << error.errorString();
        return;
    }

    config = doc.object();
    qDebug() << "JSON content:" << config;
}

void ConfigManager::processCommandLine(QCommandLineParser &parser, QCoreApplication &app) {
    parser.setApplicationDescription("My Qt Application");
    parser.addHelpOption();

    QCommandLineOption configFileOption(QStringList() << "c" << "config", "Configuration file", "file");
    parser.addOption(configFileOption);
    QCommandLineOption logLevelOption(QStringList() << "l" << "log-level", "Logging level", "level");
    parser.addOption(logLevelOption);

    parser.process(app);

    QString configFilePath = parser.value(configFileOption).isEmpty() ? "config.json" : parser.value(configFileOption);

    // Перевірка наявності файлу і копіювання з ресурсів, якщо відсутній
    if (!QFile::exists(configFilePath)) {
        copyConfigFile(":/config.json", configFilePath);
    }

    loadConfig(configFilePath);

    logLevel = parser.value(logLevelOption);
    if (!logLevel.isEmpty()) {
        qDebug() << "Overriding logging level to:" << logLevel;
    }
}

QString ConfigManager::getLogLevel() const {
    return logLevel.isEmpty() ? config["loggingLevel"].toString() : logLevel;
}
