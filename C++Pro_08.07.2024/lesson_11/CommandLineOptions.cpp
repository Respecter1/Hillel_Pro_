#include "CommandLineOptions.h"

void setupCommandLineParser(QCoreApplication &app, QCommandLineParser &parser) {
    parser.setApplicationDescription("Sensor Data Analyzer");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption(QCommandLineOption("config", "Path to the configuration file.", "config", "config.json"));
    parser.addOption(QCommandLineOption("date_time_format", "Date time format.", "format"));
    parser.addOption(QCommandLineOption("log_file_name_format", "Log file name format.", "format"));
    parser.addOption(QCommandLineOption("sensor_name_format", "Sensor name format.", "format"));
    parser.addOption(QCommandLineOption("num_sensors", "Number of sensors.", "number"));
    parser.addOption(QCommandLineOption("sensor_max_value", "Maximum sensor value.", "value"));
    parser.addOption(QCommandLineOption("timer_interval_ms", "Timer interval in milliseconds.", "interval"));
    parser.addOption(QCommandLineOption("max_records", "Maximum number of records.", "number"));
    parser.addOption(QCommandLineOption("program_duration_ms", "Program duration in milliseconds.", "duration"));

    parser.process(app);
}
