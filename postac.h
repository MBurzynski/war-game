#ifndef POSTAC_H
#define POSTAC_H


#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

class Postac : public QGraphicsPixmapItem
{
public:

    void mozliwe_ruchy();
    void mozliwy_atak();
    void atak(Postac* kogo);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void sprawdz_czy_zyje();
    void dodaj_pasek_zycia();
    void aktualizacja_paska_zycia();


    void set_zycie(int hp);
    void set_max_atak(int max_attack);
    void set_min_atak(int min_attack);
    void set_obrona(int shield);
    void set_obrona_aktualna(int shield);
    void set_zasieg_ruchu(int range_m);
    void set_zasieg_ataku(int range_a);
    void set_wlasciciel(QString owner);
    void set_pozycja_jednostki(int x, int y);
    void set_zaznaczona(bool x);
    void set_czy_sie_ruszyl(bool x);
    void set_czy_atakowal(bool x);


    int get_zycie();
    int get_max_atak();
    int get_min_atak();
    int get_obrona();
    int get_obrona_aktualna();
    int get_zasieg_ruchu();
    int get_zasieg_ataku();
    QString get_wlasciciel();
    QPoint get_pozycja_jednostki();
    bool get_zaznaczona();
    bool get_czy_sie_ruszyl();
    bool get_czy_atakowal();


private:
    int zycie;
    int max_atak;
    int min_atak;
    int obrona;
    int obrona_aktualna;
    int zasieg_ruchu;
    int zasieg_ataku;
    QString wlasciciel;
    QPoint pozycja_jednostki;
    bool zaznaczona;
    bool czy_sie_ruszyl;
    bool czy_atakowal;
    QGraphicsTextItem* zycie_text;
};

#endif // POSTAC_H
