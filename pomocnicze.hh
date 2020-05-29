#ifndef POMOCNICZE_HH
#define POMOCNICZE_HH

#include <iostream>
#include <climits>

template <typename typ>
class wektor{

    int pojemnosc;
    int rozmiar;
    typ *tablica;                   //wskaznik na tablice

    public:

    wektor();
    ~wektor();

    void usun();

    typ operator[](int indeks) const;
    typ& operator[](int indeks);

    int zwroc_rozmiar(){
        return this->rozmiar;
        }
};

template <typename typ>
struct element {

    element *poprzedni;
    typ *wartosc;
    element *nastepny;

    element(){
        wartosc = nullptr;
        nastepny = nullptr;
        poprzedni = nullptr;}

    element(typ zmienna){
        wartosc = new typ(zmienna);
        nastepny = nullptr;
        poprzedni = nullptr;}

    ~element(){if(wartosc !=nullptr) delete wartosc;}

    bool operator ==(element porownywany){
        if(this->wartosc == porownywany->wartosc) return true;
        else return false;
        }
};

template <typename typ>
class lista {

    element<typ> *pierwszy_element;
    element<typ> *ostatni_element;

    public:
    lista();

    element<typ>* pierwszy();
    element<typ>* ostatni();

    int rozmiar();
    void dodaj_koniec(typ dodaj);
    void usun_element(typ odniesienie);             // usuwa pierwszy napotkany element
    void usun_element(element<typ>* do_usuniecia);  // usuwa element mając jego wskaznik
    bool czy_pusta();
    void wyczysc();                                 // usuwa wszystkie elementy z listy

    class iterator{
        element<typ> *aktualny_element;
        lista<typ> *przypisana_lista;

        public:
        iterator();
        iterator(lista<typ> *moja_lista);

        typ iteruj(unsigned int numer_elem);        // iteruje liste

        typ operator ++ (); 
        typ operator ++ (int);
        typ operator -- (); 
        typ operator -- (int);

        void operator = (lista<typ> &moja_lista);   // przypisanie iteratora do listy
        void operator = (iterator moj_iter);        // przypisanie iteratora do innego

        element<typ>* przeszukaj(typ szukany);      // zwraca wskaznik na element lub nullptr, jesli go nie znajdzie

        typ* wartosc();                     // zwraca wskaznik na aktualny elment
        typ* wartosc(int indeks);           //zwraca wskaznik na podany element

        element<typ>* zwroc_elem();         // zwraca wskaznik na aktualny element

        void poczatek();
        void koniec();
        int rozmiar(){
            return this->przypisana_lista->rozmiar();
            }
    };
};

template <typename typ>
struct para{
    typ nazwa;
    int priorytet;

    para(){
        this->nazwa = static_cast<typ>(0);this->priorytet = INT_MAX;
        }
    para(typ nowa_nazwa){
        this->nazwa = nowa_nazwa;this->priorytet = INT_MAX;
        }

    bool operator == ( para<typ> por ){
        if(this->priorytet == por.priorytet){
            return true;
            }
        return false;
    }
    bool operator > ( para<typ> por ){
        if(this->priorytet > por.priorytet){
            return true;
            }
        return false;
    }
    bool operator >= ( para<typ> por ){
        if(this->priorytet >= por.priorytet){
            return true;
            }
        return false;
    }
    bool operator < ( para<typ> por ){
        if(this->priorytet < por.priorytet){
            return true;
            }
        return false;
    }
    bool operator <= ( para<typ> por ){
        if(this->priorytet <= por.priorytet){
            return true;
            }
        return false;
    }
};

template <typename typ>
class kopiec{

    wektor< para<typ> > kolejka;
    void podmien(para<typ> *pierwszy, para<typ> *drugi);
    void napraw_kopiec();

    public:
    void dodaj(typ do_dodania, int priorytet);  // dodaje element do kolejki
    para<typ> sciagnij();                       // zwraca i usuwa najmniejszy element
    bool czy_pusta();
};

void graf(int ilosc_wierzcholkow, std::string nazwa, int typ_gestosci);

#include "cpp/pomocnicze.cpp"
#include "cpp/lista.cpp"
#endif
