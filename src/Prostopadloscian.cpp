#include "Prostopadloscian.h"


Prostopadloscian::Prostopadloscian(double dlugosc, double wysokosc, double szerokosc, std::string kolor) {
    Wektor<WEKTOR3D> v({dlugosc, 0, 0});
    Wektor<WEKTOR3D> r({0, wysokosc, 0});
    Wektor<WEKTOR3D> w({0, 0, szerokosc});

    sciany[0] = Wielokat<ILOSC_KATOW>(v, w, Wektor<WEKTOR3D>());
    sciany[1] = Wielokat<ILOSC_KATOW>(w, v, r);
    sciany[2] = Wielokat<ILOSC_KATOW>(r, w, Wektor<WEKTOR3D>());
    sciany[3] = Wielokat<ILOSC_KATOW>(r, v, w);
    sciany[4] = Wielokat<ILOSC_KATOW>(r, w, v);
    sciany[5] = Wielokat<ILOSC_KATOW>(r, v, Wektor<WEKTOR3D>());

    srodek_symetrii = Wektor({dlugosc / 2, wysokosc/ 2,  szerokosc / 2});
    translacja(srodek_symetrii * -1);
    ustawKolor(kolor);

}


void Prostopadloscian::rysowanie() {
    for (int i = 0; i < ILOSC_SCIAN; ++i) {
        sciany[i].rysowanie();
    }
}

void Prostopadloscian::translacja(Wektor<WEKTOR3D> wektorTranslacji) {
    for (int i = 0; i < ILOSC_SCIAN; ++i) {
        sciany[i].translacja(wektorTranslacji);
    }
}

void Prostopadloscian::obrotGlowny(double kat, char os) {
    for (int i = 0; i < ILOSC_SCIAN; ++i) {
        sciany[i].obrotGlowny(kat, os);
    }
}

void Prostopadloscian::obrotWlasny(double kat, char os) {
    Wektor tmp = srodek_symetrii * -1;
    translacja(tmp);
    obrotGlowny(kat, os);
    translacja(tmp * -1);
}

void Prostopadloscian::ustawKolor(std::string _kolor) {
    for (int i = 0; i < ILOSC_SCIAN; ++i) {
        sciany[i].ustawKolor(_kolor);
    }
}

const Wielokat<ILOSC_KATOW> &Prostopadloscian::operator[](int index) const {
    return sciany[index];
}

Wielokat<ILOSC_KATOW> &Prostopadloscian::operator[](int index) {
    return sciany[index];
}

Wektor<WEKTOR3D> Prostopadloscian::wezSrodekSymetrii() {
    return srodek_symetrii;
}

void Prostopadloscian::usunObiekt() {
    for (int i = 0; i < ILOSC_SCIAN; ++i) {
        sciany[i].usunObiekt();
    }
}

