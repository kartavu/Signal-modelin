
#include <QApplication>
#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <cmath>
#include <QPainter>
#include <QLineF>
#include <QtMath>

int main(int argc, char* argv[]) {
QApplication app(argc, argv);
SignalAttenuationWidget widget;
widget.show();
return app.exec();
}





