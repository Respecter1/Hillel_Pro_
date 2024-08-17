cmake_minimum_required(VERSION 3.16)

project(lesson_11 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пошук необхідних компонентів Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Список файлів проекту
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Analyzer.h Analyzer.cpp
    CommandLineOptions.h CommandLineOptions.cpp
    Config.h Config.cpp
    Logger.h Logger.cpp
    Sensor.h Sensor.cpp
    SensorMetric.h
    SensorSystem.h SensorSystem.cpp
    ConfigLoader.h ConfigLoader.cpp
    resources.qrc
)

# Перевірка версії Qt і додавання цілі збірки
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lesson_11
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(lesson_11
        ${PROJECT_SOURCES}
    )
endif()

# Лінкування з бібліотекою Qt Widgets
target_link_libraries(lesson_11 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Встановлення параметрів для різних платформ
set_target_properties(lesson_11 PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Додавання інсталяційних директорій
include(GNUInstallDirs)
install(TARGETS lesson_11
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Завершення для Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lesson_11)
endif()
