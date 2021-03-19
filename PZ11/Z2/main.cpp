#include <stdio.h>
#include <iostream>
#include <list>
#include <stdexcept>
#include <new>
using namespace std;
const int VEL=1000;

template <typename Tip>
class Lista {
public:
    Lista();
    virtual ~Lista() {}
    virtual int brojElemenata() const=0;
    virtual const Tip trenutni() const=0;
    virtual Tip &trenutni()=0;
    virtual bool prethodni()=0;
    virtual bool sljedeci()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual void obrisi()=0;
    virtual void dodajIspred(const Tip& el)=0;
    virtual void dodajIza(const Tip& el)=0;
    virtual const Tip operator[] (int i) const =0;
    virtual Tip& operator[] (int i)=0;
};
template <typename Tip>
class NizLista : public Lista<Tip> {
    Tip* lista;
    int kapacitet, brElemenata, t;
public:
    NizLista(): Lista<Tip> (), lista(new Tip[VEL]), kapacitet(VEL), brElemenata(0), t(0) {}
    ~NizLista() { delete[] lista; }
  //  NizLista(const NizLista<Tip> &l);
  //  NizLista<Tip> &operator=(const NizLista<Tip> &l);
    int brojElemenata() const {return brElemenata; }
    virtual const Tip trenutni() const {
        if(brElemenata==0) throw"Izuzetak";
        return lista[t];
    }
    virtual Tip &trenutni() {
        if(brElemenata==0) throw "Izuzetak";
        return lista[t];
    }
    virtual bool prethodni(){
        if(brElemenata==0) throw "Izuzetak";
        if(t==0) return false;
        t--; return true;
    }
    virtual bool sljedeci(){
        if(brElemenata==0) throw "Izuzetak";
        if(t==brElemenata-1) return false;
        t++; return true;
    }
    virtual void pocetak() {
        if(brElemenata==0) throw"Izuzetak";
        t=0;
    }
    virtual void kraj() {
        if(brElemenata==0) throw"Izuzetak";
        t=brElemenata-1;
    }
  //  virtual void obrisi();
  //  virtual void dodajIspred(const Tip& el);
 //   virtual void dodajIza(const Tip& el);
    virtual const Tip operator[] (int i) const{
        if(i<0 || i>=brElemenata) throw "Izuzetak";
        return lista[i];
    }
    virtual Tip& operator[] (int i) {
        if(i<0 || i>=brElemenata) throw"Izuzetak";
        return lista[i];
    }
    NizLista<Tip> (const NizLista<Tip> &l) {
        kapacitet=l.kapacitet; brElemenata=l.brElemenata; t=l.t;
        lista= new Tip[l.kapacitet];
        for(int i=0; i<brElemenata; i++)
            lista[i]=l.lista[i];
    }
    NizLista<Tip> &operator=(const NizLista<Tip> &l) {
        if(this==&l) return *this;
        delete[] lista;
        kapacitet=l.kapacitet; brElemenata=l.brElemenata; t=l.t;
        lista= new Tip[l.kapacitet];
        for(int i=0; i<brElemenata; i++)
            lista[i]=l.lista[i];
        return *this;
    }
    void obrisi(){
        if(brElemenata==0) throw "Izuzetak";
        for(int i=t; i<brElemenata-1;i++) {
            lista[i]=lista[i+1];
        }
        brElemenata--;
        if(t==brElemenata && brElemenata>0) t--;
    }
    void dodajIspred(const Tip& el) {
        if(brElemenata==kapacitet) {
            kapacitet*=2;
            Tip* n_lista= new Tip[kapacitet];
            for(int i=0; i<brElemenata;i++)
                n_lista[i]=lista[i];
            delete[] lista;
            lista=n_lista;
        }
        for(int i=brElemenata; i>t;i--)
            lista[i]=lista[i-1];
        lista[t]=el;
        brElemenata++;
        if (brElemenata!=1) t++;
    }
    void dodajIza(const Tip& el) {
        if(brElemenata==kapacitet) {
            kapacitet*=2;
            Tip* n_lista= new Tip[kapacitet];
            for(int i=0; i<brElemenata;i++)
                n_lista[i]=lista[i];
            delete[] lista;
            lista=n_lista;
        }
        for(int i=brElemenata;i>t+1;i--)
            lista[i]=lista[i-1];
        lista[t+1]=el;
        brElemenata++;
    }
};
int main() {
    
    try {
    NizLista<int> listica;
    
    listica.dodajIspred(5);
    listica.dodajIza(3);
    listica.dodajIza(6);
    listica[0]=2;
    for(int i=0;i<listica.brojElemenata();i++)
        cout<<listica[i];
    listica.pocetak();
    listica.trenutni()=2;
    listica.sljedeci();
    cout<<listica.trenutni();
    listica.prethodni();
    listica.obrisi();
    listica.kraj();
    for(int i=0;i<listica.brojElemenata();i++)
        cout<<listica[i];
    }
    catch(...) {
        cout<<"Izuzetak";
    }
    
    return 0;
}
    
    
    