#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <cmath>
#include <QPainter>
#include <QLineF>
#include <QtMath>
#include <QtWidgets>

#include "Material.h"
#include "BrasenhamLine.h"


SignalAttenuationWidget::SignalAttenuationWidget(QWidget *parent)
    : QMainWindow(parent)

{
    this->setFixedSize(1300, 1000);
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    frequency = 2.4;
    distanceStep = 1;

    mapImage = QImage(1000, 1000, QImage::Format_RGB32);
    DrawGradient drw;
    drw.draw(&mapImage);

    QLabel* imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap::fromImage(mapImage));
    scene->addPixmap(QPixmap::fromImage(mapImage));

    view->setGeometry(170, 0, 1000, 1000);
    this->layout()->addWidget(view);
    draw_gradient();
}



void SignalAttenuationWidget::draw_gradient(){
    gradientGroupBox = new QGroupBox(QStringLiteral("Signal Strength"));
    gradientGroupBox->setGeometry(10, 100, 150, 500);
    int height = 400;
    int width = 150;
    int border = 10;
    QLinearGradient gr(0, 0, 1, height - 2 * border);
    gr.setColorAt(1.0f, Qt::blue);
    gr.setColorAt(0.8f, Qt::cyan);
    gr.setColorAt(0.6f, Qt::green);
    gr.setColorAt(0.4f, Qt::yellow);
    gr.setColorAt(0.0f, Qt::red);

    //blue,cyan,green,yellow,red
    QPixmap pm(width, height);
    pm.fill(Qt::transparent);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(gr));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(border, border, 35, height - 2 * border);
    pmp.setPen(Qt::black);
    int step = (height - 2 * border) / 10;
    for (int i = 0; i < 11; i++) {
        int yPos = i * step + border;
        pmp.drawLine(border, yPos, 55, yPos);
        pmp.drawText(60, yPos + 2, QString("%1 [dBm]").arg(-44 - (i * 10)));
    }

    label_ = new QLabel();
    label_->setPixmap(pm);

    QVBoxLayout *colorMapVBox = new QVBoxLayout;
    colorMapVBox->addWidget(label_);
    gradientGroupBox->setLayout(colorMapVBox);
    this->layout()->addWidget(gradientGroupBox);
}


