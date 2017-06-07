#ifndef KROL_H
#define KROL_H

#include "postac.h"



class Krol : public Postac
{
public:
    Krol(QString owner, int hp=100, int max_dam=40, int min_dam=25, int shield=10, int move_range=3, int attack_range=1);
    virtual void sprawdz_czy_zyje();
};

#endif // KROL_H
