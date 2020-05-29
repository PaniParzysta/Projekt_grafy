#ifndef GRAFMACIERZ_HH
#define GRAFMACIERZ_HH

#include "pomocnicze.hh"
#include "pom_macierz.hh"


template<typename kraw, typename wierzch>
class m_sasiedztwa{

    lista< wierzcholek_macierz<wierzch> > lista_wierzcholkow;
    lista< krawedz_macierz<kraw, wierzch> > lista_krawedzi;
    krawedz_macierz<kraw, wierzch> ***macierz;                         // wskaznik na dwuwymiarowa tablice wskaznikow

    public:
    m_sasiedztwa();
    ~m_sasiedztwa();

    void dodaj_wierzcholek( wierzch nazwa );
    void dodaj_krawedz( wierzcholek_macierz<wierzch> *wierzch1, wierzcholek_macierz<wierzch> *wierzch2, kraw nazwa_kraw );

    wierzcholek_macierz<wierzch> *przeciwlegly_wierzch( wierzcholek_macierz<wierzch> *moj_wierzcholek, krawedz_macierz<kraw, wierzch> *krawedz );
    krawedz_macierz<kraw, wierzch> **przylegle_krawedzie( wierzcholek_macierz<wierzch> *wierzcholek );            // zwraca wskaznik na wiersz w macierzy

    lista< wierzcholek_macierz<wierzch> > *wierzcholki(){
        return &this->lista_wierzcholkow;
        }
    lista< krawedz_macierz<kraw, wierzch> > *krawedzie(){
        return &this->lista_krawedzi;
        }
};

template <typename kraw, typename wierzch>
std::ostream& operator << ( std::ostream &strm, m_sasiedztwa<kraw, wierzch> graf );

template <typename kraw, typename wierzch>
std::istream& operator >> ( std::istream &strm, m_sasiedztwa<kraw, wierzch> &graf );

#include "cpp/g_macierz.cpp"

#endif