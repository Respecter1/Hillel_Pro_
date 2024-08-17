#include "SensorSystem.h"
#include "Config.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QCoreApplication>


SensorSystem::SensorSystem(QTableWidget* resultTable, QProgressBar* progressBar, QObject* parent)
    : QObject(parent), resultTableWidget(resultTable), simulationProgressBar(progressBar), currentSensorIndex(0)
{
    analyzer = std::make_unique<Analyzer>();
}

void SensorSystem::initialize(int numSensors) {
    sensors.clear();
    currentSensorIndex = 0;

    analyzer->reset();

    sensors.reserve(numSensors);
    for (int i = 1; i <= numSensors; ++i) {
        auto sensor = std::make_unique<Sensor>(QString(Config::SENSOR_NAME_FORMAT).arg(i));
        auto logger = std::make_unique<Logger>(sensor->objectName());

        qDebug() << "Creating sensor:" << sensor->objectName();  // Діагностика при створенні сенсора

        sensors.push_back(std::move(sensor));

        QObject::connect(sensors.back().get(), &Sensor::dataReady, logger.get(), &Logger::writeData);
        QObject::connect(sensors.back().get(), &Sensor::dataReady, this, &SensorSystem::handleSensorData);
        QObject::connect(sensors.back().get(), &Sensor::dataReady, analyzer.get(), &Analyzer::analyzeData);

        qDebug() << "Connected sensor to logger and analyzer:" << sensors.back()->objectName();  // Діагностика після підключення сигналів
    }
}

void SensorSystem::run() {
    QTimer* timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [=]() {
        if (currentSensorIndex < sensors.size()) {
            qDebug() << "Generating new data for sensor:" << sensors[currentSensorIndex]->objectName();  // Діагностика перед генерацією даних
            sensors[currentSensorIndex]->newData(QRandomGenerator::global()->bounded(Config::SENSOR_MAX_VALUE));
            ++currentSensorIndex;
        }

        if (currentSensorIndex == sensors.size()) {
            qDebug() << "All sensors have completed. Generating report...";
            analyzer->reportPrint();
            timer->stop();
        }
    });

    simulationProgressBar->setRange(0, sensors.size());
    simulationProgressBar->setValue(0);

    resultTableWidget->setRowCount(sensors.size());
    resultTableWidget->setColumnCount(2); // Колонки: Sensor Name, Value
    resultTableWidget->setHorizontalHeaderLabels({"Sensor Name", "Value"});

    qDebug() << "Starting simulation timer...";  // Діагностика перед запуском таймера
    timer->start(Config::TIMER_INTERVAL_MS);
}

void SensorSystem::handleSensorData(const SensorMetric& aSensorMetric) {
    int row = aSensorMetric.name.mid(QString(Config::SENSOR_NAME_FORMAT).size() - 2).toInt() - 1;

    qDebug() << "Handling data for sensor:" << aSensorMetric.name << "Value:" << aSensorMetric.value;

    resultTableWidget->setItem(row, 0, new QTableWidgetItem(aSensorMetric.name));
    resultTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(aSensorMetric.value)));

    simulationProgressBar->setValue(row + 1);
}

