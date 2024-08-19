#pragma once
#include <QListWidget>
#include <QTableWidget>
#include <QObject>
#include <QTableWidget>
#include <QProgressBar>
#include <vector>
#include <memory>
#include "Sensor.h"
#include "Logger.h"
#include "Analyzer.h"

class SensorSystem : public QObject {
    Q_OBJECT
public:
    SensorSystem(QObject* parent = nullptr);

    void addSensor(const QString& sensorName);
    void run(QTableWidget* tableWidget, QProgressBar* progressBar);
    void saveDataToFile(const QString& fileName);
    void removeSensorAndUpdateUI(int index, QListWidget* listWidget, QTableWidget* tableWidget);
    std::vector<std::unique_ptr<Sensor>>& getSensors();
private:
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::unique_ptr<Logger> logger;
    std::unique_ptr<Analyzer> analyzer;
};
