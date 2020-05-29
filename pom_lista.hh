#ifndef ELEMENT_L_HH
#define ELEMENT_L_HH

#include "pomocnicze.hh"

template <typename kraw, typename wierzch> struct krawedz_lista;
template <typename kraw, typename wierzch> struct wierzcholek_lista;

template <typename kraw, typename wierzch>
struct wierzcholek_lista{

    element< wierzcholek_lista< kraw, wierzch > > *miejsce_na_liscie;          // wskazuje miejsce na liscie, ktore zajmuje wierzcholek
    wierzch nazwa;
    lista< krawedz_lista< kraw, wierzch >* > *krawedzie;                       // wskazniki na krawedzie wychodzace z wierzcholka

    wierzcholek_lista();
    wierzcholek_lista( wierzch nowa_nazwa );

    bool operator == ( wierzcholek_lista< kraw, wierzch > por ){
        if( this->nazwa == por.nazwa ){
            return true;
            }
        return false;
    }
    bool operator > ( wierzcholek_lista< kraw, wierzch > por){
        if( this->nazwa > por.nazwa ){
            return true;
            } 
        return false;
    }
    bool operator >= ( wierzcholek_lista< kraw, wierzch > por){
        if( this->nazwa >= por.nazwa ){
            return true;
            } 
        return false;
    }
    bool operator < ( wierzcholek_lista< kraw, wierzch > por ){
        if( this->nazwa < por.nazwa ){
            return true;
            }
        return false;
    }
    bool operator <= ( wierzcholek_lista< kraw, wierzch > por){
        if( this->nazwa <= por.nazwa ){
            return true;
            }
        return false;
    }

};


template <typename kraw, typename wierzch>
struct krawedz_lista{

    element< krawedz_lista<kraw, wierzch> > *miejsce_na_liscie;
    kraw nazwa;
    wierzcholek_lista<kraw, wierzch> *wierzcholki[2];
    element< krawedz_lista<kraw, wierzch>* > *krawedzie_wierzcholka[2];

    krawedz_lista();
    krawedz_lista(kraw nowa_nazwa);

    bool operator == ( krawedz_lista<kraw, wierzch> por ){
        if(this->nazwa == por.nazwa){
            return true;
        }
        return false;
    }
    bool operator > ( krawedz_lista<kraw, wierzch> por ){
        if(this->nazwa > por.nazwa){
            return true;
        }
        return false;
    }
    bool operator >= ( krawedz_lista<kraw, wierzch> por ){
        if(this->nazwa >= por.nazwa){
            return true;
        }
        return false;
    }
    bool operator < ( krawedz_lista<kraw, wierzch> por ){
        if(this->nazwa < por.nazwa){
            return true;
            }
        return false;
    }
    bool operator <= ( krawedz_lista<kraw, wierzch> por ){
        if(this->nazwa <= por.nazwa){
            return true;
            }
        return false;
    }
};

template <typename kraw, typename wierzch>
wierzcholek_lista<kraw, wierzch>::wierzcholek_lista(){

    this->krawedzie = new lista< krawedz_lista<kraw, wierzch>* >;      // lista wskaznikow na krawedz
    this->miejsce_na_liscie = nullptr;
}

template <typename kraw, typename wierzch>
krawedz_lista<kraw, wierzch>::krawedz_lista(){

    this->krawedzie_wierzcholka[0] = nullptr;
    this->krawedzie_wierzcholka[1] = nullptr;
    this->miejsce_na_liscie = nullptr;
    this->wierzcholki[0] = nullptr;
    this->wierzcholki[1] = nullptr;
}

#endif