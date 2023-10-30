#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QtWidgets>


struct Material;

QT_BEGIN_NAMESPACE
namespace Ui { class SignalAttenuationWidget; }
QT_END_NAMESPACE

class SignalAttenuationWidget : public QMainWindow {
    Q_OBJECT
public:
    //SignalAttenuationWidget(QWidget* parent = nullptr);
    SignalAttenuationWidget(QWidget *parent = nullptr);
    //double computeSignalAttenuation(double distance, double lineLength, const QPointF& startPoint, const QPointF& endPoint, const QPointF& point);
private:
    Ui::SignalAttenuationWidget *ui;

    double frequency;
    double distanceStep;
    QImage mapImage;
    void draw_gradient();

    QPixmap *pixmap;
    QGraphicsScene* scene;
    QGraphicsView *view;

    QLabel *label_;
    QGroupBox *gradientGroupBox;
};

#endif // MAINWINDOW_H
