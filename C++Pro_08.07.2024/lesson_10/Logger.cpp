#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include "Config.h"

Logger::Logger(QObject* parent)
    : QObject(parent)
{
    // Генеруємо ім'я файлу один раз під час створення Logger
    logFileName = generateLogFileName();
}

QString Logger::generateLogFileName() const
{
    return QString(Config::LOG_FILE_NAME_FORMAT).arg(QDateTime::currentDateTime().toString(Config::DATE_TIME_FORMAT));
}

void Logger::writeData(const SensorMetric& aSensorMetric)
{
    QString timestamp = QDateTime::currentDateTime().toString(Config::DATE_TIME_FORMAT);
    QString logMessage = QString("%1 | name=%2 | value=%3").arg(timestamp, aSensorMetric.name, QString::number(aSensorMetric.value));

    qDebug() << logMessage.toStdString().c_str();

    QFile file(logFileName);  // Використовуємо заздалегідь збережене ім'я файлу
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << logMessage << "\n";
        file.close();
    }
}
