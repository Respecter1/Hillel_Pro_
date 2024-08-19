#pragma once

#include <QObject>
#include <QString>
#include <vector>

#include "SensorMetric.h"

class Logger : public QObject {
    Q_OBJECT
public:
    Logger(QObject* parent = nullptr);

    // Метод для записи данных в лог
    void writeData(const SensorMetric& aSensorMetric);

    // Метод для сохранения данных в файл
    void saveToFile(const QString& fileName) const;

    // Метод для получения записанных данных
    const std::vector<QString>& getLogData() const;

private:
    QString generateLogFileName() const;

    QString logFileName;
    std::vector<QString> logData;  // Хранение логов в памяти
};
