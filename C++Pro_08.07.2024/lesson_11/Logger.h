#pragma once

#include <QObject>
#include <QString>
#include "SensorMetric.h"

class Logger : public QObject
{
    Q_OBJECT
public:
    Logger(const QString& sensorName, QObject* parent = nullptr);

public slots:
    void writeData(const SensorMetric& aSensorMetric);

private:
    QString generateLogFileName(const QString& sensorName) const;

    // Змінна для збереження імені файлу
    QString logFileName;
};
