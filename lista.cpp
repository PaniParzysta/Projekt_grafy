#ifndef LISTA_CPP
#define LISTA_CPP

#include "h/pomocnicze.hh"

using namespace std;

template <typename typ>
lista<typ>::lista(){

    pierwszy_element = nullptr;
    ostatni_element = nullptr;
}

template<typename typ>
int lista<typ>::rozmiar(){

    if(this->czy_pusta() == false){
        unsigned int wielkosc = 1;                      //lista nie moze byc pusta
        element<typ> *ostatni = this->pierwszy_element;
        while(ostatni->nastepny != nullptr){
            ostatni = ostatni->nastepny;
            ++wielkosc;
        }
        return wielkosc;
    }
    return 0;
}

template <typename typ>
void lista<typ>::usun_element(element<typ>* do_usuniecia){

    //przypadek kiedy usuwamy jedyny element na liscie
    if(do_usuniecia->poprzedni == nullptr && do_usuniecia->nastepny == nullptr){
        pierwszy_element = nullptr;
        ostatni_element = nullptr;
        delete do_usuniecia;
    } else{
        // jesli pierwszy element na liscie
        if(do_usuniecia->poprzedni == nullptr && do_usuniecia->nastepny != nullptr){
            // jesli usuwamy pierwszy element na liscie
            // musimy nastepny uznac jako pierwszy
            this->pierwszy_element = do_usuniecia->nastepny;
            do_usuniecia->nastepny->poprzedni = nullptr;
            delete do_usuniecia;
        } else{
            // jesli ostatni na liscie
            if(do_usuniecia->nastepny == nullptr && do_usuniecia->poprzedni != nullptr){
                // jesli usuwamy ostatni element na liscie
                // musimy poprzedni uznac za ostatni
                this->ostatni_element = do_usuniecia->poprzedni;
                do_usuniecia->poprzedni->nastepny = nullptr;
                delete do_usuniecia;
            } else{ // srodkowy element
                do_usuniecia->poprzedni->nastepny = do_usuniecia->nastepny;
                do_usuniecia->nastepny->poprzedni = do_usuniecia->poprzedni;
                delete do_usuniecia;
            }
        }
    }
}

template <typename typ>
element<typ>* lista<typ>::pierwszy(){

    return this->pierwszy_element;
}

template <typename typ>
element<typ>* lista<typ>::ostatni(){

    return this->ostatni_element;
}

template <typename typ>
bool lista<typ>::czy_pusta(){

    if(this->pierwszy_element == nullptr){
        return true;            // zwraca true jesli lista jest pusta
    }
    return false;               // zwraca false jesli pierwszy element istnieje
}

template <typename typ>
void lista<typ>::wyczysc(){

    if(this->czy_pusta() == false){
        element<typ>* do_usuniecia = pierwszy_element;
        element<typ>* kolejny = pierwszy_element;
        while(do_usuniecia != nullptr){
            kolejny = do_usuniecia->nastepny;
            delete do_usuniecia;
            do_usuniecia = kolejny;
        }
        this->pierwszy_element = nullptr;
        this->ostatni_element = nullptr;
    }
}

template <typename typ>
lista<typ>::iterator::iterator(){

    this->aktualny_element = nullptr;
    this->przypisana_lista = nullptr;
}

template <typename typ>
lista<typ>::iterator::iterator(lista<typ> *moja_lista){

    this->aktualny_element = moja_lista->pierwszy();            // przy przypisaniu listy przypisuje jej pierwszy element
    this->przypisana_lista = moja_lista;
}


template <typename typ>
typ lista<typ>::iterator::iteruj(unsigned int numer_elem){

    if(this->przypisana_lista != nullptr){
        if(this->przypisana_lista->czy_pusta() == false){
            element<typ> *wybrany = this->przypisana_lista->pierwszy();
            for(unsigned int i=0;i<numer_elem;i++){
                if (wybrany->nastepny == nullptr){
                    cout<<"nie ma takiego elementu"<<endl;
                    cout<<"zwrocono pierwszy"<<endl;
                    return *(this->przypisana_lista->pierwszy()->wartosc);
                }
                wybrany = wybrany->nastepny;
            }
            this->aktualny_element = wybrany;               // przypisze adres elementu do pola aktualny_element
            return *(wybrany->wartosc);                     // jesli lista nie bedzie pusta zwroci wartosc elementu
        }
        cout << "lista pusta, zwrocono static_cast<typ>INT_MIN" << endl;
        return static_cast<typ>INT_MIN;                     // w razie pustej listy zwraca static_cast<typ>INT_MIN
    }
    cout << "nie przypisano listy, zwrocono static_cast<typ>INT_MIN" << endl;
    return static_cast<typ>INT_MIN;
}


template <typename typ>
typ lista<typ>::iterator::operator ++(){

    if(this->aktualny_element != nullptr){
        this->aktualny_element = this->aktualny_element->nastepny;
    }
    if(this->aktualny_element == nullptr){
        return *(this->przypisana_lista->pierwszy()->wartosc);
    }
    return *(this->aktualny_element->wartosc);
}

template <typename typ>
typ lista<typ>::iterator::operator ++(int){

    if(this->aktualny_element != nullptr){
        this->aktualny_element = this->aktualny_element->nastepny;
    }
    if(this->aktualny_element == nullptr){
        return *(this->przypisana_lista->pierwszy()->wartosc);
    }
    return *(this->aktualny_element->wartosc);
}

template <typename typ>
typ lista<typ>::iterator::operator --(){

    if(this->aktualny_element != nullptr){
        this->aktualny_element = this->aktualny_element->poprzedni;
    }
    if(this->aktualny_element == nullptr){
        return *(this->przypisana_lista->pierwszy()->wartosc);
    }
    return *(this->aktualny_element->wartosc);
}

template <typename typ>
typ lista<typ>::iterator::operator --(int){

    if(this->aktualny_element != nullptr){
        this->aktualny_element = this->aktualny_element->poprzedni;
    }
    if(this->aktualny_element == nullptr){
        return *(this->przypisana_lista->pierwszy()->wartosc);
    }
    return *(this->aktualny_element->wartosc);
}

template <typename typ>
void lista<typ>::iterator::operator =(lista<typ> &moja_lista){

    this->przypisana_lista = moja_lista;
    this->aktualny_element = moja_lista->pierwszy();
}

template <typename typ>
void lista<typ>::iterator::operator =(iterator moj_iter){

    this->aktualny_element = moj_iter.aktualny_element;
    this->przypisana_lista = moj_iter.przypisana_lista;
}

template <typename typ>
typ* lista<typ>::iterator::wartosc(){

    return this->aktualny_element->wartosc;
}

template <typename typ>
typ* lista<typ>::iterator::wartosc(int indeks){

    this->iteruj(indeks);
    return this->aktualny_element->wartosc;
}

template <typename typ>
element<typ>* lista<typ>::iterator::zwroc_elem(){

    return this->aktualny_element;
}

template <typename typ>
void lista<typ>::iterator::poczatek(){

    this->aktualny_element = this->przypisana_lista->pierwszy();
}

template <typename typ>
void lista<typ>::iterator::koniec(){

    this->aktualny_element = this->przypisana_lista->ostatni();
}

#endif