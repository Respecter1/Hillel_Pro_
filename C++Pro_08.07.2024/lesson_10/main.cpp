#include <QCoreApplication>
#include <QTimer>
#include <QRandomGenerator>
#include <vector>
#include <memory>
#include "Sensor.h"
#include "Logger.h"
#include "Analyzer.h"
#include "ConfigManager.h"
#include "Config.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    ConfigManager configManager;
    QCommandLineParser parser;
    configManager.processCommandLine(parser, app);

    std::vector<std::unique_ptr<Sensor>> sensors;
    sensors.reserve(NUM_SENSORS);
    for (int i = 1; i <= NUM_SENSORS; ++i)
    {
        sensors.push_back(std::make_unique<Sensor>(QString(SENSOR_NAME_FORMAT).arg(i)));
    }

    auto logger = std::make_unique<Logger>();
    auto analyzer = std::make_unique<Analyzer>();

    for (const auto& sensor : sensors) {
        QObject::connect(sensor.get(), &Sensor::dataReady, logger.get(), &Logger::writeData);
        QObject::connect(sensor.get(), &Sensor::dataReady, analyzer.get(), &Analyzer::analyzeData);
    }

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]()
                     {
                         static int iteration = 0;
                         if (iteration < NUM_SENSORS)
                         {
                             sensors[iteration]->newData(QRandomGenerator::global()->bounded(SENSOR_MAX_VALUE));
                             ++iteration;
                         }
                         if (iteration == NUM_SENSORS)
                         {
                             analyzer->reportPrint();
                             timer.stop();
                             QCoreApplication::quit();
                         }
                     });
    timer.start(TIMER_INTERVAL_MS);

    return app.exec();
}
