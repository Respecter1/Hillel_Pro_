#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_addSensor_clicked()
{
    QString sensorName = QString("Sensor-%1").arg(sensorSystem.getSensors().size() + 1);

    // Добавление сенсора в систему
    sensorSystem.addSensor(sensorName);

    // Обновление интерфейса
    ui->listWidget->addItem(sensorName);
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());  // Добавляем новую строку в таблицу
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(sensorName));
}

void MainWindow::on_pushButton_startSimulation_clicked()
{
    // Вызов метода симуляции из SensorSystem
    sensorSystem.run(ui->tableWidget, ui->progressBar);
}

void MainWindow::on_pushButton_saveToFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Data"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (!fileName.isEmpty()) {
        sensorSystem.saveDataToFile(fileName);
    }
}
void MainWindow::on_pushButton_clearSensor_clicked()
{
    int currentRow = ui->listWidget->currentRow();

    if (currentRow >= 0) {
        // Вызываем метод удаления сенсора из системы и обновления интерфейса
        sensorSystem.removeSensorAndUpdateUI(currentRow, ui->listWidget, ui->tableWidget);

        qDebug() << "Sensor removed at row:" << currentRow;
    } else {
        qDebug() << "No sensor selected for deletion.";
    }
}
