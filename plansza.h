#ifndef PLANSZA_H
#define PLANSZA_H

#include <QList>
#include "podloze.h"


class Plansza
{
public:
    Plansza();


    QList<Podloze*> get_podloze();


      void rysuj_plansze();

private:
    QList<Podloze*> lista_podloza;

};

#endif // PLANSZA_H
