#include "gtest/gtest.h"
#include "Wektor.h"

TEST(Wektor, konstuktor) {
    Wektor<5> v({-9, 0, 2, 2, 1});
    EXPECT_EQ(v[1], 0);
}

TEST(Wektor, dodawanie) {
    Wektor<3> v({-5, 0, 2});
    Wektor<3> w({3, 0, 0});
    Wektor<3> wynik({-2, 0, 2});
    EXPECT_EQ(v + w, wynik);
}

TEST(Wektor, odejmowanie) {
    Wektor<3> v({8, -2, 0});
    Wektor<3> w({1, 2, -3});
    Wektor<3> wynik({7, -4, 3});
    EXPECT_EQ(v - w, wynik);
}

TEST(Wektor, mnozenieStala) {
    Wektor v({1, -1, 0});
    double stala = 3;
    Wektor wynik({3, -3, 0});
    EXPECT_EQ(v * stala, wynik);
}


TEST(Wektor, dzielenie) {
    Wektor v({30, 3, -3});
    double stala = 3;
    Wektor wynik({10, 1, -1});
    EXPECT_EQ(v / stala, wynik);
}




