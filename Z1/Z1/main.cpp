#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
using namespace std;

template <typename Tip>
class Lista {
    public:
    Lista() {}
    virtual ~Lista() {};
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
class It;

template<typename Tip>
class DvostrukaLista: public Lista<Tip> {
    int brElemenata;
    struct Cvor {
        Tip element;
        Cvor* prethodni, *sljedeci;
    };
    Cvor *poc, *poslj, *t;
public:
   friend class It<Tip>;
    DvostrukaLista() : brElemenata(0), poslj(nullptr), poc(nullptr), t(nullptr) {}
    ~DvostrukaLista() {
        while(poc!=nullptr) {
            t=poc;
            poc=poc->sljedeci;
            delete t;
        }
    }
    DvostrukaLista(const DvostrukaLista<Tip> &l);
    int brojElemenata() const override { return brElemenata;}
    Tip &trenutni() override {return t->element;}
    Tip trenutni() const override {return t->element;}
    bool prethodni() override  {
        if(t==poc) return false;
        t=t->prethodni;
        return true;
    }
    bool sljedeci() override{
        if(t==poslj) return false;
        t=t->sljedeci;
        return true;
    }
    void pocetak() override{
        if(brElemenata==0) throw "Izuzetak";
        t=poc;
    }
    void kraj() override{
        if(brElemenata==0) throw "Izuzetak!";
        t=poslj;
    }
    void obrisi() override;
    void dodajIspred(const Tip& el) override ;
    void dodajIza(const Tip& el) override ;
    Tip operator [] (int i) const override {
        Cvor *pom=poc;
        for(int j=0; j<i; j++) pom=pom->sljedeci;
        return pom->element;
    }
    Tip &operator [] (int i) override {
        Cvor *pom=poc;
        for(int j=0; j<i; j++) pom=pom->sljedeci;
        return pom->element;
    }
    DvostrukaLista& operator=(const DvostrukaLista<Tip> &l);
};
template<typename Tip>
void DvostrukaLista<Tip>::obrisi() {
        if(poc==nullptr) throw "Izuzetak!";
        if(brElemenata==1) {
            delete t;
            poc=nullptr;
            poslj=nullptr;
            t=nullptr;
        } else if(t==poc) {
            poc=t->sljedeci;
            poc->prethodni=nullptr;
            delete t;
            t=poc;
        } else if(t==poslj) {
            poslj=t->prethodni;
            poslj->sljedeci=nullptr;
            delete t;
            t=poslj;
        } else {
            Cvor *pom=poc;
            while(pom->sljedeci!=t) pom=pom->sljedeci;
            t->prethodni->sljedeci=t->sljedeci;
            t->sljedeci->prethodni=t->prethodni;
            delete t;
            t=pom->sljedeci;
        }
        brElemenata--;
    }
template<typename Tip>
void DvostrukaLista<Tip>::dodajIspred(const Tip &element)
    {
        Cvor *novi= new Cvor();
        novi->element=element;
        novi->sljedeci=nullptr;
        if(brElemenata==0)
        {
            poc=novi;
            poslj=novi;
            t=novi;
        }
        else if(t==poc)
        {
            poc->prethodni=novi;
            novi->sljedeci=poc;
            poc=novi;
        }
        else
        {
            Cvor *pom=t->prethodni;
            pom->sljedeci=novi;
            novi->prethodni=pom;
            novi->sljedeci=t;
            t->prethodni=novi;
        }
        brElemenata++;
    }
template<typename Tip>
void DvostrukaLista<Tip>::dodajIza(const Tip &element) {
        Cvor *novi= new Cvor();
        novi->element=element;
        novi->sljedeci=nullptr;
        if(brElemenata==0) {
            poc=novi;
            poslj=novi;
            t=novi;
        } else if(t==poslj) {
            poslj->sljedeci=novi;
            novi->prethodni=poslj;
            poslj=novi;
        }
        else {
            Cvor *pom=t->sljedeci;
            novi->prethodni=t;
            t->sljedeci=novi;
            pom->prethodni=novi;
            novi->sljedeci=pom;
        }
        brElemenata++;
    }

template<typename Tip>
DvostrukaLista<Tip>::DvostrukaLista(const DvostrukaLista<Tip> &l) {
        Cvor *pom1=l.poc;
        Cvor *pom2=nullptr;
        brElemenata=l.brElemenata;
        while(pom1!=nullptr) {
            Cvor *novi=new Cvor;
            novi->element=pom1->element;
            if(pom1==l.poc) poc = novi;
            else {
                pom2->sljedeci=novi;
                novi->prethodni=pom2;
            }
            pom2=novi;
            if(pom1==l.t) t=novi;
            pom1=pom1->sljedeci;
        }
        poslj=pom2;
        pom2->sljedeci=nullptr;
    }
template <typename Tip>
DvostrukaLista<Tip> &DvostrukaLista<Tip>::operator=(const DvostrukaLista<Tip> &l) {
        if(this==&l) return *this;
        while(poc!=nullptr) {
            t=poc;
            poc=poc->sljedeci;
            delete t;
        }
        Cvor *pom1=l.poc;
        Cvor *pom2=nullptr;
        brElemenata=l.brElemenata;
        while(pom1!=nullptr) {
            Cvor *novi=new Cvor;
            novi->element=pom1->element;
            if(pom1==l.poc) poc=novi;
            else {
                pom2->sljedeci=novi;
                novi->prethodni=pom2;
            }
            pom2=novi;
            if(pom1==l.t) t=novi;
            pom1=pom1->sljedeci;
        }
        poslj=pom2;
        pom2->sljedeci=nullptr;

        return *this;
    }

//testne funkcije
bool testdodajiza1 (DvostrukaLista<int> &j) {
    for(int i=1;i<=5;i++) j.dodajIza(i);
    for(int i=1;i<=5;i++) {
        if((i==1 && j.trenutni()==1) || (i==2 && j.trenutni()==5)) return true;
    }
    return false;
}
bool testbrElemenata1(DvostrukaLista<int> &j) {
    if(j.brojElemenata()==5) return true;
    return false;
}
bool testtrenutni1() {
    DvostrukaLista<int> l;
    for (int i(0); i<43249; i++)
        l.dodajIspred(3);
    if(l.trenutni()==3) return true;
    return false;
}
bool testprethodni1() {
    DvostrukaLista<int> l;
    for(int i=0; i<10; i++) l.dodajIspred(i);
        l.prethodni();
    if ( l.trenutni()==9) return true;
    return false;
}
bool testdodajispred1(DvostrukaLista<int> &j1) {
    for(int i=5;i>=1;i--) j1.dodajIspred(i);
    bool t=false;
    for(int i=5;i>=1;i--) {
        if((i==5 && j1.trenutni()==1)||(i==1 && j1.trenutni()==5)) t=true;
        else t=false;
    }
    if (t==true) return true;
    return false;
}
bool testsljedeci1(DvostrukaLista<int> &j) {
    j.dodajIspred(6);
    return j.sljedeci();
}
bool testpocetak1() {
    DvostrukaLista<int> j;
    for(int i=5;i>0;i--)
        j.dodajIza(i);
    j.pocetak();
    if(j.trenutni()!=5) return false;
    return true;
}
bool testkraj1(DvostrukaLista<int> &j) {
    j.kraj();
    if(j.trenutni()!=2) return false;
    return true;
}
bool testobrisi1(DvostrukaLista<int> &j) {
    int z=j.brojElemenata();
    j.obrisi();
    if(j.brojElemenata()!=z-1)  return false;
    return true;
}

template <typename Tip>
class It {
    private:
    const DvostrukaLista<Tip> *l;
    typename DvostrukaLista<Tip>::Cvor *p;
    public:
    It (const Lista<Tip>& n1) {
        l=(const DvostrukaLista<Tip>*) &n1;
        p=l->t;
    }
    Tip& trenutni() {
        if(l->poc==nullptr) throw "Izuzetak!" ;
        return p->element;
    }
    void pocetak() {
        if(l->poc==nullptr) throw "Izuzetak!";
        p=l->poc;
    }
    void kraj() {
        if(l->poc==nullptr) throw "Izuzetak!";
        p=l->poslj;
    }
    bool prethodni() {
        if(l->poc==p) return false;
        p=l->prethodni;
        return true;
    }
    bool sljedeci() {
        if(l->poc==nullptr) throw "Izuzetak!";
        if(p==l->poslj) return false;
        p=p->sljedeci; //
        return true;
    }
};
template <typename Tip>
Tip dajMaksimum(const Lista<Tip>& n) {
    It <Tip> it(n);
    it.pocetak();
    Tip maksimum=it.trenutni();
    it.sljedeci();
    for(int j(0);j<n.brojElemenata()-1;j++ ) {
        if(it.trenutni()>maksimum) 
            maksimum=it.trenutni();
        it.sljedeci();
    }
    return maksimum;
}
bool testirajdajmaks() {
    DvostrukaLista<int> l;
    for(int i=99; i>=0;i--) l.dodajIspred(10-i);
    return dajMaksimum(l)==100;
}




int main() {
    DvostrukaLista<int> j,j1;
    try {
        cout<<testdodajiza1(j)<<endl<<testbrElemenata1(j)<<endl<<testtrenutni1()<<endl<<testprethodni1()<<endl;
        cout<<testdodajispred1(j1)<<endl<<testsljedeci1(j)<<endl<<testpocetak1()<<endl<<testkraj1(j)<<endl<<testobrisi1(j)<<endl;
    }
    catch(...) {
        cout<<"Izuzetak je uhvaćen."<<endl;
    }
    return 0;
}
