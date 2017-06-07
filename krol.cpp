#include "krol.h"
#include "gra.h"

extern Gra* gra;


Krol::Krol(QString owner, int hp, int max_dam, int min_dam, int shield, int move_range, int attack_range)
{
    set_zycie(hp);
    set_max_atak(max_dam);
    set_min_atak(min_dam);
    set_obrona(shield);
    set_obrona_aktualna(shield);
    set_zasieg_ruchu(move_range);
    set_zasieg_ataku(attack_range);
    set_wlasciciel(owner);

    if (owner==QString("CZERWONY"))
    setPixmap(QPixmap(":/obrazki/img/czerwony_krol1.png"));
    else
    setPixmap(QPixmap(":/obrazki/img/niebieski_krol1.png"));


}

void Krol::sprawdz_czy_zyje()
{
    if(get_zycie()<=0)
    {
        gra->stara_pozycja=this->get_pozycja_jednostki();
        gra->zwolnij_podloze();
        gra->get_jednostki_czerwone().removeAll(this);
        gra->get_jednostki_niebieskie().removeAll(this);
        gra->koniec_gry();
        delete this;
    }

}
