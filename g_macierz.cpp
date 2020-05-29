#ifndef GRAF_M_CPP
#define GRAF_M_CPP

#include "h/g_macierz.hh"
using namespace std;

template <typename kraw, typename wierzch>
m_sasiedztwa<kraw, wierzch>::m_sasiedztwa(){

    this->macierz = nullptr;
}

template <typename kraw, typename wierzch>
m_sasiedztwa<kraw, wierzch>::~m_sasiedztwa(){

    if(this->lista_wierzcholkow.czy_pusta() == false){
        int wielkosc = this->lista_wierzcholkow.rozmiar();

        for(int i=0;i<wielkosc;i++){
            delete [] this->macierz[i];
        }
        delete [] this->macierz;
        this->lista_krawedzi.wyczysc();
        this->lista_wierzcholkow.wyczysc();
    }
}

template <typename kraw, typename wierzch>
void m_sasiedztwa<kraw, wierzch>::dodaj_wierzcholek(wierzch nazwa){

    int wielkosc = this->lista_wierzcholkow.rozmiar();
    if(this->lista_wierzcholkow.czy_pusta() == false){
        krawedz_macierz<kraw, wierzch> ***pomocnicza = new krawedz_macierz<kraw, wierzch>** [wielkosc+1];
        for(int i=0;i<wielkosc+1;i++){
            pomocnicza[i] = new krawedz_macierz<kraw, wierzch>* [wielkosc+1];
        }

        for(int i=0;i<wielkosc;i++){
            for(int j=0;j<wielkosc;j++){
                pomocnicza[i][j] = this->macierz[i][j];
            }
            pomocnicza[i][wielkosc] = nullptr;
        }

        for(int i=0;i<wielkosc+1;i++){
            pomocnicza[wielkosc][i] = nullptr;
        }

        for(int i=0;i<wielkosc;i++){
            delete [] this->macierz[i];
        }
        delete [] this->macierz;
        this->macierz = pomocnicza;
    } else{

        this->macierz = new krawedz_macierz<kraw, wierzch>** [1];
        this->macierz[0] = new krawedz_macierz<kraw,wierzch>* [1];
        this->macierz[0][0] = nullptr;
    }
    wierzcholek_macierz<wierzch> nowy_wierzcholek(nazwa);

    nowy_wierzcholek.indeks = wielkosc;
    this->lista_wierzcholkow.dodaj_koniec(nowy_wierzcholek);
    this->lista_wierzcholkow.ostatni()->wartosc->miejsce_na_liscie = this->lista_wierzcholkow.ostatni();
}

template <typename kraw, typename wierzch>
void m_sasiedztwa<kraw, wierzch>::dodaj_krawedz(wierzcholek_macierz<wierzch> *wierzch1, wierzcholek_macierz<wierzch> *wierzch2, kraw nazwa_kraw){

    krawedz_macierz<kraw,wierzch> nowa_krawedz(nazwa_kraw);
    nowa_krawedz.wierzcholki[0] = wierzch1;
    nowa_krawedz.wierzcholki[1] = wierzch2;

    this->lista_krawedzi.dodaj_koniec(nowa_krawedz);
    this->lista_krawedzi.ostatni()->wartosc->miejsce_na_liscie = this->lista_krawedzi.ostatni();
    

    int indeks1 = wierzch1->indeks;
    int indeks2 = wierzch2->indeks;
    this->macierz[indeks1][indeks2] = this->lista_krawedzi.ostatni()->wartosc;
    this->macierz[indeks2][indeks1] = this->lista_krawedzi.ostatni()->wartosc;
}

template <typename kraw, typename wierzch>
wierzcholek_macierz<wierzch> *m_sasiedztwa<kraw, wierzch>::przeciwlegly_wierzch(wierzcholek_macierz<wierzch> *moj_wierzcholek, krawedz_macierz<kraw, wierzch> *krawedz){

    if(krawedz->wierzcholki[0] == moj_wierzcholek){
        return krawedz->wierzcholki[1];
    }
    if(krawedz->wierzcholki[1] == moj_wierzcholek){
        return krawedz->wierzcholki[0];
    }
    cout << "podany wierzcholek nie nalezy do wskazanej krawedzi" << endl;
    return nullptr;
}

template <typename kraw, typename wierzch>
krawedz_macierz<kraw, wierzch> **m_sasiedztwa<kraw, wierzch>::przylegle_krawedzie(wierzcholek_macierz<wierzch> *wierzcholek){

    int indeks = wierzcholek->indeks;
    return this->macierz[indeks];
}

template <typename kraw, typename wierzch>
ostream& operator << (ostream &strm, m_sasiedztwa<kraw, wierzch> graf){

    strm << graf.krawedzie()->rozmiar() << "\t"<< graf.wierzcholki()->rozmiar() << "\t"<< graf.wierzcholki()->pierwszy()->wartosc->nazwa << endl;

    typename lista< krawedz_macierz<kraw, wierzch> >::iterator it = graf.krawedzie();
    krawedz_macierz<kraw, wierzch> krawedz;

    int ilosc_krawedzi = graf.krawedzie()->rozmiar();
    for(int i=0;i<ilosc_krawedzi;i++){
        krawedz = *(it.wartosc());
        strm << krawedz.wierzcholki[0]->nazwa << "\t"<< krawedz.wierzcholki[1]->nazwa << "\t"<< krawedz.nazwa << endl;
        it++;
    }
    return strm;
}

template <typename kraw, typename wierzch>
istream& operator >> (istream &strm, m_sasiedztwa<kraw, wierzch> &graf){

    int ilosc_krawedzi;
    int ilosc_wierzcholkow;
    wierzch startowy;

    strm >> ilosc_krawedzi;
    strm >> ilosc_wierzcholkow;
    strm >> startowy;
    
    wierzch nazwa_w1;
    wierzch nazwa_w2;
    kraw nazwa_k;

    typename lista< wierzcholek_macierz<wierzch> >::iterator it = graf.wierzcholki();

    wierzcholek_macierz<wierzch> w1;
    wierzcholek_macierz<wierzch> w2;

    wierzcholek_macierz<wierzch> *wsk_w1;
    wierzcholek_macierz<wierzch> *wsk_w2;
    wsk_w1 = &w1;
    wsk_w2 = &w2;


    graf.dodaj_wierzcholek(startowy);
    for(int i=0;i<ilosc_krawedzi;i++){
        strm >> nazwa_w1;
        w1.nazwa = nazwa_w1;
        if(it.przeszukaj(w1) != nullptr){
            wsk_w1 = it.przeszukaj(w1)->wartosc;
        } else{
            graf.dodaj_wierzcholek(nazwa_w1);
            it.koniec();
            wsk_w1 = it.wartosc();
        }
        strm >> nazwa_w2;
        w2.nazwa = nazwa_w2;
        if(it.przeszukaj(w2) != nullptr){
            wsk_w2 = it.przeszukaj(w2)->wartosc;
        } else{
            graf.dodaj_wierzcholek(nazwa_w2);
            it.koniec();
            wsk_w1 = it.wartosc();
        }
        strm >> nazwa_k;
        graf.dodaj_krawedz(wsk_w1, wsk_w2, nazwa_k);
    }

    if(graf.wierzcholki()->rozmiar() != ilosc_wierzcholkow){
        cout << "niepoprawna ilośc wierzchołków" << endl;
    }
    return strm;
}

#endif