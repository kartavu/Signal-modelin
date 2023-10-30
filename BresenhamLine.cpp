#include "mainwindow.h"
#define COUNTM 4
#include "Material.h"
#include "BrasenhamLine.h"

double drawBresenhamLine(QPainter* painter, const QPointF& start, const QPointF& end, Material *mate) {
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
