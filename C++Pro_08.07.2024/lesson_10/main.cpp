#include <QCoreApplication>
#include <QTimer>
#include <QRandomGenerator>
#include <memory>
#include <QCommandLineParser>

#include "Sensor.h"
#include "Logger.h"
#include "Analyzer.h"
#include "Config.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Sensor Data Analyzer");
    parser.addHelpOption();
    parser.addVersionOption();


    parser.addOption(QCommandLineOption(QStringList() << "c" << "config",
                                        "Path to the configuration file.",
                                        "config",
                                        "config.json"));
    parser.addOption(QCommandLineOption(QStringList() << "date_time_format",
                                        "Date time format.",
                                        "date_time_format"));
    parser.addOption(QCommandLineOption(QStringList() << "log_file_name_format",
                                        "Log file name format.",
                                        "log_file_name_format"));
    parser.addOption(QCommandLineOption(QStringList() << "sensor_name_format",
                                        "Sensor name format.",
                                        "sensor_name_format"));
    parser.addOption(QCommandLineOption(QStringList() << "num_sensors",
                                        "Number of sensors.",
                                        "num_sensors"));
    parser.addOption(QCommandLineOption(QStringList() << "sensor_max_value",
                                        "Maximum sensor value.",
                                        "sensor_max_value"));
    parser.addOption(QCommandLineOption(QStringList() << "timer_interval_ms",
                                        "Timer interval in milliseconds.",
                                        "timer_interval_ms"));
    parser.addOption(QCommandLineOption(QStringList() << "max_records",
                                        "Maximum number of records.",
                                        "max_records"));
    parser.addOption(QCommandLineOption(QStringList() << "program_duration_ms",
                                        "Program duration in milliseconds.",
                                        "program_duration_ms"));

    parser.process(app);

    std::vector<std::unique_ptr<Sensor>> sensors;
    sensors.reserve(Config::NUM_SENSORS);
    for (int i = 1; i <= Config::NUM_SENSORS; ++i) {
        sensors.push_back(std::make_unique<Sensor>(QString(Config::SENSOR_NAME_FORMAT).arg(i)));
    }

    auto logger = std::make_unique<Logger>();
    auto analyzer = std::make_unique<Analyzer>();

    for (const auto& sensor : sensors) {
        QObject::connect(sensor.get(), &Sensor::dataReady, logger.get(), &Logger::writeData);
        QObject::connect(sensor.get(), &Sensor::dataReady, analyzer.get(), &Analyzer::analyzeData);
    }

    // Таймер для збору даних
    QTimer dataTimer;
    QObject::connect(&dataTimer, &QTimer::timeout, [&]() {
        for (auto& sensor : sensors) {
            sensor->newData(QRandomGenerator::global()->bounded(Config::SENSOR_MAX_VALUE));
        }
    });
    dataTimer.start(Config::TIMER_INTERVAL_MS);

    // Таймер для завершення програми через заданий час
    QTimer::singleShot(Config::PROGRAM_DURATION_MS, [&]() {
        analyzer->reportPrint();
        QCoreApplication::quit();
    });

    return app.exec();
}
