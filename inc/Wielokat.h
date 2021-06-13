#pragma once

#include "Obiekt.h"
#include "MacierzObrotu.h"

const int SKALA = 1;
const int ILOSC_KATOW = 4;
const int TROJKAT = 3;
const int LINIA = 2;
const std::string KOLOR = "#000000";

template<int KATY = ILOSC_KATOW>
class Wielokat : public Obiekt {
private:
    double dlugosc_krawedzi;
    std::array<Wektor<WEKTOR3D>, KATY> punkty;
public:
    Wielokat() = default;

    Wielokat(double _dlugoscKrawedzi, char orientacja = 'x');

    Wielokat(Wektor<WEKTOR3D> v, Wektor<WEKTOR3D> w, Wektor<WEKTOR3D> wektorTranslacji);

    Wielokat(const std::array<Wektor<WEKTOR3D>, KATY> &arg, std::string _kolor);

    void rysowanie() override;

    void translacja(Wektor<WEKTOR3D> wektorTranslacji) override;

    void obrotGlowny(double kat, char os) override;

    void obrotWlasny(double kat, char os) override;

    void ustawKolor(std::string _kolor) override;

    void usunObiekt() override;

    const Wektor<WEKTOR3D> &operator[](int index) const;

    Wektor<WEKTOR3D> &operator[](int index);

};


template<int KATY>
Wielokat<KATY>::Wielokat(double _dlugoscKrawedzi, char orientacja) {
    srodek_symetrii = Wektor();
    dlugosc_krawedzi = _dlugoscKrawedzi;
    kolor = KOLOR;

    Wektor<WEKTOR3D> pomocniczy;

    MacierzObrotu<3> macierzObrotuX(360 / KATY, 'x');
    MacierzObrotu<3> macierzObrotuY(360 / KATY, 'y');
    MacierzObrotu<3> macierzObrotuZ(360 / KATY, 'z');

    switch (orientacja) {
        case 'x':
            pomocniczy[0] = dlugosc_krawedzi;
            for (int i = 0; i < KATY; ++i) {
                punkty[i] = pomocniczy;
                pomocniczy = macierzObrotuY * pomocniczy;
            }
            break;
        case 'y':
            pomocniczy[1] = dlugosc_krawedzi;
            for (int i = 0; i < KATY; ++i) {
                punkty[i] = pomocniczy;
                pomocniczy = macierzObrotuZ * pomocniczy;
            }
            break;
        case 'z':
            pomocniczy[2] = dlugosc_krawedzi;
            for (int i = 0; i < KATY; ++i) {
                punkty[i] = pomocniczy;
                pomocniczy = macierzObrotuX * pomocniczy;
            }
            break;
        default:
            break;
    }
}

template<int KATY>
void Wielokat<KATY>::rysowanie() {
    if (id.empty()) {
        id = "W#" + std::to_string(lista_obiektow.size() + 1);
    }
    std::stringstream tmp, command;
    tmp << "from " << punkty[0][0] << "," << punkty[0][2] << "," << punkty[0][1] << " to ";
    for (int i = 1; i < KATY; ++i) {
        tmp << punkty[i][0] << "," << punkty[i][2] << "," << punkty[i][1] << " to ";
    }
    tmp << punkty[0][0] << "," << punkty[0][2] << "," << punkty[0][1];

    if (lista_obiektow.find(id) == lista_obiektow.end()) {
        lista_obiektow[id] = lista_obiektow.size() + 1;
    }

//    command << "set object " << lista_obiektow[id] << " polygon " << tmp.str() <<
//            " fill solid 0 border rgb \"red\"";

    command << "set object " << lista_obiektow[id] << " polygon " << tmp.str() <<
            " fillstyle transparent solid fillcolor rgb \"" << kolor << "\"";

    wykres.sendcommand(command.str());
}

template<int KATY>
void Wielokat<KATY>::translacja(Wektor<WEKTOR3D> wektorTranslacji) {
    srodek_symetrii = srodek_symetrii + wektorTranslacji;
    for (int i = 0; i < KATY; ++i) {
        punkty[i] = punkty[i] + wektorTranslacji;
    }
}

template<int KATY>
void Wielokat<KATY>::obrotGlowny(double kat, char os) {
    MacierzObrotu<3> macierzObrotu(kat, os);
    srodek_symetrii = macierzObrotu * srodek_symetrii;
    for (int i = 0; i < KATY; ++i) {
        punkty[i] = macierzObrotu * punkty[i];
    }
}

template<int KATY>
void Wielokat<KATY>::obrotWlasny(double kat, char os) {
    Wektor<3> wektor = srodek_symetrii;
    wektor = wektor * -1;
    translacja(wektor);
    obrotGlowny(kat, os);
    wektor = wektor * -1;
    translacja(wektor);
}

template<int KATY>
const Wektor<WEKTOR3D> &Wielokat<KATY>::operator[](int index) const {
    return punkty[index];
}

template<int KATY>
Wektor<WEKTOR3D> &Wielokat<KATY>::operator[](int index) {
    return punkty[index];
}

template<int KATY>
void Wielokat<KATY>::ustawKolor(std::string _kolor) {
    kolor = _kolor;
}

template<int KATY>
Wielokat<KATY>::Wielokat(Wektor<WEKTOR3D> v, Wektor<WEKTOR3D> w, Wektor<WEKTOR3D> wektorTranslacji) {
    punkty[0] = Wektor<WEKTOR3D>();
    punkty[1] = v;
    punkty[2] = v + w;
    punkty[3] = w;
    ustawKolor(KOLOR);
    translacja(wektorTranslacji);
}

template<int KATY>
void Wielokat<KATY>::usunObiekt() {
    translacja(Wektor<WEKTOR3D>({10000, 10000, 10000}));
    rysowanie();
}

template<int KATY>
Wielokat<KATY>::Wielokat(const std::array<Wektor<WEKTOR3D>, KATY> &punkty, std::string _kolor):punkty(punkty) {
    ustawKolor(_kolor);
}

