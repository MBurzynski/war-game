#ifndef ZOLNIERZ_H
#define ZOLNIERZ_H

#include "postac.h"

class Zolnierz : public Postac
{
public:
    Zolnierz(QString owner, int hp=60, int max_dam=24, int min_dam=18, int shield=5, int move_range=2, int attack_range=1);

};

#endif // ZOLNIERZ_H
