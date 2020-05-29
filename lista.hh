#ifndef LISTA_2_KIER_HH
#define LISTA_2_KIER_HH

#include <iostream>
#include <climits>

template <typename typ>
struct zmienna {
    zmienna *poprzedni;
    typ *wartosc;
    zmienna *nastepny;

    zmienna(){
        wartosc = nullptr;
        nastepny = nullptr;
        poprzedni = nullptr;}

    zmienna(typ zmienna){
        wartosc = new typ(zmienna);
        nastepny = nullptr;
        poprzedni = nullptr;}

    ~zmienna(){if(wartosc !=nullptr) delete wartosc;}

    bool operator ==(zmienna porownywany){
        if(this->wartosc == porownywany->wartosc) return true;
        else
            return false;
    }
};

template <typename typ>
class lista {

    zmienna<typ> *pierwszy_element;
    zmienna<typ> *ostatni_element;

    public:
    lista();
    zmienna<typ>* pierwszy();
    zmienna<typ>* ostatni();
    int rozmiar();
    bool czy_pusta();
    void wyczysc();                 //usuwa wszystkie elementy z listy

    class iterator{
        zmienna<typ> *aktualny_element;
        lista<typ> *przypisana_lista;

        public:
        iterator();
        iterator(lista<typ> *moja_lista);
        typ iteruj(unsigned int numer_elem); // iteruje liste

        typ operator ++();              // przeciazenie operatora ++
        typ operator ++(int);           // przeciazenie operatora ++
        typ operator --();              // przeciazenie operatora ++
        typ operator --(int);           // przeciazenie operatora ++
        void operator =(lista<typ> &moja_lista);        // przypisanie iteratora do listy
        void operator =(iterator moj_iter);             // przypisanie iteratora do innej zmiennej

        typ* wartosc();
        typ* wartosc(int indeks);

        zmienna<typ>* zwroc_elem();         // zwraca wskaznik na aktualny zmienna
        void poczatek();
        void koniec();
        int rozmiar(){return this->przypisana_lista->rozmiar();}
    };

};
//#include "../lista_2_kier.cpp"

#endif