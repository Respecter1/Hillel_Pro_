#pragma once

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "Config.h"

void loadConfig(const QCommandLineParser &parser) {
    QString configFilePath = parser.value("config");

    QFile file(configFilePath);
    if (!file.exists()) {
        qWarning() << "Config file does not exist: " << configFilePath;
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open config file.";
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Error parsing JSON:" << error.errorString();
        return;
    }

    QJsonObject obj = doc.object();

    // Завантажуємо дані з JSON у відповідні змінні конфігурації
    if (obj.contains("date_time_format")) {
        Config::DATE_TIME_FORMAT = obj["date_time_format"].toString();
    }
    if (obj.contains("log_file_name_format")) {
        Config::LOG_FILE_NAME_FORMAT = obj["log_file_name_format"].toString();
    }
    if (obj.contains("sensor_name_format")) {
        Config::SENSOR_NAME_FORMAT = obj["sensor_name_format"].toString();
    }
    if (obj.contains("num_sensors")) {
        Config::NUM_SENSORS = obj["num_sensors"].toInt();
    }
    if (obj.contains("sensor_max_value")) {
        Config::SENSOR_MAX_VALUE = obj["sensor_max_value"].toInt();
    }
    if (obj.contains("timer_interval_ms")) {
        Config::TIMER_INTERVAL_MS = obj["timer_interval_ms"].toInt();
    }
    if (obj.contains("max_records")) {
        Config::MAX_RECORDS = obj["max_records"].toInt();
    }
    if (obj.contains("program_duration_ms")) {
        Config::PROGRAM_DURATION_MS = obj["program_duration_ms"].toInt();
    }

    // Перевизначаємо параметри, якщо вони були передані через командний рядок
    if (parser.isSet("date_time_format")) {
        Config::DATE_TIME_FORMAT = parser.value("date_time_format");
    }
    if (parser.isSet("log_file_name_format")) {
        Config::LOG_FILE_NAME_FORMAT = parser.value("log_file_name_format");
    }
    if (parser.isSet("sensor_name_format")) {
        Config::SENSOR_NAME_FORMAT = parser.value("sensor_name_format");
    }
    if (parser.isSet("num_sensors")) {
        Config::NUM_SENSORS = parser.value("num_sensors").toInt();
    }
    if (parser.isSet("sensor_max_value")) {
        Config::SENSOR_MAX_VALUE = parser.value("sensor_max_value").toInt();
    }
    if (parser.isSet("timer_interval_ms")) {
        Config::TIMER_INTERVAL_MS = parser.value("timer_interval_ms").toInt();
    }
    if (parser.isSet("max_records")) {
        Config::MAX_RECORDS = parser.value("max_records").toInt();
    }
    if (parser.isSet("program_duration_ms")) {
        Config::PROGRAM_DURATION_MS = parser.value("program_duration_ms").toInt();
    }
}


