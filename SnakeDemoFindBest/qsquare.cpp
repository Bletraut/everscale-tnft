#include "qsquare.h"

QSquare::QSquare():QGraphicsItem()
{

}

QSquare::~QSquare()
{

}

QRectF QSquare::boundingRect() const
{
    return QRectF(0,0,10,10);   // Ограничиваем область, в которой лежит фигура
}

void QSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;   // Используем класс полигона, чтобы отрисовать фигуру
    // Помещаем координаты точек в полигональную модель
    polygon << QPoint(0,0) << QPoint(10,0) << QPoint(10,10) << QPoint(0,10);
    painter->setBrush(Qt::black);     // Устанавливаем кисть, которой будем отрисовывать объект
    painter->drawPolygon(polygon);  // Рисуем фигуру по полигональной модели
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
