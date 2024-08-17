#include "Analyzer.h"
#include <QDebug>
#include <algorithm>
#include "Config.h"

Analyzer::Analyzer(QObject* parent)
    : QObject(parent)
{
}

void Analyzer::analyzeData(const SensorMetric& aSensorMetric)
{
    sensorData[aSensorMetric.name].push_back(aSensorMetric.value);
    allValues.push_back(aSensorMetric.value);

    if (allValues.size() > Config::MAX_RECORDS) {
        allValues.remove(0);
    }
    if (sensorData[aSensorMetric.name].size() > Config::MAX_RECORDS) {
        sensorData[aSensorMetric.name].remove(0);
    }
}

void Analyzer::printStats(const QString& title, const QVector<int>& values) const
{
    if (values.isEmpty()) {
        qDebug() << title.toStdString() << ": No data available";
        return;
    }

    int maxVal = *std::max_element(values.begin(), values.end());
    int minVal = *std::min_element(values.begin(), values.end());
    double average = std::accumulate(values.begin(), values.end(), 0.0) / values.size();

    QVector<int> sortedValues = values;
    std::sort(sortedValues.begin(), sortedValues.end());
    int median = sortedValues[sortedValues.size() / 2];

    qDebug() << title.toStdString();
    qDebug() << "  Max: " << maxVal;
    qDebug() << "  Min: " << minVal;
    qDebug() << "  Average: " << average;
    qDebug() << "  Median: " << median;
}

void Analyzer::reportPrint() const
{
    printStats("Overall Stats", allValues);
}

void Analyzer::reset()
{
    // Очищуємо всі зібрані дані
    sensorData.clear();
    allValues.clear();
}
