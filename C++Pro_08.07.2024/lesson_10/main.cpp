#include "ConfigLoader.h"          // Для loadConfig
#include "CommandLineOptions.h"    // Для applyCommandLineOptions
#include "SensorSystem.h"          // Для SensorSystem

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    app.setApplicationName("HV_10");
    app.setApplicationVersion("1.0.0");

    // Парсинг командного рядка
    QCommandLineParser parser;
    setupCommandLineParser(app, parser);

    // Завантаження конфігурації
    QString configFilePath = parser.value("config");
    loadConfig(configFilePath);


    applyCommandLineOptions(parser);



    // Ініціалізація та запуск сенсорної системи
    SensorSystem sensorSystem;
    sensorSystem.initialize();
    sensorSystem.run();

    return app.exec();
}
