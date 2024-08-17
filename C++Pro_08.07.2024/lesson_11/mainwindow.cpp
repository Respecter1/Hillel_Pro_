#include "mainwindow.h"
#include "Config.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), sensorCounter(0)
{
    // Створюємо елементи інтерфейсу
    sensorListWidget = new QListWidget(this);
    resultTableWidget = new QTableWidget(this);
    simulationProgressBar = new QProgressBar(this);
    addButton = new QPushButton("Додати сенсор", this);
    removeButton = new QPushButton("Видалити сенсор", this);
    simulateButton = new QPushButton("Симуляція", this);

    // Задаємо макет для кнопок
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(simulateButton);

    // Основний макет
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(sensorListWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(resultTableWidget);
    mainLayout->addWidget(simulationProgressBar);

    // Створюємо віджет-обгортку і встановлюємо макет
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Встановлення мінімального розміру вікна
    setMinimumSize(600, 400);

    // Підключення сигналів та слотів
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addSensor);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeSensor);
    connect(simulateButton, &QPushButton::clicked, this, &MainWindow::simulateSensors);

    // Ініціалізація прогрес бару
    simulationProgressBar->setValue(0);

    // Ініціалізуємо SensorSystem
    sensorSystem = new SensorSystem(resultTableWidget, simulationProgressBar, this);
}

void MainWindow::addSensor()
{
    sensorCounter++;
    QString sensorName = QString("Sensor-%1").arg(sensorCounter);
    sensorListWidget->addItem(sensorName);
}

void MainWindow::removeSensor()
{
    int currentRow = sensorListWidget->currentRow(); // Отримуємо поточний рядок
    if (currentRow >= 0) {
        QListWidgetItem* item = sensorListWidget->takeItem(currentRow); // Видаляємо елемент зі списку
        delete item; // Видаляємо елемент з пам'яті
        sensorListWidget->update(); // Оновлюємо віджет
    } else {
        qDebug() << "No sensor selected for deletion.";
    }
}


void MainWindow::simulateSensors()
{
    // Очищення таблиці перед початком симуляції
    resultTableWidget->clearContents();
    resultTableWidget->setRowCount(0);  // Скидання кількості рядків
    simulationProgressBar->reset();  // Скидання прогрес-бару

    int numSensors = sensorListWidget->count();  // Отримуємо кількість сенсорів із UI

    // Ініціалізація сенсорів з передачею кількості
    sensorSystem->initialize(numSensors);
    sensorSystem->run();
}
