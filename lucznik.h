#ifndef LUCZNIK_H
#define LUCZNIK_H

#include "postac.h"

class Lucznik : public Postac
{
public:
    Lucznik(QString owner, int hp=40, int max_dam=25, int min_dam=20, int shield=0, int move_range=3, int attack_range=2);
};

#endif // LUCZNIK_H
