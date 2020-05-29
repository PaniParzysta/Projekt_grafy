#ifndef GRAF_L_CPP
#define GRAF_L_CPP

#include "h/g_lista.hh"
using namespace std;

template <typename kraw, typename wierzch>
l_sasiedztwa<kraw, wierzch>::~l_sasiedztwa(){

    while(this->lista_wierzcholkow.czy_pusta() == false){
        this->usun_wierzcholek(lista_wierzcholkow.pierwszy()->wartosc);
    }
}

template <typename kraw, typename wierzch>
void l_sasiedztwa<kraw, wierzch>::dodaj_wierzcholek(wierzch nazwa){

    wierzcholek_lista<kraw, wierzch> nowy_wierzcholek(nazwa);               // tworzy wierzcholek o nazwie
    this->lista_wierzcholkow.dodaj_koniec(nowy_wierzcholek);  //dodaje wierzcholek na koniec listy
    this->lista_wierzcholkow.ostatni()->wartosc->miejsce_na_liscie = this->lista_wierzcholkow.ostatni();
}

template <typename kraw, typename wierzch>
void l_sasiedztwa<kraw, wierzch>::dodaj_krawedz(wierzcholek_lista<kraw, wierzch> *wierzch1, wierzcholek_lista<kraw, wierzch> *wierzch2, kraw nazwa_kraw){

    krawedz_lista<kraw,wierzch> nowa_krawedz(nazwa_kraw);
    nowa_krawedz.wierzcholki[0] = wierzch1;
    nowa_krawedz.wierzcholki[1] = wierzch2;

    this->lista_krawedzi.dodaj_koniec(nowa_krawedz);
    this->lista_krawedzi.ostatni()->wartosc->miejsce_na_liscie = this->lista_krawedzi.ostatni();

    krawedz_lista<kraw, wierzch> *wskaznik_na_krawedz = this->lista_krawedzi.ostatni()->wartosc;
    wskaznik_na_krawedz->wierzcholki[0]->krawedzie->dodaj_koniec(wskaznik_na_krawedz);
    wskaznik_na_krawedz->wierzcholki[1]->krawedzie->dodaj_koniec(wskaznik_na_krawedz);
    wskaznik_na_krawedz->krawedzie_wierzcholka[0] = wierzch1->krawedzie->ostatni(); // przypisuje wskaznik na pozycje na liscie krawedzi wierzcholka
    wskaznik_na_krawedz->krawedzie_wierzcholka[1] = wierzch2->krawedzie->ostatni(); // przypisuje wskaznik na pozycje na liscie krawedzi wierzcholka
}

template <typename kraw, typename wierzch>
void l_sasiedztwa<kraw, wierzch>::usun_wierzcholek(wierzcholek_lista<kraw, wierzch>* do_usuniecia){

    typename lista< krawedz_lista<kraw, wierzch>* >::iterator it = do_usuniecia->krawedzie;
    lista< krawedz_lista<kraw, wierzch>* > *lst_kraw_wierzch = this->przylegle_krawedzie(do_usuniecia);

    while(lst_kraw_wierzch->czy_pusta() == false){          // konczy dzialanie petli gdy lista krawedzi wierzcholka bedzie pusta
        this->usun_krawedz(*(it.zwroc_elem()->wartosc));    // usuwa aktualny element z listy
        it.poczatek();                                      // za kazdym razem usuwamy pierwszy element
    }
    delete do_usuniecia->krawedzie;                         // usuwa liste krawedzi werzcholka po oproznieniu jej
    this->lista_wierzcholkow.usun_element(do_usuniecia->miejsce_na_liscie);
}

template <typename kraw, typename wierzch>
void l_sasiedztwa<kraw, wierzch>::usun_krawedz(krawedz_lista<kraw, wierzch>* do_usuniecia){

    do_usuniecia->wierzcholki[0]->krawedzie->usun_element(do_usuniecia->krawedzie_wierzcholka[0]);
    do_usuniecia->wierzcholki[1]->krawedzie->usun_element(do_usuniecia->krawedzie_wierzcholka[1]);
    this->lista_krawedzi.usun_element(do_usuniecia->miejsce_na_liscie);
}

template <typename kraw, typename wierzch>
wierzcholek_lista<kraw, wierzch> *l_sasiedztwa<kraw, wierzch>::przeciwlegly_wierzch(wierzcholek_lista<kraw, wierzch> *moj_wierzcholek, krawedz_lista<kraw, wierzch> *krawedz){

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
lista< krawedz_lista<kraw, wierzch> *> *l_sasiedztwa<kraw, wierzch>::przylegle_krawedzie(wierzcholek_lista<kraw, wierzch> *wierzcholek){

    return wierzcholek->krawedzie;
}

template <typename kraw, typename wierzch>
ostream& operator << (ostream &strm, l_sasiedztwa<kraw, wierzch> graf){

    strm << graf.krawedzie()->rozmiar() << "\t" << graf.wierzcholki()->rozmiar() << "\t" << graf.wierzcholki()->pierwszy()->wartosc->nazwa << endl;

    typename lista< krawedz_lista<kraw, wierzch> >::iterator it = graf.krawedzie();
    krawedz_lista<kraw, wierzch> krawedz;

    int ilosc_krawedzi = graf.krawedzie()->rozmiar();
    for(int i=0;i<ilosc_krawedzi;i++){
        krawedz = *(it.wartosc());
        strm << krawedz.wierzcholki[0]->nazwa << "\t" << krawedz.wierzcholki[1]->nazwa << "\t" << krawedz.nazwa << endl;
        it++;
    }
    return strm;
}

template <typename kraw, typename wierzch>
istream& operator >> (istream &strm, l_sasiedztwa<kraw, wierzch> &graf){

    int ilosc_krawedzi;
    int ilosc_wierzcholkow;
    wierzch startowy;

    strm >> ilosc_krawedzi;
    strm >> ilosc_wierzcholkow;
    strm >> startowy;
    
    wierzch nazwa_w1;
    wierzch nazwa_w2;
    kraw nazwa_k;

    typename lista< wierzcholek_lista<kraw, wierzch> >::iterator it = graf.wierzcholki();


    wierzcholek_lista<kraw, wierzch> w1;
    wierzcholek_lista<kraw, wierzch> w2;

    wierzcholek_lista<kraw, wierzch> *wsk_w1;
    wierzcholek_lista<kraw, wierzch> *wsk_w2;
    wsk_w1 = &w1;
    wsk_w2 = &w2;


    graf.dodaj_wierzcholek(startowy);
    for(int i=0;i<ilosc_krawedzi;i++){

        strm >> nazwa_w1;
        w1.nazwa = nazwa_w1;

        if(it.przeszukaj(w1) != nullptr){               // jesli istnieje wierzcholek o podanej nazwie
            wsk_w1 = it.przeszukaj(w1)->wartosc;        //wskazuje na juz istniejacy wierzcholek o podanej nazwie

        } else{                                         // jesli wierzcholek nie istnieje, dodaje go

            graf.dodaj_wierzcholek(nazwa_w1);
            it.koniec();                                // it wskazuje na dodany wierzcholek
            wsk_w1 = it.wartosc();                      // zwraca wskaznik na dodany
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
        cout << "Blad" << endl;
    }

    return strm;
}

#endif