#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>
#include <QJsonObject>
#include <QCommandLineParser>

class ConfigManager {
public:
    ConfigManager();
    void loadConfig(const QString &filePath);
    void processCommandLine(QCommandLineParser &parser, QCoreApplication &app);
    void copyConfigFile(const QString &source, const QString &destination);

    QString getLogLevel() const;
    // Інші методи для отримання налаштувань

private:
    QJsonObject config;
    QString logLevel;
};

#endif // CONFIGMANAGER_H
