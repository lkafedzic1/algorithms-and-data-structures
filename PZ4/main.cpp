#include <iostream>
#include <stdexcept>

using namespace std;

template <typename Tip>
class Lista {
    public:
    Lista() {}
    virtual ~Lista() {}
    virtual int brojElemenata() const=0;
    virtual Tip trenutni() const=0;
    virtual Tip &trenutni()=0;
    virtual bool prethodni()=0;
    virtual bool sljedeci()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual void obrisi()=0;
    virtual void dodajIspred(const Tip &el)=0;
    virtual void dodajIza(const Tip &el)=0;
    virtual Tip &operator[](int i)=0;
    virtual Tip operator[](int i) const=0;
};

template<typename Tip>
class Red {
    struct Cvor {
        Tip element;
        Cvor* sljedeci;
        Cvor(Tip el=0): element(el), sljedeci(nullptr) {}
        Cvor(const Cvor& c) :element(c.element),sljedeci(new Cvor(c.element)) {}
    };
    Cvor* p_celo;
    Cvor* p_zacelje;
    int brElemenata;
    public:
    Red(): p_celo(nullptr), p_zacelje(nullptr), brElemenata(0) {}
    ~Red() {brisi();} //destr, konstr. kopije, op. dodjele
    Red (const Red &r);
    Red &operator=(const Red &r);
    void brisi();
    void stavi(const Tip& el);
    Tip skini();
    Tip& celo() {
        if(brElemenata==0) throw "Izuzetak";
        return p_celo->element;
    }
    int brojElemenata() const {return brElemenata;}
};
template<typename Tip>
Red<Tip>::Red(const Red& r) {
    brElemenata=r.brElemenata;
    Cvor* p(r.p_celo);
   /* p_celo=new Cvor;
    p_celo->element=r.p_celo->element;
    if(brElemenata==0) {p_zacelje=p_celo;}
    else {
        Cvor* p1(p_celo);
        while(p->sljedeci!=nullptr) {
            p=p->sljedeci;
            p1->sljedeci=new Cvor(p->element);
            p1=p1->sljedeci;
        }
        p_zacelje=new Cvor(r.p_zacelje->element);
        p_zacelje->sljedeci=nullptr;
    }*/
    p_zacelje=new Cvor;
    p_celo=p_zacelje;
    while(p!=r.p_zacelje) {
        p_zacelje->element=p->element;
        p_zacelje->sljedeci=new Cvor;
        p=p->sljedeci;
        p_zacelje=p_zacelje->sljedeci;
    }
    p_zacelje->element=p->element;
    p_zacelje->sljedeci=nullptr;
}
template<typename Tip>
Red<Tip> &Red<Tip>::operator=(const Red& r) {
    if(this==&r) return *this;
    if(brElemenata!=0) brisi();
    //tijelo kopirajuceg k.
    brElemenata=r.brElemenata;
    Cvor* p(r.p_celo);
    p_zacelje=new Cvor;
    p_celo=p_zacelje;
    while(p!=r.p_zacelje) {
        p_zacelje->element=p->element;
        p_zacelje->sljedeci=new Cvor;
        p=p->sljedeci;
        p_zacelje=p_zacelje->sljedeci;
    }
    p_zacelje->element=p->element;
    p_zacelje->sljedeci=nullptr;
    return *this;
}
template<typename Tip>
void Red<Tip>::brisi() {
    if(brElemenata!=0) {
        Cvor*p=p_celo;
        while(p->sljedeci!=nullptr) {
            p_celo=p_celo->sljedeci;
            delete p;
            p=p_celo;
    }
    delete p;
    
    //
    brElemenata=0;
    }
}
template<typename Tip>
void Red<Tip>::stavi(const Tip& el) {
    Cvor* c=new Cvor(el);
    if(brElemenata==0) {
        p_celo=c;   
        p_zacelje=c; 
    }
    else {
        c->element=el;
        c->sljedeci=nullptr;
        p_zacelje->sljedeci=c;
        p_zacelje=c;
    }
    brElemenata++;
}
template<typename Tip>
Tip Red<Tip>::skini() {
    if(brElemenata==0) throw "Izuzetak! ";
    Tip el(p_celo->element); 
    if(p_celo==p_zacelje) { 
        delete p_zacelje;
    }
    else {
        Cvor* p(p_celo);
        p_celo=p_celo->sljedeci;
        delete p;
    }
    brElemenata--;
    return el;
}
//testiranje metoda
bool test1() {
    Red<int>r;
    for(int i=6;i<4;i++) r.stavi(i);
    r.brisi();
    if(r.brojElemenata()==0) return true;
    return false;
}
bool test2() {
    Red<int> r;
    r.stavi(10);
    r.stavi(10);
    r.stavi(10);
    if(r.brojElemenata()==3) return true;
    return false;
} 
bool test3() {
    Red<int> r;
    r.stavi(5);
    r.stavi(0);
    r.skini();
    if(r.brojElemenata()==1) return true;
    return false;
}
bool test4() {
    Red<int>r;
    for(int i=5;i>=2;i--) 
        r.stavi(i);
    if(r.celo()==5) return true;
    return false;
} 
bool test5() {
    Red<int>r;
    if(r.brojElemenata()==0)return true;
    return false;
}

int main() {
    cout<<test1()<<endl<<test2()<<endl<<test3()<<endl<<test4()<<endl<<test5()<<endl<<"Kraj testiranja.";
    return 0;
}
