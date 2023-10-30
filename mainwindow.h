#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class SignalAttenuationWidget; }
QT_END_NAMESPACE

class SignalAttenuationWidget : public QMainWindow {
    Q_OBJECT
public:
    //SignalAttenuationWidget(QWidget* parent = nullptr);
    SignalAttenuationWidget(QWidget *parent = nullptr);
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


    bool isPointOnLine(const QPointF& startPoint, const QPointF& endPoint, const QPointF& point);
    double computeSignalAttenuation(double distance, double lineLength, const QPointF& startPoint, const QPointF& endPoint, const QPointF& point);
    double drawBresenhamLine(QPainter* painter, const QPointF& start, const QPointF& end);
};

#endif // MAINWINDOW_H
