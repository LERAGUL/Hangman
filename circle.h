#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsItem>
#include <QPainter>

class Circle : public QGraphicsItem
{
public:
    Circle();
    ~Circle();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // метод для рисования круга
};

#endif // CIRCLE_H
