#include "SensorSystem.h"
#include "Config.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QCoreApplication>

void SensorSystem::initialize() {
    sensors.reserve(Config::NUM_SENSORS);
    for (int i = 1; i <= Config::NUM_SENSORS; ++i) {
        auto sensor = std::make_unique<Sensor>(QString(Config::SENSOR_NAME_FORMAT).arg(i));
        auto logger = std::make_unique<Logger>(sensor->objectName());  // Створюємо унікальний логгер для кожного сенсора
        sensors.push_back(std::move(sensor));

        QObject::connect(sensors.back().get(), &Sensor::dataReady, logger.get(), &Logger::writeData);
    }
}

void SensorSystem::run() {
    QTimer* timer = new QTimer(this);  // Створюємо таймер з батьком для автоматичного видалення

    connect(timer, &QTimer::timeout, this, [=]() {
        static int iteration = 0;


        if (iteration < Config::NUM_SENSORS) {
            sensors[iteration]->newData(QRandomGenerator::global()->bounded(Config::SENSOR_MAX_VALUE));
            ++iteration;
        }

        if (iteration == Config::NUM_SENSORS) {
            qDebug() << "All sensors have completed. Generating report...";
            analyzer->reportPrint();
            timer->stop();
            QCoreApplication::quit();
        }
    });

    timer->start(Config::TIMER_INTERVAL_MS);  // Запускаємо таймер
}


