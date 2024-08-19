#pragma once

#include <QMainWindow>
#include "SensorSystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_addSensor_clicked();
    void on_pushButton_startSimulation_clicked();
    void on_pushButton_saveToFile_clicked();
    void on_pushButton_clearSensor_clicked();
private:
    Ui::MainWindow *ui;
    SensorSystem sensorSystem;
};
