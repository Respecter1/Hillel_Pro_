#pragma once

#include <QObject>
#include <QVector>
#include <QMap>
#include <QString>
#include "SensorMetric.h"

class Analyzer : public QObject
{
    Q_OBJECT
public:
    Analyzer(QObject* parent = nullptr);

    void reportPrint() const;
    void printOverallStats() const;

public slots:
    void analyzeData(const SensorMetric& aSensorMetric);

private:
    void printSensorStats(const QString& sensorName, const QVector<int>& values) const;

    QMap<QString, QVector<int>> sensorData;
    QVector<int> allValues;
};
