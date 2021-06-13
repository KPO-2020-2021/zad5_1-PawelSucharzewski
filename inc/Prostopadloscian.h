#pragma once

#include "Obiekt.h"
#include "Wielokat.h"

const int ILOSC_SCIAN = 6;

class Prostopadloscian : public Obiekt{
private:
    Prostopadloscian() = default;

    std::array<Wielokat<ILOSC_KATOW>, ILOSC_SCIAN> sciany;
public:
    Prostopadloscian(double dlugosc, double wysokosc, double szerokosc, std::string kolor = KOLOR);

    void rysowanie() override;

    void translacja(Wektor<WEKTOR3D> wektorTranslacji) override;

    void obrotGlowny(double kat, char os) override;

    void obrotWlasny(double kat, char os) override;

    void ustawKolor(std::string _kolor) override;

    const Wielokat<ILOSC_KATOW> &operator[](int index) const;

    void usunObiekt() override;

    Wektor<WEKTOR3D> wezSrodekSymetrii();

    Wielokat<ILOSC_KATOW> &operator[](int index);

};

