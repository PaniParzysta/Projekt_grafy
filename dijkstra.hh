#ifndef DIJKSTRA_HH
#define DIJKSTRA_HH

#include "g_lista.hh"
#include "g_macierz.hh"
#include "pomocnicze.hh"
#include <climits>

using namespace std;

struct wynik{

    int *poprzedni;         // wskaznik na tablice poprzednich elementow
    int *droga;             // wskaznik na tablice dlugosci drogi
    int wartosc;
    wynik(){
        this->droga=nullptr; this->poprzedni=nullptr; this->wartosc=-1;
        }
};


void d_lista(l_sasiedztwa<int, int> *graf, wynik *moj_wynik, int nr_wierzch_start = 0);
void d_macierz(m_sasiedztwa<int, int> *graf, wynik *moj_wynik, int nr_wierzch_start = 0);
int czasy(string plik_pom);

ostream& operator << ( ostream &strm, wynik moj_wynik );


#endif