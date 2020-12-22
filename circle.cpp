#include "circle.h"

Circle::Circle() :
    QGraphicsItem()
{

}

Circle::~Circle()
{

}

QRectF Circle::boundingRect() const
{
    return QRectF(-250,-400,500,800);   // Ограничиваем область, в которой лежит круг
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->drawEllipse(0, 0, 124, 124);     // Устанавливаем кисть, которой будем отрисовывать объект
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
