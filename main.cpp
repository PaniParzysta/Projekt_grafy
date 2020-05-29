#include "h/g_macierz.hh"
#include "h/g_lista.hh"
#include "h/dijkstra.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <chrono>

using namespace std;

int main(){

    string plik_pomocniczy;
    ofstream graf_macierz, graf_lista;

    int wielkosc[5] = {10, 50, 100, 500, 1000};

    graf_lista.open("wyniki_l.txt");
    graf_macierz.open("m_sasiedztwa.txt");

    if(graf_lista.is_open() == false || graf_macierz.is_open() == false)
    {
        cout << "Błąd" << endl;
        return 1;
    }

    for (int k = 0; k<4; k++) {

        graf_macierz << "typ gestosci;" << k << ";" << "rozmiary;" << endl;
        graf_lista << "typ gestosci;" << k << ";" << "rozmiary;" << endl;

        for(int i=-2; i<=2; i++) {
            if (i != 2) {
                graf_macierz << wielkosc[i+2] << ";" << wielkosc[i+3] << ";";
                graf_lista << wielkosc[i+2] << ";" << wielkosc[i+3] << ";";
                ++i;
            } else {
                graf_macierz << wielkosc[i + 2] << ";" << endl;
                graf_lista << wielkosc[i + 2] << ";" << endl;
                i++;
            }
        }

        for(int i = 0; i<100; i++){
            for(int j=0; j<5; j++){
            
                plik_pomocniczy = "grafy/Graf_typ-" + to_string(wielkosc[j]) + "_g-" + to_string(k) + "_powt" + to_string(i);

                graf(wielkosc[j], plik_pomocniczy, k);
                czasy(plik_pomocniczy);                     //wywołanie i zmierzenie czasu algorytmu dijkstry
            }
            graf_lista << endl;
            graf_macierz << endl;
        }
        graf_lista << endl << endl;
        graf_macierz << endl << endl;
    }

    graf_lista.close();
    graf_macierz.close();

 return 0;
}
