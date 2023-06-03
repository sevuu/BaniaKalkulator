// Program liczący opłacalność alkoholi
// na podstawie rownania spejsona (https://pastebin.com/raw/589tPqsy)

#include <iostream>

using namespace std;

struct STrunek{
	string nazwa;
    float ml;
    float procent,cena;
	float spejson;
	float etanol;
    void wczytaj();
    void etanolowanie();
    void spejsonowanie();
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

void STrunek::spejsonowanie(){
    if(ml!=500.0){
        float podzial = 500.0/ml;
        procent = procent/podzial;
    }
    float wspolczynnik = procent/cena;
    spejson = wspolczynnik;
}

void STrunek::etanolowanie(){
    float realprocent = procent/100;
    float ilealko = realprocent * ml;
    if(ml!=500.0){					// nie mam pojęcia dlaczego muszę to sprawdzać, ale z jakiegos powodu trzeba
        float podzial = 500.0/ml;
        ilealko = ilealko*podzial;
    }
    etanol = ilealko;
}

void STrunek::wczytaj(){
    cout<<"nazwa: ";
    cin.ignore();
    getline(cin,nazwa);
    cout<<"ml: ";
    cin>>ml;
    cout<<"woltaż: ";
    cin>>procent;
    cout<<"cena: ";
    cin>>cena;
	spejsonowanie();
	etanolowanie();
};



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
        cout<<"Ilosc etanolu w trunku "<<piwo[i].nazwa<<": "<<piwo[i].etanol<<"ml"<<endl;
        cout<<"Współczynnik spejsona: "<<piwo[i].spejson<<endl;
        cout<<endl;
    }
}

string SLista::najoplacalniejsze(){
	STrunek tmp = piwo[0];
	for(int i = 0; i<liczba; i++){
		if(piwo[i].spejson>tmp.spejson){
			tmp = piwo[i];
		}
	}
	return tmp.nazwa;
}

int main(int argc, const char** argv){
    SLista listapiw;
    listapiw.wczytaj();
    listapiw.wypisz();
	if(listapiw.liczba>1){
    	cout<<"Najopłacalniejszy alkohol: "<<listapiw.najoplacalniejsze()<<endl;
	}
    return 0;
}
