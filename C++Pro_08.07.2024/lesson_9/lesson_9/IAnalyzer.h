#pragma once

#include "SensorMetric.h"

class IAnalyzer {
public:
    virtual ~IAnalyzer() = default;

    virtual void analyzeData(const SensorMetric& aSensorMetric) = 0;
    virtual void reportPrint() const = 0;
};
