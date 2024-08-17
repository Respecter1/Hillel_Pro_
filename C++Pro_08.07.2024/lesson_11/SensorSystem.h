#pragma once

#include <vector>
#include <memory>
#include <QObject>
#include "Sensor.h"
#include "Logger.h"
#include "Analyzer.h"
#include <QTableWidget>
#include <QProgressBar>
#include <QString>

class SensorSystem : public QObject {
    Q_OBJECT
public:
    explicit SensorSystem(QTableWidget* resultTable, QProgressBar* progressBar, QObject* parent = nullptr);
    void initialize(int numSensors);
    void run();

private slots:
    void handleSensorData(const SensorMetric& aSensorMetric);

private:
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::unique_ptr<Logger> logger;
    std::unique_ptr<Analyzer> analyzer;
    QTableWidget* resultTableWidget;
    QProgressBar* simulationProgressBar;
    int currentSensorIndex;
};
