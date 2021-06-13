#include "Wirnik.h"

Wirnik::Wirnik(double promien, double wysokosc, std::string _kolor) {
    ustawPodstawy(promien, wysokosc);
    ustawLinie(promien, wysokosc);
    ustawBoki(promien, wysokosc);

    kolor = _kolor;
    srodek_symetrii = Wektor<WEKTOR3D>({0, wysokosc / 2, 0});
    ustawKolor(_kolor);
}

void Wirnik::rysowanie() {
    for (int i = 0; i < SZESCIOKATNY; ++i) {
        boki[i].rysowanie();
        linie[i].rysowanie();
    }

}

void Wirnik::translacja(Wektor<WEKTOR3D> wektorTranslacji) {
    srodek_symetrii = srodek_symetrii + wektorTranslacji;
    for (int i = 0; i < ILOSC_PODSTAW; ++i) {
        podstawy[i].translacja(wektorTranslacji);
    }

    for (int i = 0; i < SZESCIOKATNY; ++i) {
        boki[i].translacja(wektorTranslacji);
        linie[i].translacja(wektorTranslacji);
    }
}

void Wirnik::obrotGlowny(double kat, char os) {
    MacierzObrotu<3> macierzObrotu(kat, os);
    srodek_symetrii = macierzObrotu * srodek_symetrii;
    for (int i = 0; i < ILOSC_PODSTAW; ++i) {
        podstawy[i].obrotGlowny(kat, os);
    }

    for (int i = 0; i < SZESCIOKATNY; ++i) {
        boki[i].obrotGlowny(kat, os);
        linie[i].obrotGlowny(kat, os);
    }
}

void Wirnik::obrotWlasny(double kat, char os) {
    Wektor<WEKTOR3D> tmp = srodek_symetrii * -1;
    translacja(tmp);
    obrotGlowny(kat, os);
    translacja(tmp * -1);
}

void Wirnik::ustawKolor(std::string _kolor) {
    kolor = _kolor;
    for (int i = 0; i < ILOSC_PODSTAW; ++i) {
        podstawy[i].ustawKolor(kolor);
    }

    for (int i = 0; i < SZESCIOKATNY; ++i) {
        boki[i].ustawKolor(kolor);
    }
}

void Wirnik::ustawPodstawy(double promien, double wysokosc) {
    podstawy[0] = Wielokat<SZESCIOKATNY>(promien);
    podstawy[1] = Wielokat<SZESCIOKATNY>(promien);
    podstawy[1].translacja(Wektor<WEKTOR3D>({0, wysokosc, 0}));
}

void Wirnik::ustawBoki(double promien, double wysokosc) {
    for (int i = 0; i < SZESCIOKATNY - 1; ++i) {
        boki[i] = Wielokat<ILOSC_KATOW>
                ({podstawy[0][i], podstawy[0][i+1], podstawy[1][i+1], podstawy[1][i]}, kolor);
    }
    boki[5] = Wielokat<ILOSC_KATOW>({podstawy[0][5], podstawy[0][0], podstawy[1][0], podstawy[1][5]}, kolor);
}

void Wirnik::ustawLinie(double promien, double wysokosc) {
    for (int i = 0; i < SZESCIOKATNY; ++i) {
        linie[i] = Wielokat<LINIA>(promien);
    }
    linie[1].obrotGlowny(60, 'y');
    linie[2].obrotGlowny(120, 'y');
    linie[4].obrotGlowny(60, 'y');
    linie[5].obrotGlowny(120, 'y');

    linie[3].translacja(Wektor<WEKTOR3D>({0, wysokosc, 0}));
    linie[4].translacja(Wektor<WEKTOR3D>({0, wysokosc, 0}));
    linie[5].translacja(Wektor<WEKTOR3D>({0, wysokosc, 0}));
}


