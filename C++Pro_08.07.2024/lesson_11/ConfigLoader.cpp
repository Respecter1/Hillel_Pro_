#include "ConfigLoader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "Config.h"
#include <functional>
#include <vector>

void loadConfig(const QString& configFilePath) {
    QFile file(configFilePath);

    // Перевірка наявності файлу та копіювання за потреби
    if (!file.exists() && QFile::copy(":/config.json", configFilePath)) {
        file.setPermissions(QFile::ReadOwner | QFile::WriteOwner);
    }

    // Спроба відкрити файл
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open config file at" << configFilePath;
        return;
    }

    // Читання та парсинг JSON
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Error parsing JSON:" << error.errorString();
        return;
    }

    // Завантаження конфігурації
    Config::loadFromJson(doc.object());
}

void applyCommandLineOptions(const QCommandLineParser& parser) {
    struct OptionHandler {
        const char* optionName;
        std::function<void(const QString&)> handler;
    };

    // Масив обробників для кожної опції
    std::vector<OptionHandler> handlers =
        {
         {"date_time_format", [](const QString& value) { Config::DATE_TIME_FORMAT = value; }},
         {"log_file_name_format", [](const QString& value) { Config::LOG_FILE_NAME_FORMAT = value; }},
         {"sensor_name_format", [](const QString& value) { Config::SENSOR_NAME_FORMAT = value; }},
         {"num_sensors", [](const QString& value) { Config::NUM_SENSORS = value.toInt(); }},
         {"sensor_max_value", [](const QString& value) { Config::SENSOR_MAX_VALUE = value.toInt(); }},
         {"timer_interval_ms", [](const QString& value) { Config::TIMER_INTERVAL_MS = value.toInt(); }},
         {"max_records", [](const QString& value) { Config::MAX_RECORDS = value.toInt(); }},
         {"program_duration_ms", [](const QString& value) { Config::PROGRAM_DURATION_MS = value.toInt(); }},
         };

    for (const auto& handler : handlers) {
        if (parser.isSet(handler.optionName)) {
            handler.handler(parser.value(handler.optionName));
        }
    }
}
