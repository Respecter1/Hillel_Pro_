#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <iostream>
#include "Config.h"

Logger::Logger(QObject* parent)
    : QObject(parent)
{ }

QString Logger::generateLogFileName() const
{

    return QString(LOG_FILE_NAME_FORMAT).arg(QDateTime::currentDateTime().toString(DATE_TIME_FORMAT));
}

void Logger::writeData(const SensorMetric& aSensorMetric)
{
    QString timestamp = QDateTime::currentDateTime().toString(DATE_TIME_FORMAT);
    QString logMessage = QString("%1 | name=%2 | value=%3").arg(timestamp, aSensorMetric.name, QString::number(aSensorMetric.value));

    std::cout << logMessage.toStdString() << std::endl;

    QFile file(generateLogFileName());
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << logMessage << "\n";
        file.close();
    }
}
