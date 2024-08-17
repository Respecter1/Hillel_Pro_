#pragma once

#include <QObject>
#include <QVector>
#include <QString>
#include <QMap>
#include "SensorMetric.h"
class Analyzer : public QObject
{
    Q_OBJECT
public:
    explicit Analyzer(QObject* parent = nullptr);
    void analyzeData(const SensorMetric& aSensorMetric);
    void reportPrint() const;

    // Додаємо метод для скидання даних
    void reset();

private:
    void printStats(const QString& title, const QVector<int>& values) const;

    QMap<QString, QVector<int>> sensorData;
    QVector<int> allValues;
};
