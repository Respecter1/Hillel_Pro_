#include "Sensor.h"

Sensor::Sensor(const QString& sensorName, QObject* parent)
    : QObject(parent), name(sensorName)
{ }

void Sensor::newData(int value)
{
    SensorMetric metric;
    metric.name = name;
    metric.value = value;
    emit dataReady(metric);
}
