#ifndef ELEMENT_M_HH
#define ELEMENT_M_HH

#include "pomocnicze.hh"

template<typename typ>
struct wierzcholek_macierz{

    int indeks;                                             // indeks w macierzy
    element< wierzcholek_macierz<typ> > *miejsce_na_liscie; // wskazuje miejsce na liscie, ktore zajmuje wierzcholek
    typ nazwa;                                              // nazwa wierzolka

    wierzcholek_macierz();
    wierzcholek_macierz(typ nowa_nazwa);

    bool operator == ( wierzcholek_macierz<typ> por ){
        if( this->nazwa == por.nazwa ){
            return true;
            }
        return false;
    }
    bool operator > ( wierzcholek_macierz<typ> por ){
        if( this->nazwa > por.nazwa ){
            return true;
            }
        return false;
    }
    bool operator >= ( wierzcholek_macierz<typ> por ){
        if( this->nazwa >= por.nazwa ){
            return true;
            }
        return false;
    }
    bool operator < (wierzcholek_macierz<typ> por){
        if(this->nazwa < por.nazwa){
            return true;
            }
        return false;
    }
    bool operator <= ( wierzcholek_macierz<typ> por ){
        if( this->nazwa <= por.nazwa ){
            return true;
            }
        return false;
    }
};

template <typename kraw, typename wierzch>
struct krawedz_macierz{

    element< krawedz_macierz<kraw, wierzch> > *miejsce_na_liscie;    // wskazuje miejsce na liscie, ktore zajmuje krawedz
    kraw nazwa;                                                      // nazwa krawedzi
    wierzcholek_macierz<wierzch> *wierzcholki[2];

    krawedz_macierz();
    krawedz_macierz( kraw nowa_nazwa );

    bool operator == ( krawedz_macierz<kraw, wierzch> por ){
        if( this->nazwa == por.nazwa ){
            return true;
            }
        return false;
    }
    bool operator > ( krawedz_macierz<kraw, wierzch> por ){
        if( this->nazwa > por.nazwa ){
            return true;
            }
        return false;
    }
    bool operator >= ( krawedz_macierz<kraw, wierzch> por ){
        if(this->nazwa >= por.nazwa){
            return true;
            }
        return false;
    }
    bool operator < ( krawedz_macierz<kraw, wierzch> por ){
        if(this->nazwa < por.nazwa){
            return true;
            }
        return false;
    }
    bool operator <= ( krawedz_macierz<kraw, wierzch> por ){
        if(this->nazwa <= por.nazwa){
            return true;
            }
        return false;
    }

};

template<typename typ>
wierzcholek_macierz<typ>::wierzcholek_macierz(){

    this->miejsce_na_liscie = nullptr;
    this->indeks = -1;                          //brak indeksu
}

template<typename kraw, typename wierzch>
krawedz_macierz<kraw, wierzch>::krawedz_macierz(){

    this->miejsce_na_liscie = nullptr;
    this->wierzcholki[0] = nullptr;
    this->wierzcholki[1] = nullptr;
}

#endif