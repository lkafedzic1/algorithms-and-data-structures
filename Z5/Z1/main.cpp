#include <iostream>
#include <string>
#include<vector>
#include <list>
#define kapacitet1 100
using namespace std;

unsigned int hashf(string ulaz,unsigned int max) {
    unsigned c(0);
    for(int i=0;i<ulaz.length();i++) {
        c+=ulaz[i];
    }
    return c%10;
}
template<typename Tip1, typename Tip2>
class Mapa {
    public:
        Mapa() {}
        virtual ~Mapa(){}
        virtual Tip2 &operator[] (const Tip1 &k)=0;
        virtual const Tip2 &operator[] (const Tip1 &k) const=0;
        virtual int brojElemenata() const=0;
        virtual void obrisi()=0;
        virtual void obrisi(const Tip1 &k)=0;
};
template<typename Tip1, typename Tip2>
class HashMapaLan: public Mapa<Tip1, Tip2> {
    int kap, vel;
    const Tip2 prazno;
    pair<Tip1,Tip2>** par;
    unsigned int (*f)(Tip1,unsigned int);
    public:
    HashMapaLan(): kap(kapacitet1), vel(0), prazno(Tip2()), par(new pair<Tip1,Tip2>* [kapacitet1]), f(nullptr){
        for(int i=0;i<kap;i++)
            par[i]=nullptr;
    }
    HashMapaLan(const HashMapaLan<Tip1,Tip2> &hm): kap(hm.kap), vel(0), par(new pair<Tip1,Tip2> *[kap]) {
        for(int i=0;i<kap;i++) {
            par[i]=nullptr;
        }
        f=hm.f;
        for(int i=0;i<kap;i++) {
            if(hm.par[i]!=nullptr) {
                if(hm.par[i]->first != Tip1()) {
                    unsigned int j=f(hm.par[i]->first, kap);
                    par[j]=new pair<Tip1,Tip2> (hm.par[i]->first, hm.par[i]->second);
                    vel++;
                }
            }
        }
    }
    ~HashMapaLan() {
        for(int i=0;i<kap;i++) {
            delete par[i];
        }
        delete[] par;
    }
    void definisiHashFunkciju(unsigned int(*par)(Tip1,unsigned int)) {
        f=par;
    }
    HashMapaLan<Tip1,Tip2>& operator= (const HashMapaLan<Tip1,Tip2> &hm) {
        if(this!=&hm) {
            for(int i=0;i<kap;i++) {
                delete par[i];
            }
            delete[] par;
            kap=hm.kap; vel=0; 
            par=new pair<Tip1,Tip2> *[kap];
            for(int i=0; i<kap;i++)
                par[i]=nullptr;
            f=hm.f;
            for(int i=0; i<hm.kap;i++) {
                if(hm.par[i]!=nullptr) {
                    if(hm.par[i]->first!=Tip1()) {
                        unsigned int j=f(hm.par[i]->first,kap);
                        par[i]=new pair<Tip1,Tip2>(hm.par[i]->first,hm.par[i]->second);
                        vel++;
                    }
                }
            }
        }
        return *this;
    }
    int brojElemenata() const{return vel;}
    void obrisi();
    void obrisi(const Tip1 &k);
    Tip2& operator[] (const Tip1& kljuc);
    const Tip2& operator[](const Tip1& kljuc) const {
        if(!f) throw "Nema hash funkcije! ";
        int i(0);
        unsigned int j=f(kljuc,kapacitet1);
        if(par[j]==nullptr) 
            return prazno;
        while(i!=kapacitet1 && par[j]!=nullptr) {
            j=(j+i)%kapacitet1;
            if(par[j]==nullptr)
                return prazno;
            if(par[j]->first==kljuc) 
                return par[j]->second;
            i++;
        }
            return prazno;
    }
};

template<typename Tip1,typename Tip2>
Tip2& HashMapaLan<Tip1,Tip2>::operator[](const Tip1& kljuc) {
        if(!f) throw "Nema hash funkcije! ";
        if(vel==kap) {
            kap*=2;
            pair<Tip1,Tip2> **par1=new pair<Tip1,Tip2> *[kap];
            for(int i=0;i<vel;i++) {
                par1[f(par[i]->first,kap)]=new pair<Tip1,Tip2>(par[i]->first,par[i]->second);
            }
            for(int i=0;i<vel;i++) 
                delete par[i];
            delete[] par;
            par=par1;
            
        }
        int i(0);
        unsigned int j=f(kljuc,kap);
        if(par[j]==nullptr) {
            par[j]=new pair<Tip1,Tip2>(kljuc,Tip2());
            vel++;
            return par[j]->second;
        }
        while(i!=kapacitet1 && par[j]!=nullptr){
            j=(j+i)%kapacitet1;
            if(par[j]!=nullptr) {
                if(par[j]->first==kljuc) 
                    return par[j]->second;
                i++;
            }
        }
        i=0;
        j=f(kljuc,kap);
        while(i!=kapacitet1 && par[j]!=nullptr) {
            j=(j+i)%kapacitet1;
            if(par[j]==nullptr) {
                par[j]=new pair<Tip1,Tip2>(kljuc, Tip2());
                vel++;
                return par[j]->second;
            }
            else if (par[j]->first == kljuc) {
                return par[j]->second;
            }
            else if(par[j]->first==Tip1()) {
                par[j]->first=kljuc;
                par[j]->second=Tip2();
                vel++;
                return par[j]->second;
            }
            i++;
        }
        return par[j]->second;
}
template <typename Tip1,typename Tip2>
void HashMapaLan<Tip1,Tip2>::obrisi() {
    for(int i=0;i<kap;i++)
        delete par[i];
    delete[] par;
    par=new pair<Tip1,Tip2> *[kap];
    for(int i=0; i<kap;i++) 
        par[i]=nullptr;
    vel=0;
}
template<typename Tip1, typename Tip2>
void HashMapaLan<Tip1,Tip2>::obrisi(const Tip1& k) {
    int i(0);
    unsigned int j=f(k,kap);
    while(i!=kap && par[j]!=nullptr) {
        j=(j+i)%kap;
        if(par[j]==nullptr) break;
        if(par[j]->first==k) {
            par[j]->first=Tip1();
            vel--;
            break;
        }
    }
}

template<typename TipOznake>
class Grana;
template<typename TipOznake>
class Cvor;
template<typename TipOznake>
class GranaIterator;

template<typename TipOznake>
class UsmjereniGraf {
    public:
    UsmjereniGraf(int brCvorova) {}
    virtual ~UsmjereniGraf() {}
    virtual int dajBrojCvorova() const=0;
    virtual void postaviBrojCvorova(int brCvorova)=0;
    virtual void dodajGranu(int polazni, int dolazni, float tezina)=0;
    virtual void obrisiGranu(int polazni, int dolazni)=0;
    virtual void postaviTezinuGrane(int polazni, int dolazni,float tezina)=0;
    virtual float dajTezinuGrane(int polazni, int dolazni) const=0;
    virtual bool postojiGrana(int polazni, int dolazni)=0;
    virtual void postaviOznakuCvora(int cvor, TipOznake o)=0;
    virtual TipOznake dajOznakuCvora(int cvor)const=0;
    virtual void postaviOznakuGrane(int polazni,int dolazni, TipOznake oznaka)=0;
    virtual TipOznake dajOznakuGrane(int polazni,int dolazni) const=0;
    Grana<TipOznake> dajGranu(int polazni, int dolazni){
        return Grana<TipOznake>(this,polazni,dolazni);
    }
    Cvor<TipOznake> dajCvor(int c) {
        return Cvor<TipOznake> (this,c);
    }
    virtual GranaIterator<TipOznake> dajGranePocetak()=0;
    virtual GranaIterator<TipOznake> dajGraneKraj()=0;
    virtual GranaIterator<TipOznake> dajSljedecuGranu(int polazni, int dolazni)=0;
}; 
template<typename TipOznake>
class Grana {
    UsmjereniGraf<TipOznake>* g;
    int polazni, dolazni;
    public:
    Grana(UsmjereniGraf<TipOznake>* g, int polazni, int dolazni): g(g),polazni(polazni), dolazni(dolazni) {}
    float dajTezinu() const {
        return g->dajTezinuGrane(polazni,dolazni);
    }
    void postaviTezinu(float tezina) {
        g->postaviTezinuGrane(polazni,dolazni,tezina);
    }
    TipOznake dajOznaku() const {
        return g->dajOznakuGrane(polazni,dolazni);
    } 
    void postaviOznaku(TipOznake oznaka) {
        g->postaviOznakuGrane(polazni, dolazni, oznaka);
    } 
    Cvor<TipOznake> dajPolazniCvor() {
        return g->dajCvor(polazni);
    } 
    Cvor<TipOznake> dajDolazniCvor() {
        return g->dajCvor(dolazni);
    }
};
template<typename TipOznake>
class Cvor{
    UsmjereniGraf<TipOznake>* g;
    int indeks;
    public:
    Cvor(UsmjereniGraf<TipOznake>* g, int indeks): g(g), indeks(indeks){}
    ~Cvor(){}
    TipOznake dajOznaku() const {
        return g->dajOznakuCvora(indeks);
    }
    void postaviOznaku(TipOznake oznaka) {
        g->postaviOznakuCvora(indeks, oznaka);
    }
    int dajRedniBroj() const {
        return indeks;
    }
};

template<typename TipOznake>
class ListaGraf: public UsmjereniGraf<TipOznake> {
    struct cvorListe{
        TipOznake oznaka;
        int redniBrojDolaznogCvora;
        float tezina;
        cvorListe(TipOznake o, int indeks, float t): oznaka(o), redniBrojDolaznogCvora(indeks), tezina(t) {}
        bool operator==(const cvorListe& cl) {
            return oznaka==cl.oznaka && redniBrojDolaznogCvora==cl.redniBrojDolaznogCvora && tezina==cl.tezina;
        }
    };
    vector<list<cvorListe>> lista_susjedstva;
    vector<TipOznake> oznake_cvorova;
public:
    ~ListaGraf() {}
    ListaGraf(int brCvorova=0): UsmjereniGraf<TipOznake>(brCvorova) {
        if(brCvorova<0) throw "Greška! ";
        oznake_cvorova.resize(brCvorova);
        lista_susjedstva.resize(brCvorova);
        postaviBrojCvorova(brCvorova);
    }
    int dajBrojCvorova() const {
        return lista_susjedstva.size();
    }
    void postaviBrojCvorova(int brCvorova) {
        if(brCvorova<lista_susjedstva.size())
            throw "Ne može se smanjiti broj čvorova! ";
        lista_susjedstva.resize(brCvorova);
        oznake_cvorova.resize(brCvorova);
    }
    void dodajGranu(int polazni, int dolazni, float tezina) {
        if(polazni<0 || polazni>=dajBrojCvorova() || dolazni>=dajBrojCvorova() || dolazni<0) 
            throw "Izlazi iz opsega. ";
        for(typename list<cvorListe>::iterator it=lista_susjedstva[polazni].begin();it!=lista_susjedstva[polazni].end();++it) {
            if((*it).redniBrojDolaznogCvora==dolazni)
                throw "Ova grana već postoji. ";
        }
        lista_susjedstva[polazni].push_back(cvorListe(TipOznake(), dolazni, tezina));
    }
    void obrisiGranu(int polazni, int dolazni) {
        if(polazni<0 || polazni>=dajBrojCvorova() || dolazni>=dajBrojCvorova() || dolazni<0) 
            throw "Izlazi iz opsega. ";
        for(typename list<cvorListe>::iterator it=lista_susjedstva[polazni].begin();it!=lista_susjedstva[polazni].end();++it) {
            if((*it).redniBrojDolaznogCvora==dolazni) {
                lista_susjedstva[polazni].remove(*it);
                return;
            }
        }
        throw "Grana ne postoji. ";
    }
    void postaviTezinuGrane(int polazni, int dolazni, float tezina) {
        if(polazni<0 || polazni>=dajBrojCvorova() || dolazni>=dajBrojCvorova() || dolazni<0) 
            throw "Izlazi iz opsega. ";
    for(typename list<cvorListe>::iterator it=lista_susjedstva[polazni].begin();it!=lista_susjedstva[polazni].end();++it) {
            if((*it).redniBrojDolaznogCvora==dolazni) {
                (*it).tezina=tezina;
                return;
            }
        }
        throw "Grana ne postoji. ";
    }
    float dajTezinuGrane(int polazni, int dolazni) const {
        if(polazni<0 || polazni>=dajBrojCvorova() || dolazni>=dajBrojCvorova() || dolazni<0) 
            throw "Izlazi iz opsega. ";
    for(typename list<cvorListe>::const_iterator it=lista_susjedstva[polazni].begin();it!=lista_susjedstva[polazni].end();++it) {
            if((*it).redniBrojDolaznogCvora==dolazni) {
                return (*it).tezina;
            }
        }
        throw "Grana ne postoji. ";
    }
    bool postojiGrana(int polazni, int dolazni ) {
        if(polazni<0 || polazni>=dajBrojCvorova() || dolazni>=dajBrojCvorova() || dolazni<0) 
            throw "Izlazi iz opsega. ";
    for(typename list<cvorListe>::const_iterator it=lista_susjedstva[polazni].begin();it!=lista_susjedstva[polazni].end();++it) {
            if((*it).redniBrojDolaznogCvora==dolazni) {
                return true;
            }
        }
        return false;
    }
    void postaviOznakuCvora(int c, TipOznake o) {
        oznake_cvorova[c]=o;
    }
    TipOznake dajOznakuCvora(int c) const {
        return oznake_cvorova[c];
    }
    void postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka) {
        if(polazni<0 || polazni>=dajBrojCvorova() || dolazni>=dajBrojCvorova() || dolazni<0) 
            throw "Izlazi iz opsega. ";
    for(typename list<cvorListe>::iterator it=lista_susjedstva[polazni].begin();it!=lista_susjedstva[polazni].end();++it) {
            if((*it).redniBrojDolaznogCvora==dolazni) {
                (*it).oznaka=oznaka;
                return;
            }
        }
        throw "Grana ne postoji. ";
    }
    TipOznake dajOznakuGrane(int polazni, int dolazni) const {
        if(polazni<0 || polazni>=dajBrojCvorova() || dolazni>=dajBrojCvorova() || dolazni<0) 
            throw "Izlazi iz opsega. ";
    for(typename list<cvorListe>::const_iterator it=lista_susjedstva[polazni].begin();it!=lista_susjedstva[polazni].end();++it) {
            if((*it).redniBrojDolaznogCvora==dolazni) {
                return (*it).oznaka;
            }
        }
        throw "Grana ne postoji. ";
    }
    Grana<TipOznake> dajGranu(int polazni, int dolazni) {
        return Grana<TipOznake> (this, polazni, dolazni);
    }
    Cvor<TipOznake> dajCvor(int c){
        return Cvor<TipOznake> (this,c);
    }
    int dajBrojGrana() const {
        int rez(0);
        for(int i=0; i<lista_susjedstva.size();i++) {
            rez+=lista_susjedstva[i].size();
        }
        return rez;
    }
    GranaIterator<TipOznake> dajSljedecuGranu(int trenutna) {
        if(trenutna==dajBrojGrana()-1)
            return dajGraneKraj();
        int predjeno(0);
        for(int i=0;i<lista_susjedstva.size();i++) {
            if(!lista_susjedstva[i].empty()) {
                for(typename list<cvorListe>::iterator it=lista_susjedstva[i].begin();it!=lista_susjedstva[i].end();++it) {
                    if(predjeno>=trenutna) {
                        typename list<cvorListe>::iterator pom=it;
                        if(pom==lista_susjedstva[i].end()) break;
                        if(predjeno==trenutna) pom++;
                        if(pom!=lista_susjedstva[i].end())
                            return GranaIterator<TipOznake>(this,i(*pom).redniBrojDolaznogCvora,trenutna+1);
                        
                    }
                    predjeno++;
                }
            }
        }
        return dajGraneKraj();
    }
    GranaIterator<TipOznake> dajSljedecuGranu(int polazni, int dolazni) {
        return GranaIterator<TipOznake>(this,-1,-1);
    }
    GranaIterator<TipOznake> dajGranePocetak() {
        GranaIterator<TipOznake> it(this,0,-1);
        return ++it;
    }
    GranaIterator<TipOznake> dajGraneKraj() {
        GranaIterator<TipOznake> it(this,-1,-1);
        return it;
    }
};
template<typename TipOznake>
class GranaIterator {
    UsmjereniGraf<TipOznake>* g;
    int polazni, dolazni;
    public:
    GranaIterator(UsmjereniGraf<TipOznake>* g, int polazni, int dolazni): g(g), polazni(polazni), dolazni(dolazni) {}
    Grana<TipOznake> operator* () {
        return Grana<TipOznake> (g, polazni, dolazni);
    }
    bool operator==(const GranaIterator& it) const {
        return(g==it.g && polazni==it.polazni && dolazni==it.dolazni);
    }
    bool operator!=(const GranaIterator& it) const {
        return !(*this==it);
    }
    GranaIterator& operator++() {
        if(polazni==-1 && dolazni==-1) {
            throw "Iterator pokazuje iza kraja! ";
        }
        GranaIterator gr=(g->dajSljedecuGranu(polazni,dolazni));
        polazni=gr.polazni;
        dolazni=gr.dolazni;
        return *this;
    }
    GranaIterator operator++(int) {
        GranaIterator pom=this;
        ++(*this);
        return pom;
    }
};
int main() {
    std::cout << "Zadaća 5, Zadatak 1";
    return 0;
}
