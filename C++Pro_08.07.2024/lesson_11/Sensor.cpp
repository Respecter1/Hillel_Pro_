#include "Sensor.h"

Sensor::Sensor(const QString& sensorName, QObject* parent)
    : QObject(parent), name(sensorName), currentValue(0)
{
}

void Sensor::newData(int value)
{
    currentValue = value;
    SensorMetric metric;
    metric.name = name;
    metric.value = currentValue;
    emit dataReady(metric);
}

SensorMetric Sensor::getMetric() const
{
    SensorMetric metric;
    metric.name = name;
    metric.value = currentValue;
    return metric;
}
