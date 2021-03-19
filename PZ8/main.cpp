#include <iostream>
#include <string>
#include <ctime>
using namespace std;

template<typename Tip1,typename Tip2>
class Mapa {
    public:
    Mapa(){}
    virtual ~Mapa(){}
    virtual Tip2& operator[] (const Tip1 &k)=0;
    virtual const Tip2& operator[](const Tip1& k) const=0;
    virtual int brojElemenata() const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const Tip1& k)=0;
};

template<typename Tip1, typename Tip2>
class NizMapa: public Mapa<Tip1, Tip2> {
    pair<Tip1,Tip2>* niz;//niz parova
    int kapacitet, brElemenata;
    Tip2 x;
public:
    NizMapa():Mapa<Tip1,Tip2>(),kapacitet(100), brElemenata(0), x(Tip2()) {
        niz=new pair<Tip1,Tip2>[kapacitet];
    }
    ~NizMapa() { delete[] niz;}
    int brojElemenata() const {return brElemenata;}
    const Tip2& operator[] (const Tip1 &k) const;
    Tip2 &operator[](const Tip1 &k);
    void obrisi() {brElemenata=0;}
    void obrisi(const Tip1 &k);
    NizMapa(const NizMapa<Tip1, Tip2> &nm);    
    NizMapa &operator=(const NizMapa<Tip1, Tip2> &nm);
};
template<typename Tip1, typename Tip2>
void NizMapa<Tip1,Tip2>::obrisi(const Tip1 &k) {
    for(int i=0;i<brElemenata;i++){
        if(niz[i].first==k) {
            niz[i].first=niz[--brElemenata].first;
            niz[i].second=niz[brElemenata].second;
            break;
        }
    }
}
template<typename Tip1, typename Tip2>
NizMapa<Tip1,Tip2>::NizMapa(const NizMapa<Tip1, Tip2> &nm) {
    kapacitet=nm.kapacitet;
    brElemenata=nm.brElemenata;
    niz = new pair<Tip1,Tip2> [kapacitet]; 
    for(int i=0;i<brElemenata;i++){
        niz[i].first=nm.niz[i].first;
        niz[i].second=nm.niz[i].second;
    }
}
template<typename Tip1, typename Tip2>
const Tip2& NizMapa<Tip1,Tip2>::operator[] (const Tip1 &k) const {
    for(int i=0;i<brElemenata;i++) {
        if(niz[i].first==k) return niz[i].second;
    }
    return x;
}
template<typename Tip1, typename Tip2>
Tip2& NizMapa<Tip1,Tip2>::operator[](const Tip1 &k){
    for(int i=0;i<brElemenata;i++) {
        if(niz[i].first==k) return niz[i].second;
    }
    if(brElemenata==kapacitet) {
        kapacitet*=2;
        pair<Tip1,Tip2>* pom=new pair<Tip1,Tip2> [kapacitet];
        for(int i=0;i<brElemenata;i++){
            pom[i].first=niz[i].first; 
            pom[i].second=niz[i].second;
        }
        delete[] niz;
        niz=pom;
        pom=nullptr;
    }
    niz[brElemenata]=pair<Tip1,Tip2> (k,Tip2());
    brElemenata++;
    return niz[brElemenata-1].second;
}
template<typename Tip1, typename Tip2>
NizMapa<Tip1,Tip2>& NizMapa<Tip1,Tip2>::operator=(const NizMapa<Tip1, Tip2> &nm) {
    if(this == &nm) return *this;
    delete[] niz;
    niz=new pair<Tip1,Tip2> [kapacitet];
    brElemenata=nm.brElemenata;
    kapacitet=nm.kapacitet;
    for(int i=0;i<brElemenata;i++) {
        niz[i].first=nm.niz[i].first;        
        niz[i].second=nm.niz[i].second;
    }
    return *this;
}

template<typename Tip1, typename Tip2>
class BinStabloMapa: public Mapa<Tip1,Tip2> {
    struct Cvor {
        Tip1 kljuc;
        Tip2 vrijednost;
        Cvor* roditelj, *lijevo, *desno;
        Cvor (const Tip1 &kljuc, const Tip2& vrijednost, Cvor* lij, Cvor* des, Cvor* rod): kljuc(kljuc), vrijednost(vrijednost), lijevo(lij),desno(des),roditelj(rod) {}
    };
    Cvor* korijen;
    int brElemenata;
    Tip2 novi;
    public:
    BinStabloMapa(): Mapa<Tip1,Tip2>(), korijen(nullptr), brElemenata(0), novi(Tip2()) {}
    void kopiraj (Cvor* &c1, Cvor* c2, Cvor* r);
    BinStabloMapa (const BinStabloMapa<Tip1,Tip2> &bsm): korijen(nullptr), brElemenata(0), novi(Tip2()) {kopiraj(korijen,bsm.korijen,nullptr);}
    ~BinStabloMapa() {obrisisve(korijen);}
    int brojElemenata() const {return brElemenata;}
    void obrisisve(Cvor* c) {
        if(c==nullptr) return;
        obrisisve(c->lijevo);
        obrisisve(c->desno);
        delete c;
        brElemenata--;
    }
    void obrisi() {
        obrisisve(korijen);
        korijen=nullptr;
    }
    void obrisiP(Cvor *c);
    Cvor* dodaj(const Tip1& kljuc, const Tip2& vrijednost, Cvor* &c,Cvor* r){
        if (c==nullptr) {
            c = new Cvor(kljuc, vrijednost, 0, 0,r);
            brElemenata++;
            return c;
        }
        if(kljuc==c->kljuc) return c;
        if(kljuc > c->kljuc) return dodaj(kljuc, vrijednost,c->desno,c);
        return dodaj(kljuc,vrijednost,c->lijevo,c);
    }
    void obrisi(const Tip1& k);
    Cvor* trazi(const Tip1& kljuc,Cvor* c) const{
        if(c==nullptr) return 0;
        if(kljuc==c->kljuc) return c;
        if(kljuc > c->kljuc) return trazi(kljuc,c->desno);
        return trazi(kljuc,c->lijevo);
    }

    const Tip2& operator[] (const Tip1& kljuc) const {
        Cvor* c=trazi(kljuc,korijen);
        if(c==nullptr) return novi;
        return c->vrijednost;
    }
    Tip2& operator[] (const Tip1& kljuc) {
        Cvor* c=dodaj(kljuc, Tip2(), korijen, nullptr);
        return c->vrijednost;
    }
    BinStabloMapa<Tip1,Tip2>& operator= (const BinStabloMapa<Tip1,Tip2>& nm) {
        if( &nm == this) return *this;
        obrisisve(korijen);
        korijen=nullptr;
        kopiraj(korijen, nm.korijen, nullptr);
        return *this;
    }
};
template <typename Tip1, typename Tip2>
void BinStabloMapa<Tip1,Tip2>::obrisi(const Tip1& k) {
        Cvor* c=trazi(k,korijen);
        obrisiP(c);
}
template<typename Tip1, typename Tip2>
void BinStabloMapa<Tip1,Tip2>::kopiraj (Cvor* &c1, Cvor* c2, Cvor* r) {
    if(c2==nullptr) return;
    c1=new Cvor(c2->kljuc,c2->vrijednost,nullptr,nullptr,r);
    kopiraj(c1->lijevo,c2->lijevo,c1);
    kopiraj(c1->desno,c2->desno,c1);
    brElemenata++;
}
template<typename Tip1, typename Tip2>
void BinStabloMapa<Tip1, Tip2>::obrisiP(Cvor *c) {
    if(c==nullptr) return;
    if(c->desno==nullptr && c->lijevo==nullptr) {
        if(c->roditelj!=nullptr) {
            if(c==c->roditelj->desno) c->roditelj->desno=nullptr;
            else c->roditelj->lijevo=nullptr;
        }
        delete c;
        brElemenata--;
    }
    else if(c->desno!=nullptr && c->lijevo!=nullptr) {
        Cvor* pom= c->lijevo;
        while(pom->desno!=nullptr) 
            pom=pom->desno;
        c->kljuc=pom->kljuc;
        c->vrijednost=pom->vrijednost;
        obrisiP(pom);
    }
    else if(c==korijen) {
        Cvor* dijete=c->lijevo;
        if(dijete==nullptr) dijete=c->desno;
        korijen=dijete;
        delete c;
        brElemenata--;
    }
    else {
        Cvor* dijete=c->lijevo;
        if(dijete==nullptr) dijete=c->desno;
        if(c->roditelj!=nullptr) {
            if(c==c->roditelj->lijevo){
             c->roditelj->lijevo=dijete;
            }
            else {
                c->roditelj->desno=dijete;
            } 
        }
        dijete->roditelj=c->roditelj;
        delete c;
        brElemenata--;
    }
}

int main() {
    int n(10000);
    NizMapa<int,int> nm;
    BinStabloMapa<int,int> bsm;
    //dodavanje u niz mapu, pa u bsm
    clock_t begin=clock();
    for(int i=0;i<n;i++) {
        nm[rand()%(10*n)]=i;
    }
    clock_t end=clock();
    double t1=double(end-begin)/(CLOCKS_PER_SEC/1000);
    begin=clock();
    for(int i=0;i<n;i++) {
        bsm[rand()%(10*n)]=i;
    }
    end=clock();
    double t2=double(end-begin)/(CLOCKS_PER_SEC/1000);
    cout<<"Vrijeme izvršenja za: nm "<<t1<<"ms ,a za bsm "<<t2<<"ms!"<<endl;
    /*Binarno stablo mape prosječno troši oko 32 puta više vremena 
    za dodavanje elemenata od niza mape*/ 
    
    //pristup el. u niz mapi, pa u bs
    begin=clock();
    for(int i=0;i<n;i++) {
        nm[i]=i+5;
    }
    end=clock();
    t1=double(end-begin)/(CLOCKS_PER_SEC/1000);
    //pristup el. u bin stablu mape
    begin=clock();
    for(int i=0;i<n;i++) {
        bsm[i]=i+5;
    }
    end=clock();
    t2=double(end-begin)/(CLOCKS_PER_SEC/1000);
    cout<<"Vrijeme izvršenja pristupa za: nm "<<t1<<"ms ,a za bsm "<<t2<<"ms!"<<endl;
    /*Pristup elementima je također brže za binarna stabla mape, nego za niz mape.*/
    return 0;
}
