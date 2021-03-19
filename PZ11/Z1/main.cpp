#include <stdio.h>
#include <iostream>
#include <list>
#include <stdexcept>
#include <new>
using namespace std;

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
int main() {
    
    return 0;
}