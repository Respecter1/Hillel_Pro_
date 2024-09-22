#include "gate.h"
#include <thread>
#include <chrono>

// Конструктор, задає початковий стан воріт (0-100%)
Gate::Gate(int initial_opening) : current_opening(initial_opening) {
    if (current_opening < 0) current_opening = 0;
    if (current_opening > 100) current_opening = 100;
    std::cout << "Gate initialized to " << current_opening << "%." << std::endl;
}

// Функція для перевірки чи ворота повністю закриті
bool Gate::isClosed() const {
    if (current_opening == 0) {
        std::cout << "Gate is fully closed." << std::endl;
        return true;
    } else {
        std::cout << "Gate is open to " << current_opening << "%." << std::endl;
        return false;
    }
}

// Функція для відкриття воріт з циклом
void Gate::open() {
    if (current_opening == 100) {
        std::cout << "Gate is already fully open." << std::endl;
        return;
    }

    std::cout << "Opening the gate..." << std::endl;
    for (int i = current_opening; i <= 100; i += 20) {
        current_opening = i;
        std::cout << "Gate opened to " << current_opening << "%." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Затримка на 1 секунду
    }
    current_opening = 100;
    std::cout << "Gate is now fully open." << std::endl;
}

// Функція для закриття воріт з циклом
void Gate::close() {
    if (current_opening == 0) {
        std::cout << "Gate is already fully closed." << std::endl;
        return;
    }

    std::cout << "Closing the gate..." << std::endl;
    for (int i = current_opening; i >= 0; i -= 20) {
        current_opening = i;
        std::cout << "Gate closed to " << (100 - current_opening) << "%." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Затримка на 1 секунду
    }
    current_opening = 0;
    std::cout << "Gate is now fully closed." << std::endl;
}
