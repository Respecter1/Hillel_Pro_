#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include "Config.h"

Logger::Logger(QObject* parent)
    : QObject(parent)
{
    // Генерируем имя файла при создании Logger
    logFileName = generateLogFileName();
}

QString Logger::generateLogFileName() const {
    return QString(Config::LOG_FILE_NAME_FORMAT).arg(QDateTime::currentDateTime().toString(Config::DATE_TIME_FORMAT));
}

void Logger::writeData(const SensorMetric& aSensorMetric) {
    QString timestamp = QDateTime::currentDateTime().toString(Config::DATE_TIME_FORMAT);
    QString logMessage = QString("%1 | name=%2 | value=%3").arg(timestamp, aSensorMetric.name, QString::number(aSensorMetric.value));

    logData.push_back(logMessage);  // Сохраняем данные в памяти
    qDebug() << logMessage;  // Выводим в консоль для отладки
}

void Logger::saveToFile(const QString& fileName) const {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& logEntry : logData) {
            out << logEntry << "\n";
        }
        file.close();
        qDebug() << "Data saved to file: " << fileName;
    } else {
        qDebug() << "Failed to open file for writing: " << fileName;
    }
}

const std::vector<QString>& Logger::getLogData() const {
    return logData;
}
