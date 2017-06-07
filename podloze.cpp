#include "podloze.h"
#include "gra.h"

extern Gra* gra;
extern Plansza* plansza;

Podloze::Podloze(QString nazwa, QGraphicsItem* parent)
{

    if(nazwa=="las")
    {
        setPixmap(QPixmap(":/obrazki/img/las.png"));
        wartosc_obrony=10;
    }
    else if (nazwa=="gora")
    {
        setPixmap(QPixmap(":/obrazki/img/gora.png"));
        wartosc_obrony=15;
    }
    else if (nazwa=="trawa")
    {
        setPixmap(QPixmap(":/obrazki/img/trawa.png"));
        wartosc_obrony=5;
    }
    else if (nazwa=="droga")
    {
        setPixmap(QPixmap(":/obrazki/img/droga.png"));
        wartosc_obrony=0;
    }

}

void Podloze::dodaj_obrone(Postac *komu)
{
    komu->set_obrona_aktualna(komu->get_obrona()+this->get_wartosc_obrony());

}

void Podloze::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    for(int i=0; i<gra->get_lista_mozliwych_ruchow().size(); i++)
    {
        QPoint mozliwa_pozycja=gra->get_lista_mozliwych_ruchow().at(i);

    if(gra->postac_do_przemieszczenia!=NULL && this->get_pozycja_podloza()==mozliwa_pozycja && this->zajety==0)
    {
        gra->przesun_postac(this);
        gra->zwolnij_podloze();
    }
    }

}

void Podloze::set_pozycja_podloza(int x, int y)
{
    pozycja_podloza.setX(x);
    pozycja_podloza.setY(y);

}

QPoint Podloze::get_pozycja_podloza()
{
    return pozycja_podloza;
}

int Podloze::get_wartosc_obrony()
{
    return wartosc_obrony;
}
