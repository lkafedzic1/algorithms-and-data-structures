#include <iostream>
#include <stdexcept>
using namespace std;

template<typename Tip>
class DvostraniRed {   
    int brElemenata;
    struct Cvor {
        Tip element;
        Cvor *sljedeci, *prethodni;
        Cvor(Tip el=0): element(el), sljedeci(nullptr), prethodni(nullptr) {}
    };
    Cvor *p_celo, *p_zacelje;
public:
    DvostraniRed(): brElemenata(0), p_celo(nullptr), p_zacelje(nullptr){}
    ~DvostraniRed() {brisi(); }
    DvostraniRed(const DvostraniRed<Tip> &r);
    DvostraniRed &operator =(const DvostraniRed<Tip> &r);
    void brisi() {
        while(brElemenata!=0){
            skiniSaVrha();
        }
    }
    int brojElemenata() const {return brElemenata;}
    void staviNaVrh(const Tip &el);
    Tip skiniSaVrha();
    void staviNaCelo(const Tip &element);
    Tip skiniSaCela();
    Tip &vrh(){
        if(brElemenata==0) throw "Izuzetak!";
        return p_zacelje->element;
    }
    Tip &celo(){
        if(brElemenata==0) throw "Izuzetak!";
        return p_celo->element;
    }
};    
template<typename Tip>
DvostraniRed<Tip>& DvostraniRed<Tip>::operator =(const DvostraniRed<Tip> &r) {
        if(this==&r) return *this;
        brisi();
        brElemenata=r.brElemenata;
        Cvor *p1=r.p_celo,*p2=nullptr;
        while(p1!=nullptr) {
            Cvor *el= new Cvor();
            el->element=p1->element;
            if(p1==r.p_celo) {
                p_celo=el;
            } else {
                p2->sljedeci=el;
                el->prethodni=p2;
            }
            p2=el;
            p1=p1->sljedeci;
        }
        p2->sljedeci=nullptr;
        p_zacelje=p2;
        return *this;
    }

template <typename Tip>
DvostraniRed<Tip>::DvostraniRed(const DvostraniRed<Tip> &r) {
        brElemenata=r.brElemenata;
        Cvor *p1=r.p_celo, *p2=nullptr;
        while(p1!=nullptr) {
            Cvor *el= new Cvor();
            el->element=p1->element;
            if(p1==r.p_celo) {
                p_celo=el;
            } else {
                p2->sljedeci=el;
                el->prethodni=p2;
            }
            p2=el;
            p1=p1->sljedeci;
        }
        p2->sljedeci=nullptr;
        p_zacelje=p2;
}
template<typename Tip>
void DvostraniRed<Tip>::staviNaVrh(const Tip &el) {
        Cvor *novi=new Cvor(el);
        if(brElemenata==0) {
            p_celo=novi;
            p_zacelje=novi;
        }else{
            novi->prethodni=p_zacelje;
            p_zacelje->sljedeci=novi;
            p_zacelje=novi;
        }
        brElemenata++;
}
template<typename Tip>
Tip DvostraniRed<Tip>::skiniSaVrha() {
        if(brElemenata==0) throw "Izuzetak!";
        Tip el=p_zacelje->element;
        if(brElemenata==1){
            delete p_zacelje;
        }else{
            Cvor *p=p_zacelje;
            p_zacelje=p_zacelje->prethodni;
            delete p;
        }
        brElemenata--;
        return el;
}
template<typename Tip>
void DvostraniRed<Tip>::staviNaCelo(const Tip &element) {
    Cvor *novi= new Cvor(element);
    if(brElemenata==0) {
        p_celo=novi;
        p_zacelje=novi;
    } else {
        novi->sljedeci=p_celo;
        p_celo->prethodni=novi;
        p_celo=novi;
    }
    brElemenata++;
}
template<typename Tip>
Tip DvostraniRed<Tip>::skiniSaCela() {
        if(brElemenata==0) throw "Izuzetak!";
        Tip el=p_celo->element;
        if(brElemenata==1) {
            delete p_zacelje;
        }else{
            Cvor *p=p_celo;
            p_celo=p_celo->sljedeci;
            delete p;
        }
        brElemenata--;
        return el;
}
//Metode testiranja
bool testbrisi() {
    DvostraniRed<int>s;
    for(int i=5;i<=3;i++) s.staviNaVrh(i);
    s.brisi();
    if(s.brojElemenata()==0) return true;
    return false;
}
bool teststavinavrh() {
    DvostraniRed<int> s;
    s.staviNaVrh(1);
    s.staviNaVrh(3);
    if(s.brojElemenata()==2) return true;
    return false;
}
bool teststavinacelo() {
    DvostraniRed<int> r;
    r.staviNaCelo(10);
    r.staviNaCelo(10);
    r.staviNaCelo(10);
    if(r.brojElemenata()==3) return true;
    return false;
}
bool testskinisavrha() {
    DvostraniRed<int> s;
    s.staviNaVrh(5);
    s.staviNaVrh(3);
    s.skiniSaVrha();
    if(s.brojElemenata()==1) return true;
    return false;
}
bool testskinisacela() {
     DvostraniRed<int> r;
    r.staviNaCelo(5);
    r.staviNaVrh(0);
    r.skiniSaCela();
    if(r.brojElemenata()==1) return true;
    return false;
}
bool testvrh(){
    DvostraniRed<int> s;
    for(int i=7;i>=2;i--) 
        s.staviNaVrh(i);
    if(s.vrh()==2) return true;
    return false;
}
bool testbrelemenata() {
    DvostraniRed<int>s;
    if(s.brojElemenata()==0)return true;
    return false;
}
bool testcelo(){
    DvostraniRed<int> r;
    r.staviNaCelo(6);
    if (r.celo()==6) return true;
    return false;
}

int main() {
    try{
    cout<<testbrisi()<<teststavinavrh()<<teststavinacelo()<<testskinisavrha()<<testskinisacela()<<testvrh()<<testbrelemenata()<<testcelo();
    } catch(...){
        cout<<"Izuzetak je uhvaćen.";
    }
    return 0;
}