#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include "Config.h"

Logger::Logger(const QString& sensorName, QObject* parent)
    : QObject(parent)
{
    // Генеруємо унікальне ім'я файлу для кожного сенсора
    logFileName = generateLogFileName(sensorName);
}

QString Logger::generateLogFileName(const QString& sensorName) const
{
    return QString("%1_%2.txt").arg(sensorName).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss"));
}

void Logger::writeData(const SensorMetric& aSensorMetric)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString logMessage = QString("%1 | name=%2 | value=%3").arg(timestamp, aSensorMetric.name, QString::number(aSensorMetric.value));

    qDebug() << logMessage.toStdString().c_str();

    QFile file(logFileName);  // Використовуємо унікальне ім'я файлу для кожного сенсора
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << logMessage << "\n";
        file.close();
    }
}
