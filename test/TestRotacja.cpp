#include "gtest/gtest.h"
#include "Wektor.h"
#include "MacierzObrotu.h"


TEST(Wektor, rotacja) {
    Wektor<3> w({1, 1, 1});
    MacierzObrotu<3> macierz(0, 'x');
    Wektor<3> wynik({1,1,1});
    w = macierz * w;
    EXPECT_EQ(w, wynik);
}

TEST(Wektor, rotacjaX) {
    Wektor<3> w({0, 1, 0});
    MacierzObrotu<3> macierz(90, 'x');
    Wektor<3> wynik({0, 0, 1});
    w = macierz * w;
    EXPECT_NEAR(w[0], wynik[0], 0.005);
    EXPECT_NEAR(w[1], wynik[1], 0.005);
    EXPECT_NEAR(w[2], wynik[2], 0.005);
}

TEST(Wektor, rotacjaY) {
    Wektor<3> w({1, 0, 0});
    MacierzObrotu<3> macierz(90, 'y');
    Wektor<3> wynik({0, 0, -1});
    w = macierz * w;
    EXPECT_NEAR(w[0], wynik[0], 0.005);
    EXPECT_NEAR(w[1], wynik[1], 0.005);
    EXPECT_NEAR(w[2], wynik[2], 0.005);
}

TEST(Wektor, rotacjaZ) {
    Wektor<3> w({1, 0, 0});
    MacierzObrotu<3> macierz(90, 'z');
    Wektor<3> wynik({0, 1, 0});
    w = macierz * w;
    EXPECT_NEAR(w[0], wynik[0], 0.005);
    EXPECT_NEAR(w[1], wynik[1], 0.005);
    EXPECT_NEAR(w[2], wynik[2], 0.005);
}

