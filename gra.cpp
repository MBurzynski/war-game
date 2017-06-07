#include "gra.h"
#include "plansza.h"
#include "podloze.h"

extern Gra* gra;
extern Plansza* plansza;

Gra::Gra(QWidget *parent)
{
    //Ustawienie ekranu
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,800);

    //Ustawienie sceny
    scene= new QGraphicsScene();
    scene->setSceneRect(0,0,800,800);
    setScene(scene);

    postac_do_przemieszczenia=NULL;
    aktywna_postac=NULL;
}

void Gra::nowaGra()
{
    scene->clear();

    plansza = new Plansza();
    plansza->rysuj_plansze();
    stworz_wojsko("NIEBIESKI",1);
    stworz_wojsko("CZERWONY",12);
    panel_gry();
}

void Gra::panel_standard(int x, int y, int szer, int wys, QColor kolor, double przezroczystosc)
{
    QGraphicsRectItem* panel= new QGraphicsRectItem(x,y,szer,wys);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(kolor);
    panel->setBrush(brush);
    panel->setOpacity(przezroczystosc);
    scene->addItem(panel);
}


void Gra::panel_gry()
{
    panel_standard(0,scene->height()-100,scene->width(),100,Qt::lightGray,1);

    czyj_ruch_text=new QGraphicsTextItem();
    set_czyj_ruch(QString("NIEBIESKI"));
    czyj_ruch_text->setPos(30,730);
    scene->addItem(czyj_ruch_text);

    Przycisk* zakoncz_ture = new Przycisk(QString("Zakoncz ture"));
    int zx= scene->width()-220;
    int zy= scene->height()-80;
    zakoncz_ture->setPos(zx,zy);
    connect(zakoncz_ture,SIGNAL(clicked()),this,SLOT(zakonczTure()));
    scene->addItem(zakoncz_ture);

}

void Gra::menu()
{
    QGraphicsTextItem* tytul=new QGraphicsTextItem(QString("Wojna"));
    QFont czcionka("Times", 50);
    tytul->setFont(czcionka);
    int tx= this->width()/2-tytul->boundingRect().width()/2;
    int ty= 100;
    tytul->setPos(tx,ty);
    scene->addItem(tytul);

    Przycisk* graj = new Przycisk(QString("Nowa gra"));
    int by= 300;
    graj->setPos(tx,by);
    connect(graj,SIGNAL(clicked()),this,SLOT(nowaGra()));
    scene->addItem(graj);

    Przycisk* wyjdz = new Przycisk(QString("Wyjdz"));
    int wy= 400;
    wyjdz->setPos(tx,wy);
    connect(wyjdz,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(wyjdz);

}



QString Gra::get_czyj_ruch()
{
    return czyj_ruch;

}

QList<Postac *> Gra::get_jednostki_czerwone()
{
    return jednostki_czerwone;

}

QList<Postac *> Gra::get_jednostki_niebieskie()
{
    return jednostki_niebieskie;
}

QList<QPoint> Gra::get_lista_mozliwych_ruchow()
{
    return lista_mozliwych_ruchow;
}

QList<QPoint> Gra::get_lista_mozliwych_atakow()
{
    return lista_mozliwych_atakow;
}


void Gra::zaznacz_postac(Postac *aktualna)
{
    if(aktualna->get_wlasciciel()==get_czyj_ruch() && postac_do_przemieszczenia==NULL && aktualna->get_czy_sie_ruszyl()==0)
    {
        postac_do_przemieszczenia=aktualna;
        aktywna_postac=aktualna;
        postac_do_przemieszczenia->set_zaznaczona(true);
        stara_pozycja=postac_do_przemieszczenia->get_pozycja_jednostki();
        return;
    }
}


void Gra::przesun_postac(Podloze *wybrane_miejsce)
{
    if(postac_do_przemieszczenia->get_czy_sie_ruszyl()==false)
    {
        if(get_czyj_ruch()==QString("NIEBIESKI"))
        {
            postac_do_przemieszczenia->setPos(wybrane_miejsce->pos());
            postac_do_przemieszczenia->set_zaznaczona(false);
            postac_do_przemieszczenia->set_czy_sie_ruszyl(true);
            postac_do_przemieszczenia->set_pozycja_jednostki(wybrane_miejsce->get_pozycja_podloza().x()*50,wybrane_miejsce->get_pozycja_podloza().y()*50);
        }
        else
        {
            postac_do_przemieszczenia->setPos(wybrane_miejsce->pos());
            postac_do_przemieszczenia->set_zaznaczona(false);
            postac_do_przemieszczenia->set_czy_sie_ruszyl(true);
            postac_do_przemieszczenia->set_pozycja_jednostki(wybrane_miejsce->get_pozycja_podloza().x()*50,wybrane_miejsce->get_pozycja_podloza().y()*50);
        }

    postac_do_przemieszczenia->set_obrona_aktualna(postac_do_przemieszczenia->get_obrona());
    wybrane_miejsce->dodaj_obrone(postac_do_przemieszczenia);
    gra->lista_mozliwych_atakow.clear();
    gra->usun_kolka_ataku();
    postac_do_przemieszczenia->mozliwy_atak();
    postac_do_przemieszczenia->aktualizacja_paska_zycia();
    postac_do_przemieszczenia=NULL;
    gra->lista_mozliwych_ruchow.clear();
    gra->usun_kolka();

    wybrane_miejsce->zajety=true;
    }
}

void Gra::usun_kolka()
{
    //Usuwanie kolek z ekranu
    for(int i=0;i<lista_kolek.size();i++)
    {
        gra->scene->removeItem(lista_kolek.at(i));
    }
    gra->lista_kolek.clear();
}

void Gra::usun_kolka_ataku()
{
    for(int i=0;i<lista_kolek_ataku.size();i++)
    {
        gra->scene->removeItem(lista_kolek_ataku.at(i));
    }
    gra->lista_kolek_ataku.clear();
}

void Gra::zwolnij_podloze()
{
    for(int i=0;i<plansza->get_podloze().size();i++)
    {
        if(stara_pozycja==plansza->get_podloze().at(i)->get_pozycja_podloza())
        {
            plansza->get_podloze().at(i)->zajety=false;
        }
    }
}

void Gra::set_czyj_ruch(QString gracz)
{
    czyj_ruch=gracz;
    czyj_ruch_text->setPlainText(QString("Ruch gracza: ") + gracz);

}

void Gra::dodaj_jednostke(QString wlasciciel, QString rodzaj,int x, int y)
{
    if(rodzaj==QString("Zolnierz"))
        postac=new Zolnierz(wlasciciel);
    else if(rodzaj==QString("Lucznik"))
        postac=new Lucznik(wlasciciel);
    else if(rodzaj==QString("Krol"))
        postac=new Krol(wlasciciel);

    postac->setPos(x,y);
    postac->set_pozycja_jednostki(x,y);
    postac->dodaj_pasek_zycia();
    plansza->get_podloze().at((x/50)%16+(y/50)*16)->zajety=1;


    if(wlasciciel==QString("NIEBIESKI"))
        jednostki_niebieskie.append(postac);
    else
        jednostki_czerwone.append(postac);

    gra->scene->addItem(postac);

}


void Gra::stworz_wojsko(QString wlasciciel, int rzad)
{
    for (int i=1;i<5;i++)
    {
        dodaj_jednostke(wlasciciel,QString("Zolnierz"),i*50,rzad*50);
    }
    for (int i=5;i<7;i++)
    {
        dodaj_jednostke(wlasciciel,QString("Lucznik"),i*50,rzad*50);
    }
    //Stworzenie króla
    dodaj_jednostke(wlasciciel,QString("Krol"),7*50,rzad*50);

    for (int i=8;i<10;i++)
    {
    dodaj_jednostke(wlasciciel,QString("Lucznik"),i*50,rzad*50);
    }
    for (int i=10;i<14;i++)
    {
    dodaj_jednostke(wlasciciel,QString("Zolnierz"),i*50,rzad*50);
    }

    if(wlasciciel==QString("NIEBIESKI"))
        for(int i=0; i<get_jednostki_niebieskie().size();i++)
            get_jednostki_niebieskie().at(i)->set_czy_sie_ruszyl(false);
    else if(wlasciciel==QString("CZERWONY"))
        for(int i=0; i<get_jednostki_czerwone().size();i++)
            get_jednostki_czerwone().at(i)->set_czy_sie_ruszyl(false);
}



void Gra::koniec_gry()
{
    QString kto_wygral;

    if(get_czyj_ruch()==QString("NIEBIESKI"))
        kto_wygral="Gracz Niebieski wygral!";
    else
        kto_wygral="Gracz Czerwony wygral!";
    ekran_koncowy(kto_wygral);
}

void Gra::ekran_koncowy(QString informacja)
{
    for(int i=0;i<scene->items().size();i++)
    {
        scene->items()[i]->setEnabled(false);
    }

    panel_standard(0,0,scene->width(),scene->height(),Qt::black,0.6);

    panel_standard(scene->width()/2-200,scene->height()/2-200,400,400,Qt::lightGray,0.75);

    Przycisk* Restart= new Przycisk(QString("Zagraj jeszcze raz"));
    Restart->setPos(scene->width()/2-100,scene->height()/2-100);
    scene->addItem(Restart);
    connect(Restart,SIGNAL(clicked()),this,SLOT(restart()));

    Przycisk* Zamknij=new Przycisk(QString("Zakończ"));
    Zamknij->setPos(scene->width()/2-100,scene->height()/2);
    scene->addItem(Zamknij);
    connect(Zamknij,SIGNAL(clicked()),this,SLOT(close()));

    QGraphicsTextItem* napis=new QGraphicsTextItem(informacja);
    napis->setPos(scene->width()/2-napis->boundingRect().width()/2,scene->height()/2-180);
    scene->addItem(napis);

}

void Gra::zakonczTure()
{
    QString aktualny_gracz=get_czyj_ruch();

    if(aktualny_gracz=="NIEBIESKI")
    {
        set_czyj_ruch("CZERWONY");
    }
    else if(aktualny_gracz=="CZERWONY")
    {
        set_czyj_ruch("NIEBIESKI");
    }
    for(int i=0; i<get_jednostki_czerwone().size();i++)
    {
        get_jednostki_czerwone().at(i)->set_czy_sie_ruszyl(false);
        get_jednostki_czerwone().at(i)->set_czy_atakowal(false);
    }

    for(int i=0; i<get_jednostki_niebieskie().size();i++)
    {
        get_jednostki_niebieskie().at(i)->set_czy_sie_ruszyl(false);
        get_jednostki_niebieskie().at(i)->set_czy_atakowal(false);
    }

    gra->lista_mozliwych_ruchow.clear();
    gra->usun_kolka();
    gra->usun_kolka_ataku();
    gra->lista_mozliwych_atakow.clear();
    postac_do_przemieszczenia=NULL;

}

void Gra::restart()
{
    lista_mozliwych_atakow.clear();
    lista_mozliwych_ruchow.clear();
    lista_kolek.clear();
    lista_kolek_ataku.clear();
    jednostki_czerwone.clear();
    jednostki_niebieskie.clear();
    scene->clear();
    nowaGra();

}

