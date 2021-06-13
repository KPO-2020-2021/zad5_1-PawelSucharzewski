#pragma once

#include "Wielokat.h"

const int SZESCIOKATNY = 6;
const int ILOSC_PODSTAW = 2;

class Wirnik : public Obiekt{
private:
    std::array<Wielokat<SZESCIOKATNY>, ILOSC_PODSTAW> podstawy;
    std::array<Wielokat<ILOSC_KATOW>, SZESCIOKATNY> boki;
    std::array<Wielokat<LINIA>, SZESCIOKATNY> linie;

    void ustawPodstawy(double promien, double wysokosc);

    void ustawBoki(double promien, double wysokosc);

    void ustawLinie(double promien, double wysokosc);
public:
    Wirnik(double promien, double wysokosc, std::string _kolor = KOLOR);

    void rysowanie() override;

    void translacja(Wektor<WEKTOR3D> wektorTranslacji) override;

    void obrotGlowny(double kat, char os) override;

    void obrotWlasny(double kat, char os) override;

    void ustawKolor(std::string _kolor) override;
};
