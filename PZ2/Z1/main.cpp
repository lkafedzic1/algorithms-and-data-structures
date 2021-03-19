#include<iostream>
#include<stdexcept>
#include <typeinfo>
#include <string>
using namespace std;
#define VEL 10000000

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

template <typename Tip>
class NizLista: public Lista <Tip> {
    int kapacitet,brElemenata,t;
    Tip** lista;
public:
    NizLista(): Lista<Tip>(), lista(new Tip*[VEL]), kapacitet(VEL),brElemenata(0),t(0) {}
    ~NizLista() {
        for(int i(0);i<brElemenata;i++) {
            delete lista[i];
        }
        delete[] lista;
    }
    NizLista(const NizLista<Tip>& l) {
        kapacitet=l.kapacitet;
        brElemenata=l.brElemenata;
        t=l.t;
        lista=new Tip*[l.kapacitet];
        for(int i=0;i<brElemenata;i++)
            lista[i]=new Tip(*l.lista[i]);
    }
    NizLista<Tip>& operator=(const NizLista<Tip> &l) {
        if(this==&l) return *this;
        for(int i(0);i<brElemenata;i++) {
            delete lista[i];
        }
        delete[] lista;
        kapacitet=l.kapacitet;
        brElemenata=l.brElemenata;
        t=l.t;
        lista=new Tip*[l.kapacitet];
        for(int i=0;i<brElemenata;i++)
            lista[i]=new Tip(*l.lista[i]);
        return *this;
    }
    int brojElemenata() const override {return brElemenata;}
    Tip trenutni() const override {
        if(brElemenata==0) throw "Izuzetak!    ";
        return *lista[t];
    }
    Tip& trenutni() override {
        if(brElemenata==0) throw "Izuzetak! ";
        return *lista[t];
    }
    void obrisi() override {
        if (brElemenata==0)
            throw  "Izuzetak! ";
        if (t==brElemenata-1 && brElemenata>0) {
            delete lista[t];
            t--;
        } else {
            delete lista[t];
            for (int i=t;i<brElemenata;i++)
                lista[i]=lista[i+1];
        }
        brElemenata--;
    }
    void pocetak() override {
        if (brElemenata==0)
            throw  "Izuzetak! ";
        t=0;
    }
    void kraj() override {
        if (brElemenata==0)
            throw  "Izuzetak! ";
        t=brElemenata-1;
    }
    bool prethodni() override {
        if (brElemenata==0)
            throw  "Izuzetak! ";
        if (t==0)
            return false;

        t--;
        return true;
    }
    bool sljedeci() override {
        if (brElemenata==0) throw  "Izuzetak! ";
        if (t==brElemenata-1) return false;
        t++;
        return true;
    }
    void dodajIspred(const Tip &el) override {
        if (brElemenata==0) {
            brElemenata++;
            lista[0]=new Tip(el);
            t=0;
        } else if (kapacitet==brElemenata) {
            kapacitet*=2;
            Tip**n_lista=new Tip*[kapacitet];
            for (int i=0;i<brElemenata;i++)
                n_lista[i]=new Tip(*lista[i]);
            for(int i=0;i<brElemenata;i++)
                delete lista[i];
            delete[] lista;
            lista=n_lista;
        } else {
            for (int i=brElemenata;i>t;i--)
                lista[i]=lista[i-1];
            lista[t]=new Tip (el);
            brElemenata++;
            if(brElemenata!=1) t++;
        }
    }
    void dodajIza(const Tip &el) override {
        if (brElemenata==0) {
            brElemenata++;
            lista[0]=new Tip (el);
            t=0;
        } else if (kapacitet==brElemenata) {
            kapacitet*=2;
            Tip**n_lista=new Tip*[kapacitet];
            for (int i=0;i<brElemenata;i++)
                n_lista[i]=new Tip(*lista[i]);
            for(int i=0;i<brElemenata;i++) {
                delete lista[i];
            }
            delete[] lista;
            lista=n_lista;
        } else {
            for (int i=brElemenata;i>t+1;i--) {
                lista[i]=lista[i-1];
            }
            lista[t+1]=new Tip(el);
            brElemenata++;
        }
    }
    Tip &operator[](int i) {
        if (i>=brojElemenata() || i<0)
            throw "Izuzetak! ";
        return *lista[i];
    }
    Tip  operator[](int i) const {
        if (i>=brojElemenata() || i<0)
            throw "Izuzetak! ";
        return  *lista[i];
    }
};

template<typename Tip>
class JednostrukaLista: public Lista <Tip> {
    int brElemenata;
    struct Cvor {
        Tip element;
        Cvor*sljedeci;
    };
    Cvor *poc,*poslj,*t;
    public:
    JednostrukaLista(): poc(nullptr), poslj(nullptr), t(nullptr), brElemenata(0) {} 
    JednostrukaLista(const JednostrukaLista &l1);
    ~JednostrukaLista();
    void obrisi() override;
    void pocetak() override {
        if (poc==nullptr) throw "Izuzetak!   ";
        t=poc;
    }
    void kraj() override {
        if (poc==nullptr) throw "Izuzetak!   ";
        t=poslj;
    }
    Cvor* DajPocetak() const { return poc;}
    Cvor* DajTekuci() const {return t;}
    bool prethodni() override;
    bool sljedeci() override;
    Tip trenutni() const override;
    Tip &trenutni() override;
    int brojElemenata() const override {return brElemenata;}
    Tip &operator[](int i) override;
    Tip operator[](int i) const;
    JednostrukaLista& operator=(const JednostrukaLista &l1);
    void dodajIspred(const Tip& el) override;
    void dodajIza(const Tip& el) override;
};
template <typename Tip>
void JednostrukaLista<Tip>::obrisi() {
    if (poc==nullptr) throw "Izuzetak!   ";
    brElemenata--;
    if (t==poc) {
        poc=poc->sljedeci;
        delete t;
        t=nullptr;
        t=poc;

        if (brElemenata==0) {
            poslj=nullptr;
            poc=nullptr;
            t=nullptr;
        }
    } else {
        Cvor* pom(poc);

        while(pom->sljedeci!= t) {
            pom=pom->sljedeci;
        }
        pom->sljedeci=t->sljedeci;
        delete t;
        t=pom->sljedeci;
        if (t==nullptr) {
            poslj=pom;
            t=pom;
        }
    }
}

template<typename Tip >
bool JednostrukaLista<Tip>::prethodni() {
    if (poc==nullptr) throw ("Izuzetak!   ");
    if (t==poc) return false;
    Cvor* pomocni(poc);
    while (pomocni->sljedeci != t)
        pomocni=pomocni->sljedeci;
    t=pomocni;
    return true;
}

template<typename Tip >
bool JednostrukaLista<Tip>::sljedeci() {
    if (poc==nullptr)
        throw "Izuzetak!   ";
    if (t->sljedeci== nullptr)
        return false;
    t=t->sljedeci;
    return true;
}

template<typename Tip>
Tip& JednostrukaLista <Tip> ::trenutni() {
    return t->element;
}

template<typename Tip>
Tip JednostrukaLista <Tip> ::trenutni() const {
    return t->element;
}

template<typename Tip >
Tip &JednostrukaLista<Tip>::operator[](int i) {
    if (i<0 || i >= brElemenata) throw "Izuzetak!   ";
    Cvor* pomocni(poc);
    for (int j(0);j<i;j++)
        pomocni=pomocni->sljedeci;
    return pomocni->element;
}
template<typename Tip >
Tip JednostrukaLista<Tip>::operator[](int i) const {
    if (i<0 || i>= brElemenata) throw "Izuzetak!   ";
    Cvor* pomocni(poc);
    for (int j(0);j<i;j++)
        pomocni=pomocni->sljedeci;
    return pomocni->element;
}

template<typename Tip >
JednostrukaLista<Tip>::JednostrukaLista(const JednostrukaLista &l1) {
    brElemenata=l1.brojElemenata();
    Cvor*pom1(l1.DajPocetak());
    Cvor*pom2(nullptr);
    while (pom1 != nullptr) {
        Cvor* novi=new Cvor;
        novi->element=pom1->element;
        novi->sljedeci=nullptr;
        if (pom2==nullptr) {
            poc=novi;
        } else {
            pom2->sljedeci=novi;
        }
        pom2=novi;
        if (pom1==l1.DajTekuci()) {
            t=novi;
        }
        pom1=pom1->sljedeci;
    }
    poslj=pom2;
}
template<typename Tip>
JednostrukaLista<Tip>& JednostrukaLista<Tip>::operator=(const JednostrukaLista<Tip> &l1) {
    if (this==&l1) return *this;
    Cvor*pom(poc);
    Cvor*privremeni2(nullptr);
    while (pom != nullptr) {
        privremeni2=pom;
        pom=pom->sljedeci;
        delete privremeni2;
    }
    brElemenata=l1.brojElemenata();
    Cvor*pom1(l1.DajPocetak());
    Cvor*pom2(nullptr);
    while (pom1 != nullptr) {
        Cvor*novi=new Cvor;
        novi->element=pom1->element;
        novi->sljedeci=nullptr;
        if (pom2==nullptr) {
            poc=novi;
        } else {
            pom2->sljedeci=novi;
        }
        pom2=novi;
        if (pom1==l1.DajTekuci()) {
            t=novi;
        }
        pom1=pom1->sljedeci;
    }
    poslj=pom2;

    return *this;
}
template<typename Tip >
JednostrukaLista<Tip>::~JednostrukaLista() {
    Cvor*pom(poc);
    Cvor*privremeni2(nullptr);
    while (pom != nullptr) {
        privremeni2=pom;
        pom=pom->sljedeci;
        delete privremeni2;
    }
}
template<typename Tip >
void JednostrukaLista<Tip>::dodajIspred(const Tip &element) {
    Cvor*pom1=new Cvor;
    pom1->element=element;
    pom1->sljedeci=nullptr;
    brElemenata++;
    if (poc==nullptr) {
        poc=pom1;
        poslj=pom1;
        t=pom1;
    } else if (t==poc) {
        pom1->sljedeci=poc;
        poc=pom1;
    } else {
        Cvor*pom(poc);
        while (pom->sljedeci != t)
            pom=pom->sljedeci;
        pom1->sljedeci=pom->sljedeci;
        pom->sljedeci=pom1;
    }
}

template<typename Tip >
void JednostrukaLista<Tip>::dodajIza(const Tip &element){
    Cvor* pom1=new Cvor;
    pom1->element=element;
    pom1->sljedeci=nullptr;
    brElemenata++;
    if (poc==nullptr) {
        poslj=pom1;
        poc=pom1;
        t=pom1;

    } else {
        pom1->sljedeci=t->sljedeci;
        t->sljedeci=pom1;
        if (poslj==t) {
            poslj=pom1;
        }
    }
}
//testne funkcije
bool testdodajiza (NizLista<int>&l) {
    for(int i=1;i<=5;i++) l.dodajIza(i);
    for(int i=1;i<=5;i++) {
        if(l[0]==1 && l[1]==5 && l[2]==4) return true;
    }
    return false;
}
bool testdodajiza1 (JednostrukaLista<int> &j) {
    for(int i=1;i<=5;i++) j.dodajIza(i);
    for(int i=1;i<=5;i++) {
        if((i==1 && j.trenutni()==1) || (i==2 && j.trenutni()==5)) return true;
    }
    return false;
}
bool testbrElemenata(NizLista<int>&l) {
    if(l.brojElemenata()==5) return true;
    return false;
}
bool testbrElemenata1(JednostrukaLista<int> &j) {
    if(j.brojElemenata()==5) return true;
    return false;
}
bool testtrenutni(NizLista<int> &l) {
    int i=1;
    bool t=false;
    do {
        if((i==1 && l.trenutni()==1) || (i==3 && l.trenutni()==4)) t=true;
        else t=false;
        i++;
    } while(l.sljedeci());
    if (t=true) return true;
    return false;
}
bool testtrenutni1(JednostrukaLista<int> &j) {
    int i=1;
    bool t=false;
    do {
        if((i==1 && j.trenutni()==1) || (i==3 && j.trenutni()==4)) t=true;
        else t=false;
        i++;
    } while(j.sljedeci());
    if (t=true) return true;
    return false;
}
bool testprethodni(NizLista<int> &l) {
    if(l.prethodni()) return true;
    return false;
}
bool testprethodni1(JednostrukaLista<int> &j) {
    if(j.prethodni()) return true;
    return false;
}
bool testdodajispred(NizLista<int> &l1) {
    for(int i=5;i>=1;i--) l1.dodajIspred(i);
    bool t=false;
    for(int i=5;i>=1;i--) {
        if((i==5 && l1.trenutni()==1)||(i==1 && l1.trenutni()==5)) t=true;
        else t=false;
    }
    if (t=true) return true;
    return false;
}
bool testdodajispred1(JednostrukaLista<int> &j1) {
    for(int i=5;i>=1;i--) j1.dodajIspred(i);
    bool t=false;
    for(int i=5;i>=1;i--) {
        if((i==5 && j1.trenutni()==1)||(i==1 && j1.trenutni()==5)) t=true;
        else t=false;
    }
    if (t=true) return true;
    return false;
}
bool testsljedeci(NizLista<int> &l) {
    l.dodajIspred(6);
    return l.sljedeci();
}
bool testsljedeci1(JednostrukaLista<int> &j) {
    j.dodajIspred(6);
    return j.sljedeci();
}
bool testpocetak(NizLista<int> &l) {
    l.pocetak();
    if(l.trenutni()!=1) return false;
    return true;
}
bool testpocetak1(JednostrukaLista<int> &j) {
    j.pocetak();
    if(j.trenutni()!=1) return false;
    return true;
}
bool testkraj(NizLista<int> &l) {
    l.kraj();
    if(l.trenutni()!=2) return false;
    return true;
}
bool testkraj1(JednostrukaLista<int> &j) {
    j.kraj();
    if(j.trenutni()!=2) return false;
    return true;
}
bool testobrisi(NizLista<int> &l) {
    int z=l.brojElemenata();
    l.obrisi();
    if(l.brojElemenata()!=z-1)  return false;
    return true;
}
bool testobrisi1(JednostrukaLista<int> &j) {
    int z=j.brojElemenata();
    j.obrisi();
    if(j.brojElemenata()!=z-1)  return false;
    return true;
}
bool testoperatora(NizLista<int> &l) {
    if(l[0]==1) return true;
    return false;
}
int main() {
    NizLista<int> l,l1;
    JednostrukaLista<int> j,j1;
    try {
        if (testdodajiza(l)) cout<<"Test je uspjesan!";
        else cout<<"Test1 nije uspjesan!";
        cout<<endl;
        if (testdodajiza1(j)) cout<<"Test je uspjesan!";
        else cout<<"Test2 nije uspjesan!";
        cout<<endl;
        if (testbrElemenata(l)) cout<<"Test je uspjesan!";
        else cout<<"Test3 nije uspjesan!";
        cout<<endl;
        if (testbrElemenata1(j)) cout<<"Test je uspjesan!";
        else cout<<"Test4 nije uspjesan!";
        cout<<endl;
        if (testtrenutni(l)) cout<<"Test je uspjesan!";
        else cout<<"Test5 nije uspjesan!";
        cout<<endl;
        if (testtrenutni1(j)) cout<<"Test je uspjesan!";
        else cout<<"Test6 nije uspjesan!";
        cout<<endl;
        if (testprethodni(l)) cout<<"Test je uspjesan!";
        else cout<<"Test7 nije uspjesan!";
        cout<<endl;
        if (testprethodni1(j)) cout<<"Test je uspjesan!";
        else cout<<"Test8 nije uspjesan!";
        cout<<endl;
        if (testdodajispred(l1)) cout<<"Test je uspjesan!";
        else cout<<"Test9 nije uspjesan!";
        cout<<endl;
        if (testdodajispred1(j1)) cout<<"Test je uspjesan!";
        else cout<<"Test10 nije uspjesan!";
        cout<<endl;
        if (testsljedeci(l)) cout<<"Test je uspjesan!";
        else cout<<"Test11 nije uspjesan!";
        cout<<endl;
        if (testsljedeci1(j)) cout<<"Test je uspjesan!";
        else cout<<"Test12 nije uspjesan!";
        cout<<endl;
        if (testpocetak(l)) cout<<"Test je uspjesan!";
        else cout<<"Test13 nije uspjesan!";
        cout<<endl;
        if (testpocetak1(j)) cout<<"Test je uspjesan!";
        else cout<<"Test14 nije uspjesan!";
        cout<<endl;
        if (testkraj(l)) cout<<"Test je uspjesan!";
        else cout<<"Test15 nije uspjesan!";
        cout<<endl;
        if (testkraj1(j)) cout<<"Test je uspjesan!";
        else cout<<"Test16 nije uspjesan!";
        cout<<endl;
        if (testobrisi(l)) cout<<"Test je uspjesan!";
        else cout<<"Test17 nije uspjesan!";
        cout<<endl;
        if (testobrisi1(j)) cout<<"Test je uspjesan!";
        else cout<<"Test18 nije uspjesan!";
        cout<<endl;
        if (testoperatora(l)) cout<<"Test je uspjesan!";
        else cout<<"Test19 nije uspjesan!";
        cout<<endl;
    } catch(...) {
        cout<<"Uhvacen je zuzetak! ";
    }

    return 0;
}
