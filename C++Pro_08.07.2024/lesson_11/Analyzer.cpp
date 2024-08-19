#include "Analyzer.h"
#include <QDebug>
#include <algorithm>
#include "Config.h"

Analyzer::Analyzer(QObject* parent)
    : QObject(parent)
{
}

void Analyzer::analyzeData(const SensorMetric& aSensorMetric) {
    sensorData[aSensorMetric.name].push_back(aSensorMetric.value);
    allValues.push_back(aSensorMetric.value);

    if (allValues.size() > Config::MAX_RECORDS) {
        allValues.removeAt(0);
    }
    if (sensorData[aSensorMetric.name].size() > Config::MAX_RECORDS) {
        sensorData[aSensorMetric.name].removeAt(0);
    }
}

void Analyzer::reportPrint() const {
    if (allValues.isEmpty()) {
        qDebug() << "No data available for statistics.";
        return;
    }

    int maxVal = *std::max_element(allValues.begin(), allValues.end());
    int minVal = *std::min_element(allValues.begin(), allValues.end());
    double average = std::accumulate(allValues.begin(), allValues.end(), 0.0) / allValues.size();

    QList<int> sortedValues = allValues;
    std::sort(sortedValues.begin(), sortedValues.end());
    int median = sortedValues[sortedValues.size() / 2];

    qDebug() << "Overall Stats";
    qDebug() << "  Max:" << maxVal;
    qDebug() << "  Min:" << minVal;
    qDebug() << "  Average:" << average;
    qDebug() << "  Median:" << median;
}

