#include "mainwindow.h"

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
    int sensorCount = sensorListWidget->count();
    if (sensorCount == 0) {
        return;
    }

    // Ініціалізація таблиці результатів
    resultTableWidget->setRowCount(sensorCount);
    resultTableWidget->setColumnCount(2); // Колонки: Sensor Name, Value
    resultTableWidget->setHorizontalHeaderLabels({"Sensor Name", "Value"});

    simulationProgressBar->setRange(0, sensorCount);
    simulationProgressBar->setValue(0);

    // Симуляція для кожного сенсора
    for (int i = 0; i < sensorCount; ++i) {
        // Отримуємо ім'я сенсора
        QListWidgetItem* sensorItem = sensorListWidget->item(i);
        QString sensorName = sensorItem->text();

        // Генерація випадкового значення для сенсора
        int sensorValue = QRandomGenerator::global()->bounded(100); // Генеруємо випадкове значення від 0 до 99

        // Додаємо результат в таблицю
        resultTableWidget->setItem(i, 0, new QTableWidgetItem(sensorName));
        resultTableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(sensorValue)));

        // Оновлення прогрес-бару
        simulationProgressBar->setValue(i + 1);

        // Для анімації або затримки (опціонально)
        QCoreApplication::processEvents();
    }
}


