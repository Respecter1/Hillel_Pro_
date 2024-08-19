#pragma once

#include <QObject>
#include "SensorMetric.h"

class Sensor : public QObject
{
    Q_OBJECT
public:
    Sensor(const QString& sensorName, QObject* parent = nullptr);

    void newData(int value);  // Новый метод для генерации данных
    SensorMetric getMetric() const;

signals:
    void dataReady(const SensorMetric& aSensorMetric);

private:
    QString name;
    int currentValue;
};
