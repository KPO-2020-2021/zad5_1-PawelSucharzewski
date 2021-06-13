#pragma once

#include "Wirnik.h"
#include "Prostopadloscian.h"

const double DLUGOSC = 50;
const double SZEROKOSC = 12.5;

class Dron : public Obiekt {
private:
    /* wielkosci */
    /* calkowita to wielkosc ogolna, bez calkowita to wielkosc chwilowa (zmieniana) */
    std::vector<Wirnik> wirniki;
    std::vector<Prostopadloscian> korpusy;
    Wektor<WEKTOR3D> orientacja;
    Wektor<WEKTOR3D> orientacjaCalkowita;
    Wektor<WEKTOR3D> translacjaCalkowita;

    /* predkosci */
    double predkoscWznoszenia;
    double predkoscWirnikow;
    double predkoscObrotu;
    double predkoscLotu;

    void ustawKorpusy(double dlugosc = DLUGOSC, double szerokosc = SZEROKOSC);

    void ustawWirniki(double dlugosc = DLUGOSC, double szerokosc = SZEROKOSC);

    void obrotWlasny(double kat, char os) override;

    void obrotGlowny(double kat, char os) override;

    void translacja(Wektor<WEKTOR3D> wektorTranslacji) override;

    void translacja(double x, double y, double z);

    void rotacjaWirnikow(double predkosc);

public:
    Dron(double _skala = 1, Wektor<WEKTOR3D> wektorPoczatkowy = Wektor<WEKTOR3D>());

    void rysowanie() override;

    void ustawKolor(std::string _kolor) override;

    void wznoszenie(double wysokosc);

    void ladowanie();

    void obracanie(double kat);

    void lot();

    Wektor<WEKTOR3D> policzTrase(double odleglosc, Wektor<WEKTOR3D> _orientacja = Wektor());

    void ustawOrientacje(Wektor<WEKTOR3D> arg);

    void ustawOrientacjeCalkowita(Wektor<WEKTOR3D> arg);

    void ustawTranslacjeCalkowita(Wektor<WEKTOR3D> arg);

    double wezPredkoscWznoszenia();

    double wezPredkoscObrotu();

    Wektor<WEKTOR3D> wezSrodekSymetrii();

    Wektor<WEKTOR3D> wezOrientacje();

    Wektor<WEKTOR3D> wezTranslacjeCalkowita();

    Wektor<WEKTOR3D> wezOrientacjaCalkowita();

    std::string wezKolor();

    double wezSkale() { return skala; }
};

