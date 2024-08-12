#include "Analyzer.h"
#include <algorithm>
#include <iostream>
#include "Config.h"

Analyzer::Analyzer(QObject* parent)
    : QObject(parent) {}

void Analyzer::analyzeData(const SensorMetric& aSensorMetric) {
    sensorData[aSensorMetric.name].push_back(aSensorMetric.value);
    allValues.push_back(aSensorMetric.value);

    // Обмежуємо кількість записів
    if (allValues.size() > MAX_RECORDS) {
        allValues.remove(0);
    }
    if (sensorData[aSensorMetric.name].size() > MAX_RECORDS) {
        sensorData[aSensorMetric.name].remove(0);
    }
}

void Analyzer::printStats(const QString& title, const QVector<int>& values) const {
    if (values.isEmpty()) {
        std::cout << title.toStdString() << ": No data available" << std::endl;
        return;
    }

    int maxVal = *std::max_element(values.begin(), values.end());
    int minVal = *std::min_element(values.begin(), values.end());
    double average = std::accumulate(values.begin(), values.end(), 0.0) / values.size();

    QVector<int> sortedValues = values;
    std::sort(sortedValues.begin(), sortedValues.end());
    int median = sortedValues[sortedValues.size() / 2];

    std::cout << title.toStdString() << std::endl;
    std::cout << "  Max: " << maxVal << std::endl;
    std::cout << "  Min: " << minVal << std::endl;
    std::cout << "  Average: " << average << std::endl;
    std::cout << "  Median: " << median << std::endl;
}

void Analyzer::reportPrint() const
{
    printStats("Overall Stats", allValues);
}
