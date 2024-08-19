#include "SensorSystem.h"
#include "Config.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QCoreApplication>

SensorSystem::SensorSystem(QObject* parent)
    : QObject(parent)
{
    logger = std::make_unique<Logger>();
    analyzer = std::make_unique<Analyzer>();
}

void SensorSystem::addSensor(const QString& sensorName) {
    auto sensor = std::make_unique<Sensor>(sensorName);
    sensors.push_back(std::move(sensor));

    // Подключаем сенсоры к логгеру и анализатору
    QObject::connect(sensors.back().get(), &Sensor::dataReady, logger.get(), &Logger::writeData);
    QObject::connect(sensors.back().get(), &Sensor::dataReady, analyzer.get(), &Analyzer::analyzeData);
}

void SensorSystem::run(QTableWidget* tableWidget, QProgressBar* progressBar) {
    if (sensors.empty()) {
        qDebug() << "No sensors available to run.";
        return;
    }

    // Устанавливаем количество строк и колонок в таблице
    tableWidget->setRowCount(sensors.size());
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels({"Sensor Name", "Value"});

    progressBar->setRange(0, sensors.size());
    progressBar->setValue(0);

    QTimer* timer = new QTimer(this);
    int iteration = 0;

    connect(timer, &QTimer::timeout, this, [=]() mutable {

        if (iteration < sensors.size()) {
            int sensorValue = QRandomGenerator::global()->bounded(100);
            sensors[iteration]->newData(sensorValue);

            // Обновляем таблицу
            tableWidget->setItem(iteration, 0, new QTableWidgetItem(sensors[iteration]->getMetric().name));
            tableWidget->setItem(iteration, 1, new QTableWidgetItem(QString::number(sensorValue)));

            // Обновляем прогресс-бар
            progressBar->setValue(iteration + 1);

            ++iteration;
        }

        if (iteration == sensors.size()) {
            qDebug() << "Simulation complete.";
            analyzer->reportPrint();
            timer->stop();
        }

        QCoreApplication::processEvents();
    });

    qDebug() << "Starting timer.";
    timer->start(Config::TIMER_INTERVAL_MS);
}

void SensorSystem::saveDataToFile(const QString& fileName) {
    logger->saveToFile(fileName);
}

std::vector<std::unique_ptr<Sensor>>& SensorSystem::getSensors() {
    return sensors;
}


void SensorSystem::removeSensorAndUpdateUI(int index, QListWidget* listWidget, QTableWidget* tableWidget)
{
    if (index >= 0 && index < sensors.size()) {
        // Разрываем соединения сенсора с логгером и анализатором
        QObject::disconnect(sensors[index].get(), nullptr, logger.get(), nullptr);
        QObject::disconnect(sensors[index].get(), nullptr, analyzer.get(), nullptr);

        // Удаляем сенсор из списка сенсоров
        sensors.erase(sensors.begin() + index);

        // Обновляем интерфейс: удаляем элемент из списка и строку из таблицы
        delete listWidget->takeItem(index);
        tableWidget->removeRow(index);

        qDebug() << "Sensor removed from system and UI at index:" << index;
    } else {
        qDebug() << "Invalid sensor index:" << index;
    }
}
