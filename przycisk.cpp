#include "przycisk.h"


Przycisk::Przycisk(QString nazwa, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0,0,200,60);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    setBrush(brush);

    tekst= new QGraphicsTextItem(nazwa,this);
    int x=rect().width()/2-tekst->boundingRect().width()/2;
    int y=rect().height()/2-tekst->boundingRect().height()/2;
    tekst->setPos(x,y);

    setAcceptHoverEvents(true);

}

void Przycisk::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();

}

void Przycisk::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::lightGray);
    setBrush(brush);
}

void Przycisk::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    setBrush(brush);
}
