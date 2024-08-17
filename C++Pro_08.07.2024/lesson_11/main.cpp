#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();  // Важливо викликати метод show() для відображення вікна

    return app.exec();  // Запуск основного циклу подій
}
