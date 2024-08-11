#include "Analyzer.h"
#include <algorithm>
#include <iostream>
#include "Config.h"

Analyzer::Analyzer(QObject* parent)
    : QObject(parent)
{ }

void Analyzer::analyzeData(const SensorMetric& aSensorMetric)
{
    if (values.size() >= maxRecords)
    {
        values.remove(0);
    }
    values.push_back(aSensorMetric.value);
}

void Analyzer::reportPrint() const
{
    if (values.isEmpty())
    {
        std::cout << "No data available" << std::endl;
        return;
    }

    int maxVal = *std::max_element(values.begin(), values.end());
    int minVal = *std::min_element(values.begin(), values.end());
    double average = std::accumulate(values.begin(), values.end(), 0.0) / values.size();

    QVector<int> sortedValues = values;
    std::sort(sortedValues.begin(), sortedValues.end());
    int median = sortedValues[sortedValues.size() / 2];

    std::cout << "Max: " << maxVal << std::endl;
    std::cout << "Min: " << minVal << std::endl;
    std::cout << "Average: " << average << std::endl;
    std::cout << "Median: " << median << std::endl;
}
