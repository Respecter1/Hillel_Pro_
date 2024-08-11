#pragma once

#include <QObject>
#include <QVector>
#include "SensorMetric.h"
#include "Config.h"


class Analyzer : public QObject {
    Q_OBJECT
public:
    Analyzer(QObject* parent = nullptr);
    void reportPrint() const;

public slots:
    void analyzeData(const SensorMetric& aSensorMetric);

private:
    QVector<int> values;
    int maxRecords = MAX_RECORDS;
};
