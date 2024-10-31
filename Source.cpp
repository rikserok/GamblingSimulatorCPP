#include <iostream> // cout, cin, itp.
#include <cstdlib>  // random liczba
#include <chrono>   // czas
#include <thread>   // w¹tki

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

// USTAWIENIA
// dane ktore mozna zmieniac
int defaultpieniadze = 10000; // ilosc poczatkowych pieniedzy
int szansa = 2;               // wartosc mniejsza = wieksze szanse (nie moze byc mniejsza od 0)

// przywolywanie funkcji
void maingame(int& rngNum, int& pieniadze, int pieniadzeUzyte);
void ai(int& pieniadze, int pieniadzeUzyte);

// Wypisane zasady
void zasady() {
    std::cout << "Masz " << defaultpieniadze << " pieniedzy do dyspozycji. Mozesz obstawic dowolna kwote i jesli wygrasz zostanie ona pomnozona x2. Jezeli przegrasz, tracisz obstawiana sume. \n";
}

int main() {
    // dane gracza
    int pieniadze = defaultpieniadze;
    bool grajDalej = true;

    zasady();

    while (grajDalej && pieniadze > 0) {
        int pieniadzeUzyte;
        std::cout << "Ile chcesz obstawic? (maksymalnie: " << pieniadze << "):  \n";
        std::cin >> pieniadzeUzyte;

        if (pieniadzeUzyte > pieniadze || pieniadzeUzyte <= 0) {
            std::cout << "Nieprawidlowa kwota! Sprobuj ponownie.\n";
            continue;
        }

        ai(pieniadze, pieniadzeUzyte);

        if (pieniadze > 0) {
            char odpowiedz;
            std::cout << "Czy chcesz grac dalej? (y/n): ";
            std::cin >> odpowiedz;
            grajDalej = (odpowiedz == 'y' || odpowiedz == 'Y');
        }
        else {
            std::cout << "Nie masz juz pieniedzy! Gra zakonczona.\n";
        }
    }

    std::cout << "Koniec gry! Masz " << pieniadze << " pieniedzy.\n";
    return 0;
}

void ai(int& pieniadze, int pieniadzeUzyte) {
    srand(time(0));
    int rngNum = rand() % szansa;
    maingame(rngNum, pieniadze, pieniadzeUzyte);
}

void maingame(int& rngNum, int& pieniadze, int pieniadzeUzyte) {
    std::cout << "Wylosowany numer: " << rngNum << "\n"; // Do debugowania

    if (rngNum == 0) {
        pieniadze += pieniadzeUzyte; // Wygrana
        std::cout << "Wygrales! Masz teraz " << pieniadze << " pieniedzy.\n";
    }
    else {
        pieniadze -= pieniadzeUzyte; // Przegrana
        std::cout << "Przegrales! Masz teraz " << pieniadze << " pieniedzy.\n";
    }
}
