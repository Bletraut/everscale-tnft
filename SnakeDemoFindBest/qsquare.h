#ifndef QSQUARE_H
#define QSQUARE_H

#include <QGraphicsItem>
#include <QPainter>

class QSquare : public QGraphicsItem
{
public:
    QSquare();
    ~QSquare();

    bool m_show;

protected:
    QRectF boundingRect() const;    /* Определяем виртуальный метод,
                                     * который возвращает область, в которой
                                     * находится треугольник
                                     * */
    /* Определяем метод для отрисовки треугольника
     * */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // QSQUARE_H
