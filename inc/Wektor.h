#pragma once

#include <array>
#include <iostream>
#include <valarray>

const int WEKTOR3D = 3;

template<int ROZMIAR = WEKTOR3D>
class Wektor {
private:
    std::array<double, ROZMIAR> tablica;
public:
    Wektor() { tablica.fill(0); };

    Wektor(std::array<double, ROZMIAR> args) : tablica(args) {};

    Wektor<ROZMIAR> operator+(Wektor<ROZMIAR> &arg2);

    Wektor<ROZMIAR> operator+=(const Wektor<ROZMIAR> &arg2);

    Wektor<ROZMIAR> operator-(const Wektor<ROZMIAR> &arg2) const;

    Wektor<ROZMIAR> operator*(double arg2) const;

    Wektor<ROZMIAR> operator/(double arg2) const;

    const double &operator[](int index) const;

    double &operator[](int index);
};

template<int ROZMIAR>
double &Wektor<ROZMIAR>::operator[](const int index) {
    if (index > ROZMIAR || index < 0) throw std::out_of_range("Index jest niepoprawny !");
    return tablica[index];
}

template<int ROZMIAR>
const double &Wektor<ROZMIAR>::operator[](const int index) const {
    if (index > ROZMIAR || index < 0) throw std::out_of_range("Index jest niepoprawny !");
    return tablica[index];
}

template<int ROZMIAR>
Wektor<ROZMIAR> Wektor<ROZMIAR>::operator+(Wektor<ROZMIAR> &arg2) {
    Wektor<ROZMIAR> wynik;
    for (int i = 0; i < ROZMIAR; i++) {
        wynik[i] = tablica[i] + arg2[i];
    }
    return wynik;
}

template<int ROZMIAR>
Wektor<ROZMIAR> Wektor<ROZMIAR>::operator+=(const Wektor<ROZMIAR> &arg2) {
    Wektor<ROZMIAR> wynik;
    for (int i = 0; i < ROZMIAR; i++) {
        wynik[i] = tablica[i] + arg2[i];
    }
    return wynik;
}

template<int ROZMIAR>
Wektor<ROZMIAR> Wektor<ROZMIAR>::operator-(const Wektor<ROZMIAR> &arg2) const {
    Wektor<ROZMIAR> wynik;
    for (int i = 0; i < ROZMIAR; i++) {
        wynik[i] = tablica[i] - arg2[i];
    }
    return wynik;
}

template<int ROZMIAR>
Wektor<ROZMIAR> Wektor<ROZMIAR>::operator*(double arg2) const {
    Wektor<ROZMIAR> result;
    for (int i = 0; i < ROZMIAR; i++) {
        result[i] = tablica[i] * arg2;
    }
    return result;
}

template<int ROZMIAR>
Wektor<ROZMIAR> Wektor<ROZMIAR>::operator/(double arg2) const {
    if (arg2 == 0) throw std::invalid_argument("[Wektor] Dzielenie przez zero!");
    Wektor<ROZMIAR> result;
    for (int i = 0; i < ROZMIAR; i++) {
        result[i] = tablica[i] / arg2;
    }
    return result;
}

template<int ROZMIAR>
bool operator==(const Wektor<ROZMIAR> &v, const Wektor<ROZMIAR> &w) {
    for (int i = 0; i < ROZMIAR; i++) {
        if (std::abs(v[i] - w[i]) >= 0.99) return false;
    }
    return true;
}

template<int ROZMIAR>
std::ostream &operator<<(std::ostream &ost, const Wektor<ROZMIAR> &Vec) {
    std::cout << std::fixed;
    for (int i = 0; i < ROZMIAR; i++) {
        ost << Vec[i];
        if (i != ROZMIAR - 1) ost << ",";
    }
    return ost;
}

template<int ROZMIAR>
std::istream &operator>>(std::istream &ist, Wektor<ROZMIAR> &Vec) {
    double tmp;
    for (int i = 0; i < ROZMIAR; i++) {
        std::cout << "Wektor [" << i + 1 << "] : ";
        ist >> tmp;
        Vec[i] = tmp;
    }

    return ist;
}

template<int ROZMIAR>
double dystansMiedzyWektorami(const Wektor<ROZMIAR> &v, const Wektor<ROZMIAR> &w) {
    double tmp;
    for (int i = 0; i < ROZMIAR; i++) {
        tmp += pow(abs(v[i] - w[i]), 2);
    }
    return sqrt(tmp);
}

