#include "h/dijkstra.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <chrono>

using namespace std;

void d_lista(l_sasiedztwa<int, int> *graf, wynik *moj_wynik, int nr_wierzch_start){

    int ilos_wierzch = graf->wierzcholki()->rozmiar();
    lista< wierzcholek_lista<int, int> >::iterator it_w = graf->wierzcholki();                 // iterator do wierzcholkow
    wierzcholek_lista<int,int> *w = it_w.wartosc(nr_wierzch_start);
    kopiec< wierzcholek_lista<int,int> *> kolejka;                                             // kolejka wskaznikow na wierzcholek

    for(int i=0; i<ilos_wierzch;i++){
        moj_wynik->droga[i] = INT_MAX;
        moj_wynik->poprzedni[i] = -1;
    }

    moj_wynik->droga[nr_wierzch_start] = 0;
    kolejka.dodaj(w, moj_wynik->droga[nr_wierzch_start]);                           // droga do wierzcholka startowego to 0

    while(kolejka.czy_pusta() == false){

        para< wierzcholek_lista<int, int> *> pomocnicza = kolejka.sciagnij();
        int indeks = pomocnicza.nazwa->nazwa;                                       // pobiera nazwe bedaca indeksem z wierzcholka
        int odleglosc = pomocnicza.priorytet;

        if(odleglosc <= moj_wynik->droga[indeks]){                                  // jesli odleglosc jest wieksza niz w wyniku to wierzcholek byl aktualizowany
        
            lista< krawedz_lista<int, int> *>::iterator it_kraw_wierzch = graf->przylegle_krawedzie(pomocnicza.nazwa);
            int ilosc_krawedzi = it_kraw_wierzch.rozmiar();

            for(int i=0;i<ilosc_krawedzi;i++){

                krawedz_lista<int, int> *k = *(it_kraw_wierzch.wartosc());                 // wskaznik na krawedz pomocnicza
                w = graf->przeciwlegly_wierzch(pomocnicza.nazwa, k);

                if(moj_wynik->droga[w->nazwa] > (k->nazwa + moj_wynik->droga[pomocnicza.nazwa->nazwa])){

                    moj_wynik->droga[w->nazwa] = k->nazwa + moj_wynik->droga[pomocnicza.nazwa->nazwa];  // aktualizuje droge na krotsza
                    moj_wynik->poprzedni[w->nazwa] = pomocnicza.nazwa->nazwa;                           // aktualizuje poprzednia
                    kolejka.dodaj(w, moj_wynik->droga[w->nazwa]);                                       // dodaje do kolejki zaktualizowany wierzcholek
                }
                it_kraw_wierzch++;
            }
        }
    }
}

void d_macierz(m_sasiedztwa<int, int> *graf, wynik *moj_wynik, int nr_wierzch_start){

    int ilos_wierzch = graf->wierzcholki()->rozmiar();
    lista< wierzcholek_macierz<int> >::iterator it_w = graf->wierzcholki();
    wierzcholek_macierz<int> *w = it_w.wartosc(nr_wierzch_start);
    kopiec< wierzcholek_macierz<int> *> kolejka;

    for(int i=0; i<ilos_wierzch;i++){
        moj_wynik->droga[i] = INT_MAX;
        moj_wynik->poprzedni[i] = -1;
    }

    moj_wynik->droga[nr_wierzch_start] = 0;
    kolejka.dodaj(w, moj_wynik->droga[nr_wierzch_start]);

    while(kolejka.czy_pusta() == false){

        para< wierzcholek_macierz<int> *> pomocnicza = kolejka.sciagnij();
        int indeks = pomocnicza.nazwa->indeks;
        int odleglosc = pomocnicza.priorytet;

        if(odleglosc <= moj_wynik->droga[indeks]){

            krawedz_macierz<int, int> **wiersz = graf->przylegle_krawedzie(pomocnicza.nazwa);
            int ilosc_krawedzi = graf->wierzcholki()->rozmiar();

            for(int i=0;i<ilosc_krawedzi;i++){                              // wiersz ma tyle elementow ile jest wierzcholkow w grafie

                krawedz_macierz<int, int> *k = wiersz[i];

                if(k != nullptr){

                    w = graf->przeciwlegly_wierzch(pomocnicza.nazwa, k);

                    if(moj_wynik->droga[w->indeks] > (k->nazwa + moj_wynik->droga[pomocnicza.nazwa->indeks])){

                        moj_wynik->droga[w->indeks] = k->nazwa + moj_wynik->droga[pomocnicza.nazwa->indeks];
                        moj_wynik->poprzedni[w->indeks] = pomocnicza.nazwa->indeks;
                        kolejka.dodaj(w, moj_wynik->droga[w->indeks]);
                    }
                }
            }
        }
    }
}

int czasy(string plik_pom){

    chrono::high_resolution_clock::time_point start, koniec;        //do pomiaru czasu
    double czas_trwania;
    ofstream graf_macierz, graf_lista;

    ifstream plik;
    l_sasiedztwa<int, int> graf_l;
    plik.open(plik_pom);
    if(plik.is_open() == false){
        cout << "Nie udalo sie otworzyc pliku" << endl;
        return 1;
    }
    plik >> graf_l;
    plik.close();

    wynik wynik_l;
    int wartosc = graf_l.wierzcholki()->rozmiar();
    wynik_l.droga = new int[wartosc];
    wynik_l.poprzedni = new int[wartosc];
    wynik_l.wartosc = wartosc;

    start = std::chrono::high_resolution_clock::now();
    d_lista(&graf_l, &wynik_l);
    koniec = std::chrono::high_resolution_clock::now();

    czas_trwania = std::chrono::duration<double, std::milli>(koniec-start).count();
    graf_lista<<czas_trwania << ":";                                //czas działania algorytmu

    wynik wynik_m;
    wynik_m.droga = new int[wartosc];
    wynik_m.poprzedni = new int[wartosc];
    wynik_m.wartosc = wartosc;

    m_sasiedztwa<int, int> graf_m;
    plik.open(plik_pom);
    if(plik.is_open() == false){
        cout << "Nie udalo sie otworzyc pliku" << endl;
        return 1;
    }

    plik >> graf_m;
    plik.close();

    start = std::chrono::high_resolution_clock::now();
    d_macierz(&graf_m, &wynik_m);
    koniec = std::chrono::high_resolution_clock::now();

    czas_trwania = std::chrono::duration<double, std::milli>(koniec-start).count();
    graf_macierz << czas_trwania << ":";

    return 0;
}

ostream& operator << (ostream &strm, wynik moj_wynik){
    strm << "indeks, droga, poprzednicy po spacji" << endl;
    for(int i=0;i<moj_wynik.wartosc;i++){
        
        strm << i << ", " << moj_wynik.droga[i] << ", ";
        int j = i;

        while(moj_wynik.poprzedni[j] != -1){

            strm << moj_wynik.poprzedni[j] << " ";
            j = moj_wynik.poprzedni[j];
            
        }
        strm << endl;
    }
    return strm;
}

