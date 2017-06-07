#include "lucznik.h"

Lucznik::Lucznik(QString owner, int hp, int max_dam, int min_dam, int shield, int move_range, int attack_range)
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
    setPixmap(QPixmap(":/obrazki/img/czerwony_lucznik1.png"));
    else
    setPixmap(QPixmap(":/obrazki/img/niebieski_lucznik1.png"));
}
