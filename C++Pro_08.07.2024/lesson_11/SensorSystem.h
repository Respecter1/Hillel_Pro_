#pragma once

#include <vector>
#include <memory>
#include "Sensor.h"
#include "Logger.h"
#include "Analyzer.h"

class SensorSystem : public QObject {
    Q_OBJECT
public:
    void initialize();
    void run();
private:
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::unique_ptr<Logger> logger;
    std::unique_ptr<Analyzer> analyzer;
};
