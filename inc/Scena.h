#pragma once

#include "Dron.h"

const int ILOSC_LINII = 3;

struct Komenda{
    char znak;
    double wartosc;
};

class Scena {
private:
    std::vector<Dron> drony;
    std::vector<Komenda> komendy;
    std::vector<Obiekt *> elementyTerenu;
    std::array<Wielokat<LINIA>, ILOSC_LINII> trasa;
    int numerDrona;

    void animacja();
    void narysujTrase();
    bool translacjaWykonana();
    void wystartuj();
    void obrot();
    void przesun();
    void ladowanie();
public:
    Scena();

    void wybierzDrona();
    void rysuj();
    void lot();
    void wyswietlAktywnegoDrona();

};