cmake_minimum_required(VERSION 3.0)
#Вказує мінімальну версію CMAKE для зпуску програми яка повинна бути встановленна на власному пк

project(Homework_1)
#назва проекту по якому можна буде його запускати 

set(CMAKE_CXX_STANDARD 17)
#вибір стандарта для проекту

add_executable(Homework_1 main.cpp myUnique_ptr.h)
#це типу макроса(псевдоніма) для мого проекта і написавши його я запускаю проект 
