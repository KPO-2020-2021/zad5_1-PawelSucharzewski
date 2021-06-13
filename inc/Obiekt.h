#pragma once

#include "Wektor.h"
#include "Wykres.h"

class Obiekt {
protected:
    std::string id;
    double skala;
    std::string kolor;
    Wektor<WEKTOR3D> srodek_symetrii;
public:

    virtual void rysowanie() {}

    virtual void translacja(Wektor<WEKTOR3D> wektorTranslacji) {}

    virtual void obrotGlowny(double kat, char os) {}

    virtual void obrotWlasny(double kat, char os) {}

    virtual void ustawKolor(std::string _kolor) {}

    virtual void usunObiekt(){}

    virtual Wektor<WEKTOR3D> wezSrodekSymetrii(){return Wektor<WEKTOR3D>();}

};
