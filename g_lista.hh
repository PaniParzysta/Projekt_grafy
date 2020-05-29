#ifndef GRAFLISTA_HH
#define GRAFLISTA_HH

#include "pom_lista.hh"
#include "pomocnicze.hh"

template <typename kraw, typename wierzch>
class l_sasiedztwa{

    lista< wierzcholek_lista<kraw, wierzch> > lista_wierzcholkow;
    lista< krawedz_lista<kraw, wierzch> > lista_krawedzi;

    public:

    ~l_sasiedztwa();

    void dodaj_wierzcholek( wierzch nazwa );
    void dodaj_krawedz( wierzcholek_lista<kraw, wierzch> *wierzch1, wierzcholek_lista<kraw, wierzch> *wierzch2, kraw nazwa_kraw );
    void usun_wierzcholek( wierzcholek_lista<kraw, wierzch> *do_usuniecia );           // usuwa też przylegajace krawedzie
    void usun_krawedz( krawedz_lista<kraw, wierzch> *do_usuniecia );

    wierzcholek_lista<kraw, wierzch> *przeciwlegly_wierzch( wierzcholek_lista<kraw, wierzch> *moj_wierzcholek, krawedz_lista<kraw, wierzch> *krawedz );
    lista< krawedz_lista<kraw, wierzch> *> *przylegle_krawedzie( wierzcholek_lista<kraw, wierzch> *wierzcholek );

    lista< wierzcholek_lista<kraw, wierzch> > *wierzcholki(){
        return &this->lista_wierzcholkow;
        }
    lista< krawedz_lista<kraw, wierzch> > *krawedzie(){
        return &this->lista_krawedzi;
        }
};

template <typename kraw, typename wierzch>
std::ostream& operator << ( std::ostream &strm, l_sasiedztwa<kraw, wierzch> graf );

template <typename kraw, typename wierzch>
std::istream& operator >> ( std::istream &strm, l_sasiedztwa<kraw, wierzch> &graf );

#include "cpp/g_lista.cpp"

#endif