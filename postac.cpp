#include "postac.h"
#include "gra.h"
#include "plansza.h"
#include <cmath>

extern Gra* gra;
extern Plansza* plansza;


void Postac::mozliwe_ruchy()
{
    QPoint jednostka=get_pozycja_jednostki();

    for(int i=0;i<plansza->get_podloze().size();i++)
    {
        QPoint punkt = plansza->get_podloze().at(i)->get_pozycja_podloza();

        if(((abs(punkt.x()-jednostka.x())+abs(punkt.y()-jednostka.y()))<=get_zasieg_ruchu()))
            if(plansza->get_podloze().at(i)->zajety==0)
            {
                QGraphicsEllipseItem* podswietlenie=new QGraphicsEllipseItem(punkt.x()*50,punkt.y()*50,50,50);
                QPen* czerwony=new QPen(Qt::red,3);
                podswietlenie->setPen(*czerwony);
                gra->scene->addItem(podswietlenie);
                gra->lista_mozliwych_ruchow.append(punkt);
                gra->lista_kolek.append(podswietlenie);

            }
        }

}

void Postac::mozliwy_atak()
{
    QPoint jednostka=get_pozycja_jednostki();

    if(get_wlasciciel()==QString("NIEBIESKI"))
    {

    for(int i=0;i<gra->get_jednostki_czerwone().size();i++)
    {
        QPoint punkt=gra->get_jednostki_czerwone().at(i)->get_pozycja_jednostki();

        if(((abs(punkt.x()-jednostka.x())+abs(punkt.y()-jednostka.y()))<=get_zasieg_ataku()))
        {
            QGraphicsEllipseItem* podswietlenie_niebieskie=new QGraphicsEllipseItem(punkt.x()*50,punkt.y()*50,50,50);
            QPen* niebieski=new QPen(Qt::blue,3);
            podswietlenie_niebieskie->setPen(*niebieski);
            gra->scene->addItem(podswietlenie_niebieskie);
            gra->lista_mozliwych_atakow.append(punkt);
            gra->lista_kolek_ataku.append(podswietlenie_niebieskie);
        }
    }
    }

    if(get_wlasciciel()==QString("CZERWONY"))
    {

    for(int i=0;i<gra->get_jednostki_niebieskie().size();i++)
    {
        QPoint punkt=gra->get_jednostki_niebieskie().at(i)->get_pozycja_jednostki();

        if(((abs(punkt.x()-jednostka.x())+abs(punkt.y()-jednostka.y()))<=get_zasieg_ataku()))
        {
            QGraphicsEllipseItem* podswietlenie_niebieskie=new QGraphicsEllipseItem(punkt.x()*50,punkt.y()*50,50,50);
            QPen* niebieski=new QPen(Qt::blue,3);
            podswietlenie_niebieskie->setPen(*niebieski);
            gra->scene->addItem(podswietlenie_niebieskie);
            gra->lista_mozliwych_atakow.append(punkt);
            gra->lista_kolek_ataku.append(podswietlenie_niebieskie);
        }
    }
    }

}

void Postac::atak(Postac *kogo)
{
    int wartosc_ataku;
    wartosc_ataku= rand()%(gra->aktywna_postac->get_max_atak()-gra->aktywna_postac->get_min_atak())+gra->aktywna_postac->get_min_atak()-kogo->get_obrona_aktualna();
    kogo->set_zycie(kogo->get_zycie()-wartosc_ataku);
    gra->usun_kolka_ataku();
    gra->usun_kolka();
    gra->lista_mozliwych_atakow.clear();
    kogo->aktualizacja_paska_zycia();
    kogo->sprawdz_czy_zyje();
    gra->aktywna_postac->set_czy_sie_ruszyl(true);
    gra->aktywna_postac->set_czy_atakowal(true);
    gra->aktywna_postac->set_zaznaczona(false);
    gra->aktywna_postac=NULL;
    gra->postac_do_przemieszczenia=NULL;

}

void Postac::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    //Jeśli postać nie jest zaznaczona to zaznacz ją
    if(get_zaznaczona()==0 && get_wlasciciel()==gra->get_czyj_ruch() && gra->postac_do_przemieszczenia==NULL && get_czy_sie_ruszyl()==0)
    {
        gra->aktywna_postac=NULL;
        gra->usun_kolka_ataku();
        gra->lista_mozliwych_atakow.clear();
        gra->zaznacz_postac(this);
        this->mozliwe_ruchy();
        this->mozliwy_atak();
    }
    else if(get_wlasciciel()==gra->get_czyj_ruch() && get_czy_sie_ruszyl()==0)
    {
        gra->postac_do_przemieszczenia->set_czy_sie_ruszyl(false);
        gra->postac_do_przemieszczenia->set_zaznaczona(false);
        gra->postac_do_przemieszczenia=NULL;
        gra->usun_kolka();
        gra->lista_mozliwych_ruchow.clear();
        gra->usun_kolka_ataku();
        gra->lista_mozliwych_atakow.clear();

    }
    else if(get_wlasciciel()!=gra->get_czyj_ruch() && gra->aktywna_postac!=NULL)
        if(gra->aktywna_postac->get_czy_atakowal()==false)
        for (int i=0;i<gra->get_lista_mozliwych_atakow().size();i++)
            if(this->get_pozycja_jednostki()==gra->get_lista_mozliwych_atakow().at(i))
                atak(this);
}

void Postac::sprawdz_czy_zyje()
{
    if(get_zycie()<=0)
    {
        gra->stara_pozycja=this->get_pozycja_jednostki();
        gra->zwolnij_podloze();
        if(get_wlasciciel()=="NIEBIESKI")
        {
            for(int i=0;i<gra->get_jednostki_niebieskie().size();i++)
            {
                if(gra->get_jednostki_niebieskie().at(i)==this)
                    delete gra->get_jednostki_niebieskie().at(i);
            }
        }
        else
        {
            for(int i=0;i<gra->get_jednostki_czerwone().size();i++)
            {
                if(gra->get_jednostki_czerwone().at(i)==this)
                    delete gra->get_jednostki_czerwone().at(i);

        }
        }
        gra->get_jednostki_czerwone().removeAll(this);
        gra->get_jednostki_niebieskie().removeAll(this);
        gra->scene->removeItem(this);
    }

}

void Postac::dodaj_pasek_zycia()
{
    zycie_text=new QGraphicsTextItem();
    QFont czcionka("Arial",11,QFont::Bold);
    zycie_text->setFont(czcionka);
    zycie_text->setDefaultTextColor(Qt::black);
    zycie_text->setPlainText(QString::number(get_zycie()));
    zycie_text->setPos(get_pozycja_jednostki().x()*50-10,get_pozycja_jednostki().y()*50-10);
    gra->scene->addItem(zycie_text);
}

void Postac::aktualizacja_paska_zycia()
{
    zycie_text->setPlainText(QString::number(get_zycie()));
    zycie_text->setPos(get_pozycja_jednostki().x()*50-10,get_pozycja_jednostki().y()*50-10);
    if(get_zycie()<=0)
        gra->scene->removeItem(zycie_text);
}


void Postac::set_zycie(int hp)
{
    zycie=hp;
}

void Postac::set_max_atak(int max_attack)
{
    max_atak=max_attack;
}

void Postac::set_min_atak(int min_attack)
{
    min_atak=min_attack;
}

void Postac::set_obrona(int shield)
{
    obrona=shield;
}

void Postac::set_obrona_aktualna(int shield)
{
    obrona_aktualna=shield;
}

void Postac::set_zasieg_ruchu(int range_m)
{
    zasieg_ruchu=range_m;
}

void Postac::set_zasieg_ataku(int range_a)
{
    zasieg_ataku=range_a;
}

void Postac::set_wlasciciel(QString owner)
{
    wlasciciel=owner;
}

void Postac::set_pozycja_jednostki(int x, int y)
{
    pozycja_jednostki.setX(x/50);
    pozycja_jednostki.setY(y/50);
}

void Postac::set_zaznaczona(bool x)
{
    zaznaczona=x;
}

void Postac::set_czy_sie_ruszyl(bool x)
{
    czy_sie_ruszyl=x;
}

void Postac::set_czy_atakowal(bool x)
{
    czy_atakowal=x;
}

int Postac::get_zycie()
{
    return zycie;
}

int Postac::get_max_atak()
{
    return max_atak;
}

int Postac::get_min_atak()
{
    return min_atak;
}

int Postac::get_obrona()
{
    return obrona;
}

int Postac::get_obrona_aktualna()
{
    return obrona_aktualna;
}

int Postac::get_zasieg_ruchu()
{
    return zasieg_ruchu;
}

int Postac::get_zasieg_ataku()
{
    return zasieg_ataku;
}

QString Postac::get_wlasciciel()
{
    return wlasciciel;
}

QPoint Postac::get_pozycja_jednostki()
{
    return pozycja_jednostki;
}

bool Postac::get_zaznaczona()
{
    return zaznaczona;
}

bool Postac::get_czy_sie_ruszyl()
{
    return czy_sie_ruszyl;
}

bool Postac::get_czy_atakowal()
{
    return czy_atakowal;
}
