#pragma once

#include <QCommandLineParser>

void loadConfig(const QString& configFilePath);
void applyCommandLineOptions(const QCommandLineParser& parser);
