#include "mainwindow.h"
#include "Material.h"
#define COUNTM 5

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

double computeAttention(int materialType, double frequency) {
    if (materialType >= 0 &&  materialType < 5) {
        return arrayOfMaterial[materialType](frequency);
    } else {
        return 0.0;
    }
}
double (*arrayOfMaterial[5])(double) {
    calculationOfMultiPanelGlass,
    calculationOfGlass,
    calculationOfConcrete,
    calculationOfWood
};
Material material[COUNTM] = { {concrete, 416, 408, 426, 458, QColor(20, 20, 20, 1)},
                       {concrete, 467, 304, 477, 354,  QColor(20, 20, 20, 1)},
                       {concrete, 50, 100, 100, 150,  QColor(20, 20, 20, 1)},
                        {concrete, 312, 90, 362, 120, QColor(20, 20, 20, 1)},
                        {concrete, 48, 198, 72, 253,  QColor(20, 20, 20, 1)}
};
