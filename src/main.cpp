#include "Scena.h"

void wyswietlMenu();

int main(){
    char opcja = ' ';
    Scena scena;

    scena.wyswietlAktywnegoDrona();
    wyswietlMenu();

    do {
        std::cout << "Twoj wybor: ";
        std::cin >> opcja;

        switch (opcja) {
            case 'A':
            case 'a':
                scena.wybierzDrona();
                break;
            case 'P':
            case 'p':
                scena.lot();
                scena.rysuj();
                std::cout << "Dron wyladowal ...\n";
                break;
            case 'M':
            case 'm':
                scena.wyswietlAktywnegoDrona();
                wyswietlMenu();
                break;
            case 'K':
            case 'k':
                break;
            default:
                std::cout << "Nie ma takiej opcji do wyboru! \n";
                break;
        }

    } while (opcja != 'k' && opcja != 'K');



    return 0;
}

void wyswietlMenu() {
    std::cout << "a - wybor drona\n";
    std::cout << "p - przelot drona\n";
    std::cout << "m - menu\n\n";
    std::cout << "k - koniec\n";
}

