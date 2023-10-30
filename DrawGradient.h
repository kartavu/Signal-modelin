#ifndef DRAWGRADIENT_H
#define DRAWGRADIENT_H



#include "Material.h"
#include "BrasenhamLine.h"


#include <QLabel>
#include <QVBoxLayout>
#include <cmath>
#include <QPainter>
#include <QLineF>
#include <QtMath>
#include <QtWidgets>



class DrawGradient {
public:
    DrawGradient();
    void draw( QImage *mapImage );

private:


};
#endif // DRAWGRADIENT_H
