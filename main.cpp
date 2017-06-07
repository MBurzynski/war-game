#include <QApplication>
#include <stdlib.h>
#include <time.h>
#include "gra.h"

Gra* gra;
Plansza* plansza;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    srand(time(NULL));

    gra=new Gra;
    gra->show();
    gra->menu();


    return a.exec();
}
