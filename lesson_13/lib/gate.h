#pragma once
#include <iostream>

class Gate {
public:
    // Конструктор, задає початковий стан воріт (0-100%)
    Gate(int initial_opening);

    // Функція для відкриття воріт з перевіркою
    void open();

    // Функція для закриття воріт з перевіркою
    void close();

    // Перевірка, чи ворота повністю закриті
    bool isClosed() const;

private:
    // Поточний стан відкриття (0-100%)
    int current_opening;
};
