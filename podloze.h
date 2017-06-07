#ifndef PODLOZE_H
#define PODLOZE_H

#include <QGraphicsPixmapItem>
#include <QRect>
#include "postac.h"


class Podloze : public QGraphicsPixmapItem
{
public:
    Podloze(QString nazwa, QGraphicsItem* parent=NULL);

    void dodaj_obrone(Postac* komu);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    void set_pozycja_podloza(int x, int y);

    QPoint get_pozycja_podloza();
    int get_wartosc_obrony();
    bool zajety;

private:
    int wartosc_obrony;
    QPoint pozycja_podloza;



};

#endif // PODLOZE_H
