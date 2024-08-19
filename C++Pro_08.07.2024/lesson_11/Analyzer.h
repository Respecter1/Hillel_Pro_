#pragma once

#include <QObject>
#include <QMap>
#include <QList>
#include "SensorMetric.h"

class Analyzer : public QObject
{
    Q_OBJECT
public:
    explicit Analyzer(QObject* parent = nullptr);
    void reportPrint() const;

public slots:
    void analyzeData(const SensorMetric& aSensorMetric);

private:
    void printStats(const QString& title, const QList<int>& values) const;

    QMap<QString, QList<int>> sensorData;
    QList<int> allValues;
};
