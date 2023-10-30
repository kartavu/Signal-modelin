#ifndef BRASENHAMLINE_H
#define BRASENHAMLINE_H



#include <QPainter>
#include "Material.h"



double drawBresenhamLine(QPainter* painter, const QPointF& start, const QPointF& end, Material *mate);


#endif // BRASENHAMLINE_H
