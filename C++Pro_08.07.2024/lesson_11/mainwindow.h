#pragma once

#include <QMainWindow>
#include <QListWidget>
#include <QTableWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCoreApplication>
#include "SensorSystem.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void addSensor();
    void removeSensor();
    void simulateSensors();

private:
    QListWidget* sensorListWidget;
    QTableWidget* resultTableWidget;
    QProgressBar* simulationProgressBar;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* simulateButton;

    int sensorCounter;
    SensorSystem* sensorSystem;
};
