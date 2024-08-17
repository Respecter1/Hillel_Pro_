#pragma once
#include <QString>
#include <QJsonObject>


struct Config {
    static QString DATE_TIME_FORMAT;
    static QString LOG_FILE_NAME_FORMAT;
    static QString SENSOR_NAME_FORMAT;
    static int NUM_SENSORS;
    static int SENSOR_MAX_VALUE;
    static int TIMER_INTERVAL_MS;
    static int MAX_RECORDS;
    static int PROGRAM_DURATION_MS;

    static void loadFromJson(const QJsonObject &json);
};

