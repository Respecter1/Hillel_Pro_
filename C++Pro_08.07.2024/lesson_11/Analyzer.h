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

public slots:
    void analyzeData(const SensorMetric& aSensorMetric);

private:
    void printStats(const QString& title, const QVector<int>& values) const;

    QMap<QString, QVector<int>> sensorData;
    QVector<int> allValues;
};
