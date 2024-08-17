#pragma once

#include <QString>
#include <QMetaType>

struct SensorMetric
{
    QString name;
    int value;

};

Q_DECLARE_METATYPE(SensorMetric)
