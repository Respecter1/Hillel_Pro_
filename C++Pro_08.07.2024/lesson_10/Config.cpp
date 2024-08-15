#include "Config.h"

// Ініціалізація статичних змінних
QString Config::DATE_TIME_FORMAT = "yyyy-MM-dd hh:mm:ss";
QString Config::LOG_FILE_NAME_FORMAT = "log_%132.txt";
QString Config::SENSOR_NAME_FORMAT = "Sensor_%12";
int Config::NUM_SENSORS = 10;
int Config::SENSOR_MAX_VALUE = 100;
int Config::TIMER_INTERVAL_MS = 1000;
int Config::MAX_RECORDS = 10000;
int Config::PROGRAM_DURATION_MS = 10000;

void Config::loadFromJson(const QJsonObject &json) {
    if (json.contains("date_time_format")) {
        DATE_TIME_FORMAT = json["date_time_format"].toString();
    }
    if (json.contains("log_file_name_format")) {
        LOG_FILE_NAME_FORMAT = json["log_file_name_format"].toString();
    }
    if (json.contains("sensor_name_format")) {
        SENSOR_NAME_FORMAT = json["sensor_name_format"].toString();
    }
    if (json.contains("num_sensors")) {
        NUM_SENSORS = json["num_sensors"].toInt();
    }
    if (json.contains("sensor_max_value")) {
        SENSOR_MAX_VALUE = json["sensor_max_value"].toInt();
    }
    if (json.contains("timer_interval_ms")) {
        TIMER_INTERVAL_MS = json["timer_interval_ms"].toInt();
    }
    if (json.contains("max_records")) {
        MAX_RECORDS = json["max_records"].toInt();
    }
    if (json.contains("program_duration_ms")) {
        PROGRAM_DURATION_MS = json["program_duration_ms"].toInt();
    }
}
