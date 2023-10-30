#ifndef MATERIAL_H
#define MATERIAL_H
#include "DrawGradient.h"
//#include "BrasenhamLine.h"


#define COUNTM 4
extern double (*arrayOfMaterial[4])(double);
enum typeOfMaterial {
    multiPanelGlass,
    glass,
    concrete,
    wood
};


struct Material {
    typeOfMaterial type;
    int x_Pozition, y_Pozition, x1_Size, y1_Size;
    double Pl_Function(double f) {
        return arrayOfMaterial[type](f);
    }
    QColor col;
};
extern Material material[COUNTM];


double calculationOfMultiPanelGlass(double f);
double calculationOfGlass(double f);
double calculationOfConcrete(double f);
double calculationOfWood(double f);
#endif // MATERIAL_H
