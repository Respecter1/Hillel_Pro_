#pragma once

#include <QObject>
#include "SensorMetric.h"

class Logger : public QObject
{
    Q_OBJECT
public:
    Logger(QObject* parent = nullptr);

public slots:
    void writeData(const SensorMetric& aSensorMetric);

private:
    QString generateLogFileName() const;
};
