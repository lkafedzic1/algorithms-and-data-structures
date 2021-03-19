#include <iostream>
#include <stdexcept>
using namespace std;

template <typename Tip>
class Lista{
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
    virtual void dodajIspred(const Tip& el)=0;
    virtual void dodajIza(const Tip &el)=0;
    virtual Tip operator[](int i) const=0;
    virtual Tip& operator[](int i)=0;
};
template <typename Tip>
class Stek {
    int brElemenata;
    struct Cvor {
        Cvor* sljedeci;
        Tip element;
        Cvor(const Tip& el): element(el), sljedeci(nullptr) {}
        Cvor(const Cvor &c): element(c.element), sljedeci(new Cvor(c.sljedeci)) {}
    };
    Cvor* p_vrh;
    public:
    Stek(): p_vrh(nullptr), brElemenata(0) {}
    ~Stek() {brisi();} //destr, konstr. kopije i op. dodjele:
    Stek(const Stek& s);
    Stek &operator=(const Stek& s);
    void brisi();
    void stavi(const Tip& el);
    Tip skini();
    Tip &vrh() const {
        if(brElemenata==0) throw "Izuzetak";
        return p_vrh->element;
    }
    int brojElemenata() const {return brElemenata;}
};

template<typename Tip>
Stek<Tip>::Stek(const Stek& s) {
    brElemenata=s.brElemenata;
    Cvor* p(s.p_vrh);
    p_vrh=new Cvor(s.p_vrh->element);
    Cvor* p1(p_vrh);
    while(p->sljedeci!=nullptr) {
        p=p->sljedeci;
        p1->sljedeci=new Cvor(p->element);
        p1=p1->sljedeci;
    }
    p1->sljedeci=nullptr;
}
template<typename Tip>
Stek<Tip> &Stek<Tip>::operator=(const Stek& s) {
    if(this==&s) return *this;
    if(brElemenata>0) brisi(); //kopirajuci konstruktor 
    brElemenata=s.brElemenata;
    Cvor* p(s.p_vrh);
    p_vrh=new Cvor(s.p_vrh->element);
    Cvor* p1(p_vrh);
    while(p->sljedeci!=nullptr) {
        p=p->sljedeci;
        p1->sljedeci=new Cvor(p->element);
        p1=p1->sljedeci;
    }
    p1->sljedeci=nullptr;
    return *this;
}

template<typename Tip>
void Stek<Tip>::brisi() {
    if(brElemenata!=0) {
        Cvor* p=p_vrh;
        while(p!=nullptr) {
            p_vrh=p_vrh->sljedeci;
            delete p;
            p=p_vrh;
            brElemenata--;
        }
        delete p;
        p=nullptr; 
        p_vrh=nullptr; 
    }
}
template<typename Tip>
void Stek<Tip>::stavi(const Tip& el) {
    Cvor *c=new Cvor(el);
    if(brElemenata==0)  p_vrh=c;
    else {
        c->sljedeci=p_vrh;
        p_vrh=c;
    }
    brElemenata++;
}
template <typename Tip>
Tip Stek<Tip>::skini() {
    if(brElemenata==0) throw "Izuzetak";
    Tip el=p_vrh->element;
    Cvor* p=p_vrh;
    p_vrh=p_vrh->sljedeci;
    delete p;
    brElemenata--;
    return el;
}
//testiranje metoda
bool testbrisi() {
    Stek<int>s;
    for(int i=5;i<=3;i++) s.stavi(i);
    s.brisi();
    if(s.brojElemenata()==0) return true;
    return false;
}//5
bool teststavi() {
    Stek<int> s;
    s.stavi(1);
    s.stavi(3);
    if(s.brojElemenata()==2) return true;
    return false;
} //1
bool testskini() {
    Stek<int> s;
    s.stavi(5);
    s.stavi(3);
    s.skini();
    if(s.brojElemenata()==1) return true;
    return false;
}//4
bool testvrh() {
    Stek<int>s;
    for(int i=7;i>=2;i--) 
        s.stavi(i);
    if(s.vrh()==2) return true;
    return false;
} //2
bool testbrojElemenata() {
    Stek<int>s;
    if(s.brojElemenata()==0)return true;
    return false;
}//3

int main() {
    try {
        if(teststavi()) cout<<"Test 1 je ispravan";
        else cout<<"Test 1 nije ispravan";
        cout<<endl;
        if(testvrh()) cout<<"Test 2 je ispravan";
        else cout<<"Test 2 nije ispravan";
        cout<<endl;
        if(testbrojElemenata()) cout<<"Test 3 je ispravan";
        else cout<<"Test 3 nije ispravan";
        cout<<endl;
        if(testskini()) cout<<"Test 4 je ispravan";
        else cout<<"Test 4 nije ispravan";
        cout<<endl;        
        if(testskini()) cout<<"Test 5 je ispravan";
        else cout<<"Test 5 nije ispravan";
        cout<<endl;
    }
    catch(...) {
        cout<<"Izuzetak je uhvaćen! ";
    }

    return 0;
}
