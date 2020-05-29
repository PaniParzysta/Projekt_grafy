#ifndef POMOCNICZE_CPP
#define POMOCNICZE_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <chrono>

#include "h/pomocnicze.hh"
using namespace std;

template <typename typ>
void kopiec<typ>::podmien(para<typ> *pierwszy, para<typ> *drugi){

    para<typ> chwilowe = *pierwszy;

    pierwszy->priorytet = drugi->priorytet;
    drugi->priorytet = chwilowe.priorytet;

    pierwszy->nazwa = drugi->nazwa;
    drugi->nazwa = chwilowe.nazwa;
}

template<typename typ>
void kopiec<typ>::napraw_kopiec(){

    int i = 1;
    int rozmiar = this->kolejka.zwroc_rozmiar();

    while(i<=rozmiar){
        if(i*2 <= rozmiar){
            if( (i*2+1) <= rozmiar){
                if(this->kolejka[i*2-1]<this->kolejka[i*2]){
                    if(this->kolejka[i-1]>this->kolejka[i*2-1]){
                        podmien(&this->kolejka[i*2-1], &this->kolejka[i-1]);
                    }
                    i*=2;
                } else{
                    if(this->kolejka[i-1]>this->kolejka[i*2]){
                        podmien(&this->kolejka[i*2], &this->kolejka[i-1]);
                    }
                    i = i*2 + 1;
                }
            } else{
                if(this->kolejka[i-1]>this->kolejka[i*2-1]){
                    podmien(&this->kolejka[i*2-1], &this->kolejka[i-1]);
                }
                i*=2;
            }
        } else{
            i*=2;
        }
    }
}

template <typename typ>
para<typ> kopiec<typ>::sciagnij(){

    para<typ> do_zwrocenia;

    do_zwrocenia.nazwa = this->kolejka[0].nazwa;
    do_zwrocenia.priorytet = this->kolejka[0].priorytet;
    podmien(&this->kolejka[0], &this->kolejka[this->kolejka.zwroc_rozmiar()-1]);

    this->kolejka.usun();
    this->napraw_kopiec();

    return do_zwrocenia;
}

template <typename typ>
bool kopiec<typ>::czy_pusta(){

    if(this->kolejka.zwroc_rozmiar() == 0){
        return true;                                // jesli kolejka jest pusta zwraca true
    }
    return false;                                   // jesli kolejka ma elementy zwraca false
}

template <typename typ>
wektor<typ>::wektor(){

    this->pojemnosc = 1;
    this->rozmiar = 0;
    this->tablica = new typ[this->pojemnosc];
}

template <typename typ>
wektor<typ>::~wektor(){

    delete [] this->tablica;
}

template <typename typ>
void wektor<typ>::usun(){

    if(rozmiar>0){
        if(this->pojemnosc>2*(this->rozmiar+2)){ //jesli wektor bedzie za duzy
            this->pojemnosc /= 2;
            typ *pomocnicza = new typ[this->pojemnosc];

            for(int i=0;i<rozmiar;i++){ // przepisuje do mniejszej tablicy
                pomocnicza[i] = this->tablica[i];
            }
            delete [] this->tablica;
            this->tablica = pomocnicza;
        }
        this->rozmiar--;
    } else{
        std::cout << "proba usuniecia elementu z pustego wektora" << std::endl;
    }
}

template<typename typ>
typ wektor<typ>::operator[](int indeks) const{

    if(indeks<rozmiar){
        return this->tablica[indeks];
    }

    std::cout << "nie ma takiego elementu" << std::endl;
    return this->tablica[0];
}

template<typename typ>
typ& wektor<typ>::operator[](int indeks){

    if(indeks<rozmiar){
        return this->tablica[indeks];
    }

    std::cout << "nie ma takiego elementu" << std::endl;
    return this->tablica[0];
}

void graf(int ilosc_wierzcholkow, string nazwa, int typ_gestosci){

    srand(time(NULL));
    ofstream plik;
    plik.open(nazwa);

    if(plik.is_open() == false){
        cout << "BLAD" << endl;
        return;
    }

    int **tab;
    tab = new int* [ilosc_wierzcholkow];

    for(int i=0;i<ilosc_wierzcholkow;i++){
        tab[i] = new int[ilosc_wierzcholkow];
    }
    int ilosc_krawedzi = 0;

    switch(typ_gestosci){
        case 0: // graf pelny
            ilosc_krawedzi = (ilosc_wierzcholkow*(ilosc_wierzcholkow-1)/2);
            break;
        case 1: // gestosc 75%
            ilosc_krawedzi = (ilosc_wierzcholkow*(ilosc_wierzcholkow-1)/2)*3/4;
            break;
        case 2: // gestosc 50%
            ilosc_krawedzi = (ilosc_wierzcholkow*(ilosc_wierzcholkow-1)/2)/2;
            break;
        case 3: // gestosc 25%
            ilosc_krawedzi = (ilosc_wierzcholkow*(ilosc_wierzcholkow-1)/2)/4;
            break;
        default:
            cout << "zła gęstość" << endl;
            break;
    }

    for(int i=0;i<ilosc_wierzcholkow;i++){
        for(int j=0;j<i;j++){
            tab[i][j] = rand()%99+1;
        }
    }
    plik << ilosc_krawedzi << "\t"
         << ilosc_wierzcholkow << "\t"
         << 0 << endl;
    int licznik_gestosci = 0;

    for(int i=0;i<ilosc_wierzcholkow;i++){
        for(int j=0;j<i;j++){
            switch(typ_gestosci){
                case 0: // graf pelny
                    plik << i << "\t"
                         << j << "\t"
                         << tab[i][j] << endl;
                    break;
                case 1: // gestosc 75%
                    if(licznik_gestosci %4 != 3){
                        plik << i << "\t"
                             << j << "\t"
                             << tab[i][j] << endl;
                    }
                    break;
                case 2: // gestosc 50%
                    if(licznik_gestosci %2 == 0){
                        plik << i << "\t"
                             << j << "\t"
                             << tab[i][j] << endl;
                    }
                    break;
                case 3: // gestosc 25%
                    if(licznik_gestosci %4 == 0){
                        plik << i << "\t"
                             << j << "\t"
                             << tab[i][j] << endl;
                    }
                    break;
                default:
                    cout << "zła gestość" << endl;
                    break;
            }
            licznik_gestosci++;
        }
    }
    plik.close();
}
#endif
