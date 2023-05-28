// Program liczący opłacalność alkoholi
// na podstawie rownania spejsona (https://pastebin.com/raw/589tPqsy)

#include <iostream>

using namespace std;

struct STrunek{
    char nazwa[64];
    float ml;
    float procent,cena;
    void wczytaj();
    float etanol();
    float spejson();
};

struct SLista{
    int liczba;
    STrunek* piwo;
    void wczytaj();
    void wypisz();
    string najoplacalniejsze();
    ~SLista(){
        liczba = 0;
        if(!(piwo==nullptr)){
            delete [] piwo;
            piwo = 0;
        }
    }
};

void STrunek::wczytaj(){
    cout<<"nazwa: ";
    cin.ignore();
    cin.getline(nazwa,64);
    cout<<"ml: ";
    cin>>ml;
    cout<<"woltaż: ";
    cin>>procent;
    cout<<"cena: ";
    cin>>cena;
};

float STrunek::etanol(){
    // obliczanie ile jest czystego alkoholu w trunku
    float realprocent = procent/100;
    float ilealko = realprocent * ml;
    return ilealko;
}

float STrunek::spejson(){
    if(ml!=500.0){
        float podzial = 500.0/ml;
        procent = procent/podzial;
    }
    float wspolczynnik = procent/cena;
    return wspolczynnik;
}

void SLista::wczytaj(){
    cout<<"Liczba trunków do porównania: ";
    cin>>liczba;
    piwo = new STrunek [liczba];
    for(int i = 0; i<liczba;i++){
        cout<<"========Trunek nr "<<i+1<<"========"<<endl;
        piwo[i].wczytaj();
    }
}

void SLista::wypisz(){
    cout<<"==========Wyniki==========="<<endl;
    for(int i = 0; i<liczba;i++){
        cout<<"Ilosc etanolu w trunku "<<piwo[i].nazwa<<": "<<piwo[i].etanol()<<"ml"<<endl;
        cout<<"Współczynnik spejsona: "<<piwo[i].spejson()<<endl;
        cout<<endl;
    }

}

string SLista::najoplacalniejsze(){
    float tmp = piwo[0].spejson();
    string tmpnazwa;
    for(int i = 0; i<liczba; i++){
        if(piwo[i].spejson()>tmp){
            tmp = piwo[i].spejson();
            string nazwastring(piwo[i].nazwa);
            tmpnazwa = nazwastring;
        }
    }
    return tmpnazwa;
}

int main(int argc, const char** argv){
    SLista listapiw;
    listapiw.wczytaj();
    listapiw.wypisz();
    cout<<"Najopłacalniejszy alkohol: "<<listapiw.najoplacalniejsze()<<endl;
    return 0;
}