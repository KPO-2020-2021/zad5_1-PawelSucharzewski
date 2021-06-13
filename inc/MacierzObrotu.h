#pragma once

#include <cmath>
#include <iostream>
#include <array>
#include "Wektor.h"

template<int ROZMIAR>
class MacierzObrotu {
private:
    std::array<Wektor<ROZMIAR>, ROZMIAR> tablica;
public:
    MacierzObrotu();

    MacierzObrotu(double kat, char os);

    Wektor<ROZMIAR> operator*(const Wektor<ROZMIAR> &arg) const;

    MacierzObrotu<ROZMIAR> operator*(const MacierzObrotu<ROZMIAR> &macierz);

    const Wektor<ROZMIAR> &operator[](int index) const;

    Wektor<ROZMIAR> &operator[](int index);
};

template<int ROZMIAR>
const Wektor<ROZMIAR> &MacierzObrotu<ROZMIAR>::operator[](int index) const {
    if (index > ROZMIAR || index < 0) throw std::out_of_range("Index jest niewlasciwy !");
    return tablica[index];
}

template<int ROZMIAR>
Wektor<ROZMIAR> &MacierzObrotu<ROZMIAR>::operator[](int index) {
    if (index > ROZMIAR || index < 0) throw std::out_of_range("Index jest niewlasciwy !");
    return tablica[index];
}

template<int ROZMIAR>
Wektor<ROZMIAR> MacierzObrotu<ROZMIAR>::operator*(const Wektor<ROZMIAR> &arg) const {
    Wektor<ROZMIAR> wynik;
    wynik[0] = arg[0] * tablica[0][0] + arg[1] * tablica[0][1] + arg[2] * tablica[0][2];
    wynik[1] = arg[0] * tablica[1][0] + arg[1] * tablica[1][1] + arg[2] * tablica[1][2];
    wynik[2] = arg[0] * tablica[2][0] + arg[1] * tablica[2][1] + arg[2] * tablica[2][2];
    return wynik;
}

template<int WYMIAR>
MacierzObrotu<WYMIAR>::MacierzObrotu() {
    tablica[0] = Wektor<3>({1, 0, 0});
    tablica[1] = Wektor<3>({0, 1, 0});
    tablica[2] = Wektor<3>({0, 0, 1});
}

template<int WYMIAR>
MacierzObrotu<WYMIAR>::MacierzObrotu(double katObrotu, char os) {
    katObrotu = (M_PI / 180) * katObrotu;
    switch (os) {
        case 'x':
            tablica[0] = Wektor<3>({1, 0, 0});
            tablica[1] = Wektor<3>({0, std::cos(katObrotu), -std::sin(katObrotu)});
            tablica[2] = Wektor<3>({0, std::sin(katObrotu), std::cos(katObrotu)});
            break;
        case 'y':
            tablica[0] = Wektor<3>({std::cos(katObrotu), 0, std::sin(katObrotu)});
            tablica[1] = Wektor<3>({0, 1, 0});
            tablica[2] = Wektor<3>({-std::sin(katObrotu), 0, std::cos(katObrotu)});
            break;
        case 'z':
            tablica[0] = Wektor<3>({std::cos(katObrotu), -std::sin(katObrotu), 0});
            tablica[1] = Wektor<3>({std::sin(katObrotu), std::cos(katObrotu), 0});
            tablica[2] = Wektor<3>({0, 0, 1});
            break;
        default:
            throw std::invalid_argument("Nie ma takiej osi!");
    }
}

template<int ROZMIAR>
MacierzObrotu<ROZMIAR> MacierzObrotu<ROZMIAR>::operator*(const MacierzObrotu<ROZMIAR> &macierz) {
    MacierzObrotu<3> wynik;
    wynik[0] = Wektor<3>({tablica[0][0] * macierz[0][0] + tablica[0][1] * macierz[1][0] + tablica[0][2] * macierz[2][0],
                          tablica[0][0] * macierz[0][1] + tablica[0][1] * macierz[1][1] + tablica[0][2] * macierz[2][1],
                          tablica[0][0] * macierz[0][2] + tablica[0][1] * macierz[1][2] + tablica[0][2] * macierz[2][2],
                         });

    wynik[1] = Wektor<3>({tablica[1][0] * macierz[0][0] + tablica[1][1] * macierz[1][0] + tablica[1][2] * macierz[2][0],
                          tablica[1][0] * macierz[0][1] + tablica[1][1] * macierz[1][1] + tablica[1][2] * macierz[2][1],
                          tablica[1][0] * macierz[0][2] + tablica[1][1] * macierz[1][2] + tablica[1][2] * macierz[2][2]
                         });
    wynik[2] = Wektor<3>({tablica[2][0] * macierz[0][0] + tablica[2][1] * macierz[1][0] + tablica[2][2] * macierz[2][0],
                          tablica[2][0] * macierz[0][1] + tablica[2][1] * macierz[1][1] + tablica[2][2] * macierz[2][1],
                          tablica[2][0] * macierz[0][2] + tablica[2][1] * macierz[1][2] + tablica[2][2] * macierz[2][2]
                         });

    return wynik;
}

template<int ROZMIAR>
std::ostream &operator<<(std::ostream &ost, const MacierzObrotu<ROZMIAR> &macierz) {
    ost << macierz[0] << std::endl;
    ost << macierz[1] << std::endl;
    if (ROZMIAR == 3)
        ost << macierz[2];
    return ost;
}

