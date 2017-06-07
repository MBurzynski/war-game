#ifndef GRA_H
#define GRA_H

#include<QGraphicsView>
#include <QGraphicsTextItem>
#include "plansza.h"
#include "przycisk.h"
#include "postac.h"
#include "zolnierz.h"
#include "lucznik.h"
#include "krol.h"

class Gra : public QGraphicsView
{
    Q_OBJECT
public:
    // Konstruktor
    Gra(QWidget* parent=NULL);

    QGraphicsScene* scene;
    Postac* postac_do_przemieszczenia;
    Postac* aktywna_postac;
    QList<QPoint> lista_mozliwych_ruchow;
    QList<QPoint> lista_mozliwych_atakow;
    QList<QGraphicsEllipseItem*> lista_kolek;
    QList<QGraphicsEllipseItem*> lista_kolek_ataku;
    QPoint stara_pozycja;
    Postac* postac;

    QString get_czyj_ruch();
    QList<Postac*> get_jednostki_czerwone();
    QList<Postac*> get_jednostki_niebieskie();
    QList<QPoint> get_lista_mozliwych_ruchow();
    QList<QPoint> get_lista_mozliwych_atakow();

    void zaznacz_postac(Postac* aktualna);
    void przesun_postac(Podloze* wybrane_miejsce);
    void usun_kolka();
    void usun_kolka_ataku();
    void zwolnij_podloze();


    void set_czyj_ruch(QString gracz);

    void menu();
    void dodaj_jednostke(QString wlasciciel, QString rodzaj, int x, int y);
    void stworz_wojsko(QString wlasciciel, int rzad);
    void koniec_gry();
    void ekran_koncowy(QString informacja);

public slots:
        void nowaGra();
        void zakonczTure();
        void restart();

private:
        void panel_gry();
        void panel_standard(int x, int y, int szer, int wys, QColor kolor, double przezroczystosc);
        QString czyj_ruch;
        QGraphicsTextItem* czyj_ruch_text;
        QList<Postac*> jednostki_czerwone;
        QList<Postac*> jednostki_niebieskie;



};

#endif // GRA_H
