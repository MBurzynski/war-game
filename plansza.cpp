#include "plansza.h"
#include "gra.h"

extern Gra* gra;

Plansza::Plansza()
{

}

QList<Podloze *> Plansza::get_podloze()
{
    return lista_podloza;

}



void Plansza::rysuj_plansze()
{


    int mapa[16*14]={
        3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,1,0,1,0,1,0,0,1,0,1,0,1,2,2,
        2,2,1,0,1,0,1,0,0,1,0,1,0,1,2,2,
        2,2,1,0,0,0,1,0,0,1,0,0,0,1,2,2,
        2,2,1,1,0,1,1,0,0,1,1,0,1,1,2,2,
        2,2,2,2,0,0,0,0,0,0,0,0,2,2,2,2,
        3,3,3,3,3,3,3,0,0,3,3,3,3,3,3,3,
        3,3,3,3,3,3,3,0,0,3,3,3,3,3,3,3,
        2,2,2,2,0,0,0,0,0,0,0,0,2,2,2,2,
        2,2,1,1,0,1,1,0,0,1,1,0,1,1,2,2,
        2,2,1,0,0,0,1,0,0,1,0,0,0,1,2,2,
        2,2,1,0,1,0,1,0,0,1,0,1,0,1,2,2,
        2,2,1,0,1,0,1,0,0,1,0,1,0,1,2,2,
        3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
    };

    for(int i=0;i<16*14;i++)
    {
        Podloze* podloze;

        switch(mapa[i])
        {
        case 0:
            podloze=new Podloze("droga");

            break;
        case 1:
            podloze=new Podloze("trawa");
            break;
        case 2:
            podloze=new Podloze("las");
            break;
        case 3:
            podloze=new Podloze("gora");
            break;
        }
        podloze->setPos((i%16)*50,(i/16)*50);
        podloze->set_pozycja_podloza(i%16,i/16);
        podloze->zajety=0;
        lista_podloza.append(podloze);
        gra->scene->addItem(podloze);
    }

}
