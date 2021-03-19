#include <iostream>
#include <string>
#include <utility>

using namespace std;

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
            return;
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
NizMapa<Tip1,Tip2>& NizMapa<Tip1,Tip2>::operator=(const NizMapa<Tip1, Tip2> &nm)  {
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
//testiranje NizMape
bool test1() {
    NizMapa<string,string> nm;
    nm["lkafedzic1"]="Lejla Kafedžić";
    return (nm.brojElemenata()==1);
}
bool test2() {
    NizMapa<int,int> nm;
    for(int i=0;i<4;i++) {
        nm[i]=i;
    }
    nm.obrisi(3);
    return nm.brojElemenata()==3;
}
bool test3() {
    NizMapa<string,double> nm;
    nm["dm_z1"]=3.03;
    nm["dm_z2"]=5.00;
    nm["dm_z3"]=5.00;
    return (nm["dm_z3"]-5.00)<0.0001;
}
bool test4() {
    NizMapa<int,char> nm;
    for(int i=0;i<5;i++) {
        nm[i]=(char)i;
    }
    nm.obrisi();
    return nm.brojElemenata()==0;
}
bool test5() {
    NizMapa<string, string> nm;
    nm["lkafedzic1"]="Lejla Kafedžić";
    nm["lkagočić1"]="Lejla Kagočić";
    NizMapa<string,string> nm1(nm);
    return nm1.brojElemenata()==2;
}
int main() {
    cout<<test1()<<endl<<test2()<<endl<<test3()<<endl<<test4()<<endl<<test5();
    return 0;
}

