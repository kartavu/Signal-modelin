#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <cmath>
#include <QPainter>
#include <QLineF>
#include <QtMath>
#include <QtWidgets>
#define COUNTM 4


SignalAttenuationWidget::SignalAttenuationWidget(QWidget *parent)
    : QMainWindow(parent)
{


    Material material[COUNTM] = { {glass, 400, 400, 410, 450, QColor(20, 20, 20, 1)},
                           {wood, 450, 300, 460, 350,  QColor(255, 228, 205, 1)},
                           {concrete, 50, 100, 100, 105,  QColor(129, 132, 121, 1)},
                            {multiPanelGlass, 50, 200, 100, 205,  QColor(255, 132, 121, 1)}


                                };

    this->setFixedSize(1300, 1000);
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    frequency = 2.4;
    distanceStep = 1;


    mapImage = QImage(1000, 1000, QImage::Format_RGB32);

    QPointF center(200, 200);
    QPointF startPoint(center);
    QPointF endPoint(800, 800);



    qreal dx = endPoint.x() - startPoint.x();
    qreal dy = endPoint.y() - startPoint.y();
    qreal lineLength = sqrt(dx * dx + dy * dy);

    QPainter painter(&mapImage);

    for (int x = 0; x < mapImage.width(); x++) {
        for (int y = 0; y < mapImage.height(); y++) {

            QPointF point(x, y);
            double distance = QLineF(center, point).length();

            double gradientValue = distance / (mapImage.width() / 2.0);

            double redComponent = qBound(0.0, 1.0 - gradientValue * 2, 1.0);
            double greenComponent = qBound(0.0, gradientValue * 2, 1.0);
            double blueComponent = qBound(0.0, (gradientValue - 0.5) * 2, 1.0);

            double ff = drawBresenhamLine(&painter, center, QPointF(x, y), material) / 10.0;

            gradientValue += ff/20;

            redComponent = qBound(0.0, 1.0 - gradientValue * 2, 1.0);
            greenComponent = qBound(0.0, gradientValue * 2, 1.0);
            blueComponent = qBound(0.0, (gradientValue - 0.5) * 2, 1.0);

            QColor color;
            color.setRedF(redComponent);
            color.setGreenF(greenComponent);
            color.setBlueF(blueComponent);
            mapImage.setPixelColor(x, y, color);
            for(int i = 0; i < COUNTM; ++i){
                if(x > material[i].x_Pozition && x < material[i].x1_Size && y > material[i].y_Pozition && y < material[i].y1_Size){
                    mapImage.setPixelColor(x, y, material[i].col);
                }

            }

        }
    }

    QLabel* imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap::fromImage(mapImage));
    scene->addPixmap(QPixmap::fromImage(mapImage));

    view->setGeometry(170, 0, 1000, 1000);
    this->layout()->addWidget(view);


    draw_gradient();

}

bool SignalAttenuationWidget::isPointOnLine(const QPointF& startPoint, const QPointF& endPoint, const QPointF& point) {
    qreal distance = QLineF(startPoint, endPoint).length();
    qreal d1 = QLineF(startPoint, point).length() + QLineF(point, endPoint).length();
    return qAbs(distance - d1) < 1.0;
}

double SignalAttenuationWidget::computeSignalAttenuation(double distance, double lineLength, const QPointF& startPoint, const QPointF& endPoint, const QPointF& point) {
    double attenuation = 1.0;
    if (isPointOnLine(startPoint, endPoint, point)) {
        qreal distanceToLine = QLineF(startPoint, point).length() * sin(qDegreesToRadians(QLineF(startPoint, point).angleTo(QLineF(startPoint, endPoint))));
        attenuation = 1.0 - qBound(0.0, distanceToLine / lineLength, 1.0);

    }
    return attenuation;
}

double SignalAttenuationWidget::drawBresenhamLine(QPainter* painter, const QPointF& start, const QPointF& end, Material *mate) {
    int x0 = int(start.x());
    int y0 = int(start.y());
    int x1 = int(end.x());
    int y1 = int(end.y());

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    double ff = 0;

    while (x0 != x1 || y0 != y1) {
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
            for(int i = 0; i < COUNTM; ++i){
                if(x0 > mate[i].x_Pozition && x0 < mate[i].x1_Size && y0 > mate[i].y_Pozition && y0 < mate[i].y1_Size){
                    ff += mate[i].Pl_Function(2.4);
                }

            }
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
    return ff;
}
float PL(float f, float d){
    return 28 + 22 * log10(f) + 20* log10(d);
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



double calculationOfMultiPanelGlass(double f) {
    double multiPanelGlass = 2.0 + (0.2 * f);
    return multiPanelGlass;
}

double calculationOfGlass(double f) {
    double glass = 23.0 + (0.3 * f);
    return glass;
}

double calculationOfConcrete(double f) {
    double concrete = 5.0 + (4.0 * f);
    return concrete;
}

double calculationOfWood(double f) {
    double wood = 4.85 + (0.12 * f);
    return wood;
}

double (*arrayOfMaterial[4])(double) {
    calculationOfMultiPanelGlass,
    calculationOfGlass,
    calculationOfConcrete,
    calculationOfWood
};

