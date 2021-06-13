#include "Dron.h"

Dron::Dron(double _skala, Wektor<WEKTOR3D> wektorPoczatkowy) {
    orientacja = Wektor<WEKTOR3D>();
    predkoscWirnikow = 0;
    predkoscWznoszenia = 0;
    predkoscObrotu = 0;
    predkoscLotu = 0;
    skala = _skala;

    ustawKorpusy();
    ustawWirniki();

    translacja(0, (SZEROKOSC * skala) / 2, 0);

    srodek_symetrii = Wektor<WEKTOR3D>();
    translacja(wektorPoczatkowy);
    translacjaCalkowita = Wektor<WEKTOR3D>();
}

void Dron::rysowanie() {
    for (int i = 0; i < korpusy.size(); ++i) {
        korpusy[i].rysowanie();
    }

    for (int i = 0; i < wirniki.size(); ++i) {
        wirniki[i].rysowanie();
    }
}

void Dron::ustawKorpusy(double dlugosc, double szerokosc) {
    dlugosc *= skala;
    szerokosc *= skala;

    korpusy.push_back(Prostopadloscian(dlugosc, szerokosc, szerokosc));

    korpusy.push_back(Prostopadloscian(dlugosc - 0.1 * dlugosc, 0.1 * dlugosc,
                                       0.1 * dlugosc));

    korpusy.push_back(Prostopadloscian(dlugosc - 0.1 * dlugosc, 0.1 * dlugosc,
                                       0.1 * dlugosc));
    korpusy[1].obrotGlowny(90, 'y');
    korpusy[1].translacja(Wektor<3>({(dlugosc - 0.1 * dlugosc) / 3, 0, 0}));
    korpusy[2].obrotGlowny(90, 'y');
    korpusy[2].translacja(Wektor<3>({-(dlugosc - 0.1 * dlugosc) / 3, 0, 0}));
}

void Dron::ustawWirniki(double dlugosc, double szerokosc) {
    dlugosc *= skala;
    szerokosc *= skala;
    double promien = szerokosc - 0.1 * szerokosc;
    double wysokosc = 0.1 * dlugosc;

    wirniki.push_back(Wirnik(promien, wysokosc));
    wirniki.push_back(Wirnik(promien, wysokosc));
    wirniki.push_back(Wirnik(promien, wysokosc));
    wirniki.push_back(Wirnik(promien, wysokosc));

    wirniki[0].translacja(
            Wektor<3>({(dlugosc - 0.1 * dlugosc) / 3, 0.1 * dlugosc / 2, (dlugosc - 0.1 * dlugosc) / 2 - promien / 4}));
    wirniki[1].translacja(Wektor<3>(
            {(dlugosc - 0.1 * dlugosc) / 3, 0.1 * dlugosc / 2, -(dlugosc - 0.1 * dlugosc) / 2 + promien / 4}));
    wirniki[2].translacja(Wektor<3>(
            {-(dlugosc - 0.1 * dlugosc) / 3, 0.1 * dlugosc / 2, (dlugosc - 0.1 * dlugosc) / 2 - promien / 4}));
    wirniki[3].translacja(Wektor<3>(
            {-(dlugosc - 0.1 * dlugosc) / 3, 0.1 * dlugosc / 2, -(dlugosc - 0.1 * dlugosc) / 2 + promien / 4}));
}

void Dron::translacja(Wektor<WEKTOR3D> wektorTranslacji) {
    srodek_symetrii = srodek_symetrii + wektorTranslacji;
    for (int i = 0; i < korpusy.size(); ++i) {
        korpusy[i].translacja(wektorTranslacji);
    }

    for (int i = 0; i < wirniki.size(); ++i) {
        wirniki[i].translacja(wektorTranslacji);
    }
}

void Dron::translacja(double x, double y, double z) {
    translacja(Wektor<WEKTOR3D>({x, y, z}));
}

void Dron::rotacjaWirnikow(double predkosc) {
    wirniki[0].obrotWlasny(-predkosc, 'y');
    wirniki[1].obrotWlasny(predkosc, 'y');
    wirniki[2].obrotWlasny(predkosc, 'y');
    wirniki[3].obrotWlasny(-predkosc, 'y');
}


void Dron::ustawKolor(std::string _kolor) {
    kolor = _kolor;
    for (int i = 0; i < korpusy.size(); ++i) {
        korpusy[i].ustawKolor(kolor);
    }

    for (int i = 0; i < wirniki.size(); ++i) {
        wirniki[i].ustawKolor(kolor);
    }
}

void Dron::obrotGlowny(double kat, char os) {
    MacierzObrotu<3> macierzObrotu(kat, os);
    srodek_symetrii = macierzObrotu * srodek_symetrii;

    for (int i = 0; i < korpusy.size(); ++i) {
        korpusy[i].obrotGlowny(kat, os);
    }
    for (int i = 0; i < wirniki.size(); ++i) {
        wirniki[i].obrotGlowny(kat, os);
    }

    switch (os) {
        case 'x':
            orientacja[0] += kat;
            break;
        case 'y':
            orientacja[1] += kat;
            break;
        case 'z':
            orientacja[2] += kat;
            break;
        default:
            break;
    }
}

void Dron::obrotWlasny(double kat, char os) {
    Wektor<3> tmp = srodek_symetrii * -1;
    translacja(tmp);
    obrotGlowny(kat, os);
    translacja(tmp * -1);
}

void Dron::wznoszenie(double wysokosc) {
    if (predkoscWirnikow < 15) predkoscWirnikow += 0.1;
    if (predkoscWirnikow > 12) predkoscWznoszenia += 0.075;
    if (srodek_symetrii[1] >= wysokosc) {
        predkoscWznoszenia = 0;
    }
    rotacjaWirnikow(predkoscWirnikow);
    translacja(0, predkoscWznoszenia, 0);
}


void Dron::ladowanie() {
    if (predkoscWirnikow > 12) predkoscWirnikow -= 0.1;
    if (predkoscWirnikow < 13) predkoscWznoszenia += 0.05;
    if (srodek_symetrii[1] <= 0) {
        predkoscWznoszenia = 0;
    }
    rotacjaWirnikow(predkoscWirnikow);
    translacja(0, -predkoscWznoszenia, 0);
}

void Dron::obracanie(double kat) {
    if (predkoscObrotu == 0 && kat > 0) predkoscObrotu = 0.5;
    else if (predkoscObrotu == 0 && kat < 0) predkoscObrotu = -0.5;

    if (kat >= 0 && orientacja[1] >= kat) {
        predkoscObrotu = 0;
    } else if (kat < 0 && orientacja[1] <= kat) {
        predkoscObrotu = 0;
    }

    rotacjaWirnikow(predkoscWirnikow);
    obrotWlasny(predkoscObrotu, 'y');
}

void Dron::lot() {
    rotacjaWirnikow(predkoscWirnikow);
    if (predkoscLotu < 5) predkoscLotu += 0.025;
    Wektor<WEKTOR3D> tmp = policzTrase(predkoscLotu);
    translacja(tmp);
    translacjaCalkowita = translacjaCalkowita + tmp;
}

Wektor<WEKTOR3D> Dron::policzTrase(double odleglosc, Wektor<WEKTOR3D> _orientacja) {
    Wektor tmp = _orientacja + orientacjaCalkowita;
    MacierzObrotu<3> obrot(tmp[0], 'x');
    Wektor<WEKTOR3D> trasa({odleglosc, 0, 0});
    obrot = obrot * MacierzObrotu<3>(tmp[1], 'y');
    obrot = obrot * MacierzObrotu<3>(tmp[2], 'z');
    trasa = obrot * trasa;
    return trasa;
}

Wektor<WEKTOR3D> Dron::wezTranslacjeCalkowita() {
    return translacjaCalkowita;
}

std::string Dron::wezKolor() {
    return kolor;
}

void Dron::ustawOrientacje(Wektor<WEKTOR3D> arg) {
    orientacja = arg;
}

void Dron::ustawOrientacjeCalkowita(Wektor<WEKTOR3D> arg) {
    orientacjaCalkowita = arg;
}

Wektor<WEKTOR3D> Dron::wezOrientacjaCalkowita() {
    return orientacjaCalkowita;
}

void Dron::ustawTranslacjeCalkowita(Wektor<WEKTOR3D> arg) {
    translacjaCalkowita = arg;
}



double Dron::wezPredkoscWznoszenia() {
    return predkoscWznoszenia;
}

Wektor<WEKTOR3D> Dron::wezSrodekSymetrii() {
    return srodek_symetrii;
}

double Dron::wezPredkoscObrotu() {
    return predkoscObrotu;
}

Wektor<WEKTOR3D> Dron::wezOrientacje() {
    return orientacja;
}

