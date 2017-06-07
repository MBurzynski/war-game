#ifndef PRZYCISK_H
#define PRZYCISK_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>


class Przycisk : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Przycisk(QString nazwa, QGraphicsItem* parent=NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();

private:
    QGraphicsTextItem* tekst;
};

#endif // PRZYCISK_H
