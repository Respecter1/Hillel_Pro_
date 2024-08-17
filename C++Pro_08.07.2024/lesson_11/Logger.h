#pragma once

#include <QObject>
#include <QString>
#include "SensorMetric.h"
class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(const QString& sensorName, QObject* parent = nullptr);

    void writeData(const SensorMetric& aSensorMetric);
    void clearLogs();  // Оголошуємо метод для очищення логів

private:
    QString logFileName;

    QString generateLogFileName(const QString& sensorName) const;
};
