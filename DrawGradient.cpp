#include "mainwindow.h"
#include "Material.h"
#include "BrasenhamLine.h"
#include "DrawGradient.h"

#include <QLabel>
#include <QVBoxLayout>
#include <cmath>
#include <QPainter>
#include <QLineF>
#include <QtMath>
#include <QtWidgets>

DrawGradient::DrawGradient()
{

}

void DrawGradient::draw( QImage *mapImage ){


    QPointF center(200, 200);
    QPointF startPoint(center);
    QPointF endPoint(800, 800);
    QPainter painter(mapImage);

    qreal dx = endPoint.x() - startPoint.x();
    qreal dy = endPoint.y() - startPoint.y();
    qreal lineLength = sqrt(dx * dx + dy * dy);
    for (int x = 0; x < mapImage->width(); x++) {
        for (int y = 0; y < mapImage->height(); y++) {

            QPointF point(x, y);
            double distance = QLineF(center, point).length();

            double gradientValue = distance / (mapImage->width() / 2.0);

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

            mapImage->setPixelColor(x, y, color);
            for(int i = 0; i < COUNTM; ++i){
                if(x > material[i].x_Pozition && x < material[i].x1_Size && y > material[i].y_Pozition && y < material[i].y1_Size){
                    mapImage->setPixelColor(x, y, material[i].col);
                }

            }

        }
    }
}




