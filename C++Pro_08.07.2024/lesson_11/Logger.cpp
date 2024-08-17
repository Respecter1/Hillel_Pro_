#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include "Config.h"
#include <QDir>

Logger::Logger(const QString& sensorName, QObject* parent)
    : QObject(parent)
{
    // Генеруємо унікальне ім'я файлу для кожного сенсора при кожному запуску
    logFileName = generateLogFileName(sensorName);
}

QString Logger::generateLogFileName(const QString& sensorName) const
{
    // Отримуємо шлях до виконуваного файлу
    QString currentPath = QDir::currentPath();
    qDebug() << "Current path: " << currentPath;  // Діагностика: виводимо шлях до каталогу

    // Генеруємо нове ім'я файлу з урахуванням дати і часу кожного запуску програми
    QString uniqueFileName = QString("%1_%2.txt").arg(sensorName).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss"));

    // Поєднуємо шлях і унікальне ім'я файлу
    return QDir(currentPath).filePath(uniqueFileName);
}

void Logger::writeData(const SensorMetric& aSensorMetric)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString logMessage = QString("%1 | name=%2 | value=%3").arg(timestamp, aSensorMetric.name, QString::number(aSensorMetric.value));

    qDebug() << logMessage.toStdString().c_str();

    QFile file(logFileName);  // Використовуємо унікальне ім'я файлу для кожного сенсора

    // Додатковий діагностичний код для перевірки, чи можливо створити файл
    if (!file.exists()) {
        qDebug() << "File does not exist, trying to create: " << logFileName;
    }

    if (file.open(QIODevice::Append | QIODevice::Text))  // Відкриваємо файл для запису
    {
        QTextStream out(&file);
        out << logMessage << "\n";
        file.close();
        qDebug() << "File written: " << logFileName;  // Додаємо повідомлення про успішний запис у файл
    }
    else
    {
        qDebug() << "Failed to open file for writing: " << logFileName;  // Виведення помилки, якщо файл не вдалося відкрити
        qDebug() << "Error: " << file.errorString();  // Виводимо текст помилки
    }
}
