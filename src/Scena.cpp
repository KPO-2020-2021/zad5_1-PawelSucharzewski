#include <chrono>
#include <thread>
#include "Scena.h"

bool petlaGry = true;
bool porownanieZPrezycjaEpsilon(double a, double b, double epsilon = 0.9);

Scena::Scena() {
    numerDrona = 0;
    drony.push_back(Dron());
    drony.push_back(Dron(1, Wektor<WEKTOR3D>({0, 0, 200})));
    drony.push_back(Dron(1, Wektor<WEKTOR3D>({-200, 0, 0})));
    drony[0].ustawKolor("#FF0000");
    drony[1].ustawKolor("#00FF00");
    drony[2].ustawKolor("#0000FF");
}

void Scena::rysuj() {
    petlaGry = true;
    using clock = std::chrono::steady_clock;
    auto next_frame = clock::now();
    narysujTrase();

    while(petlaGry) {
        next_frame += std::chrono::milliseconds(1000 / 60); // 60FPS
        if (komendy.empty()) { petlaGry = false; }
        else {
            animacja();
        }
        for (int i = 0; i < drony.size(); ++i) {
            drony[i].rysowanie();
        }

        for (int j = 0; j < elementyTerenu.size(); ++j) {
            elementyTerenu[j]->rysowanie();
        }

        for (int i = 0; i < trasa.size(); ++i) {
            trasa[i].rysowanie();
        }
        wykres.rysujWykres();
        std::this_thread::sleep_until(next_frame);
    }
}

void Scena::animacja() {
    switch (komendy[0].znak) {
        case 'W':
            drony[numerDrona].wznoszenie(komendy[0].wartosc);
            if (drony[numerDrona].wezSrodekSymetrii()[1] >= komendy[0].wartosc) {
                komendy.erase(komendy.begin());
            }
            break;
        case 'O':
            drony[numerDrona].obracanie(komendy[0].wartosc);
            if (drony[numerDrona].wezPredkoscObrotu() == 0 &&
            porownanieZPrezycjaEpsilon(drony[numerDrona].wezOrientacje()[1], komendy[0].wartosc)){
                komendy.erase(komendy.begin());
                Wektor tmp = drony[numerDrona].wezOrientacje();
                tmp = drony[numerDrona].wezOrientacjaCalkowita() + tmp;
                drony[numerDrona].ustawOrientacjeCalkowita(tmp);
                drony[numerDrona].ustawOrientacje(Wektor<WEKTOR3D>());
            }
            break;
        case 'P':
            drony[numerDrona].lot();
            if (translacjaWykonana()) {
                drony[numerDrona].ustawTranslacjeCalkowita(Wektor());
                komendy.erase(komendy.begin());
            }
            break;
        case 'L':
            drony[numerDrona].ladowanie();
            if (drony[numerDrona].wezSrodekSymetrii()[1] <= 0) {
                komendy.erase(komendy.begin());
            }
            break;
        default:
            break;
    }

}

void Scena::obrot() {
    double kat = 0;
    std::cout << "Podaj kat obrotu: ";
    std::cin >> kat;
    if (drony[numerDrona].wezSrodekSymetrii()[1] > 2 || !komendy.empty()) { komendy.push_back(Komenda({'O', kat})); }
    else std::cout << "Nie mozna obrocic, gdy sie nie wystartowalo !\n";
}

void Scena::wystartuj() {
    double wysokosc = 0;
    std::cout << "Podaj wysokosc: ";
    std::cin >> wysokosc;
    if (drony[numerDrona].wezSrodekSymetrii()[1] < 2 || komendy.empty()) { komendy.push_back(Komenda({'W', wysokosc})); }
    else std::cout << "Dron juz wystartowal !\n";
}

void Scena::wybierzDrona() {
    for (int i = 0; i < drony.size(); ++i) {
        std::cout << "Dron nr " << i << ". Polozenie: " << drony[i].wezSrodekSymetrii();
        if (numerDrona == i) std::cout << "   <-- dron aktywny \n";
        else std::cout << "\n";
    }

    std::cout << "Podaj numer drona: ";
    std::cin >> numerDrona;
    if (numerDrona > drony.size() || numerDrona < 0) throw std::invalid_argument("Bledny index drona!\n");
}

void Scena::przesun() {
    double odleglosc = 0;
    std::cout << "Podaj odleglosc: ";
    std::cin >> odleglosc;
    if (drony[numerDrona].wezSrodekSymetrii()[1] > 2 || !komendy.empty()) { komendy.push_back(Komenda({'P', odleglosc})); }
    else std::cout << "Nie mozna leciec, gdy sie nie wystartowalo !\n";
}

void Scena::ladowanie() {
    if (drony[numerDrona].wezSrodekSymetrii()[1] > 2 || !komendy.empty()) { komendy.push_back(Komenda({'L', 0})); }
    else std::cout << "Nie mozna ladowac, gdy sie nie wystartowalo !\n";
}

bool Scena::translacjaWykonana() {
    bool x = porownanieZPrezycjaEpsilon(drony[numerDrona].wezTranslacjeCalkowita()[0],
                                  drony[numerDrona].policzTrase(komendy[0].wartosc)[0], 5);

    bool y = porownanieZPrezycjaEpsilon(drony[numerDrona].wezTranslacjeCalkowita()[1],
                                  drony[numerDrona].policzTrase(komendy[0].wartosc)[1], 5);

    bool z = porownanieZPrezycjaEpsilon(drony[numerDrona].wezTranslacjeCalkowita()[2],
                                  drony[numerDrona].policzTrase(komendy[0].wartosc)[2], 5);
    return x && y && z;
}

void Scena::narysujTrase() {
    std::cout << "Rysuje zaplanowana sciezke lotu ... \n";
    for (int i = 0; i < trasa.size(); ++i) {
        trasa[i].ustawKolor("#FFFF0000");
        trasa[i].translacja(Wektor({1000000, 10000, 100000}));
        trasa[i].rysowanie();
    }

    std::string kolorDrona = drony[numerDrona].wezKolor();
    double kat = komendy[1].wartosc;
    Wektor orientacja({0, komendy[1].wartosc, 0});

    Wektor<WEKTOR3D> miejsceStartu = drony[numerDrona].wezSrodekSymetrii();
    trasa[0] = Wielokat<LINIA>({miejsceStartu, Wektor({0, komendy[0].wartosc, 0}) + miejsceStartu}, kolorDrona);

    Wektor miejsceLadowaniaDolne = drony[numerDrona].policzTrase(komendy[2].wartosc, orientacja);
    miejsceLadowaniaDolne = drony[numerDrona].wezSrodekSymetrii() + miejsceLadowaniaDolne;

    Wektor miejsceLadowaniaGorne = Wektor({0, komendy[0].wartosc, 0}) + miejsceLadowaniaDolne;

    trasa[1] = Wielokat<LINIA>({Wektor({0, komendy[0].wartosc, 0}) + miejsceStartu, miejsceLadowaniaGorne}, kolorDrona);
    trasa[2] = Wielokat<LINIA>({miejsceLadowaniaGorne, miejsceLadowaniaDolne}, kolorDrona);
}

void Scena::wyswietlAktywnegoDrona() {
    std::string kolor = "";
    switch (numerDrona) {
        case 0:
            kolor = "Czerwony";
            break;
        case 1:
            kolor = "Zielony";
            break;
        case 2:
            kolor = "Niebieski";
            break;
    }
     std::cout << "Polozenie aktywnego drona | " << kolor << " | (x,z) = ("
     << drony[numerDrona].wezSrodekSymetrii()[0] << ", " << drony[numerDrona].wezSrodekSymetrii()[2]
     << ")" << std::endl;
}

void Scena::lot() {
    wystartuj();
    obrot();
    przesun();
    ladowanie();
    std::cout << "Realizacja przelotu ...\n";
}

bool porownanieZPrezycjaEpsilon(double a, double b, double epsilon) {
    return std::abs(a - b) < epsilon;
}
