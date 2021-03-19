#include <iostream>
#include <algorithm>
#include <vector>
template<typename tip>
struct cvor {
    tip vrijednost;
    cvor<tip>* sljedeci=nullptr;
};
template<typename tip>
class Stek {
    cvor<tip>*pocetak;
    int duzina;
    public:
        Stek(){
            pocetak=new cvor<tip>;
            duzina=0;
        }
        Stek(const Stek &s){
            pocetak=new cvor<tip>;
            pocetak->sljedeci=nullptr;
            duzina=s.duzina;
            cvor<tip>*tmp,*trenutni=pocetak;
            tmp=s.pocetak->sljedeci;
            while(tmp){
                cvor<tip>*novi=new cvor<tip>;
                novi->vrijednost=tmp->vrijednost;
                novi->sljedeci=nullptr;
                trenutni->sljedeci=novi;
                trenutni=trenutni->sljedeci;
                tmp=tmp->sljedeci;
            }
        }
        Stek(Stek &&s){
            std::swap(pocetak,s.pocetak);
            std::swap(duzina,s.duzina);
        }
        void brisi(){
            while (pocetak->sljedeci!=nullptr) {
                cvor<tip>*tmp=pocetak->sljedeci;
                pocetak->sljedeci=tmp->sljedeci;
                delete tmp;
            }
            duzina=0;
        }
        void stavi(const tip &el){
            cvor<tip> *novi=new cvor<tip>;
            novi->vrijednost=el;
            novi->sljedeci=pocetak->sljedeci;
            pocetak->sljedeci=novi;
            duzina++;
        }
        tip skini(){
            if(duzina==0) throw ("ERRR");
            cvor<tip>*tmp=pocetak->sljedeci;
            pocetak->sljedeci=tmp->sljedeci;
            auto a=tmp->vrijednost;
            delete tmp;
            duzina--;
            return a;
        }
        tip &vrh(){
            if(duzina==0) throw ("ERRR");
            cvor<tip>*tmp=pocetak->sljedeci;
            return tmp->vrijednost;
        }
        int brojElemenata(){return duzina;}
        Stek &operator=(const Stek&s){
            if(this==&s)return *this;
            while(pocetak->sljedeci!=nullptr){
                cvor<tip>*tmp=pocetak->sljedeci;
                pocetak->sljedeci=tmp->sljedeci;
                delete tmp;
            }
            pocetak->sljedeci=nullptr;
            duzina=s.duzina;
            cvor<tip>*tmp,*trenutni=pocetak;
            tmp=s.pocetak->sljedeci;
            while(tmp){
                cvor<tip>*novi=new cvor<tip>;
                novi->vrijednost=tmp->vrijednost;
                novi->sljedeci=nullptr;
                trenutni->sljedeci=novi;
                trenutni=trenutni->sljedeci;
                tmp=tmp->sljedeci;
            }
            return *this;
        }
        Stek &operator =(Stek &&s){
            std::swap(pocetak,s.pocetak);
            std::swap(duzina,s.duzina);
            return *this;
        }
        ~Stek(){
               while(pocetak->sljedeci!=nullptr){
                cvor<tip>*tmp=pocetak->sljedeci;
                pocetak->sljedeci=tmp->sljedeci;
                delete tmp;
            }
            delete pocetak;
            duzina=0;
        }
};    
template <typename tip> void test1(Stek<tip> &s){
    std::cout<<s.brojElemenata()<<std::endl;
}
template <typename tip> void test2(Stek<tip> &s,tip a){
    s.vrh()=a;
    std::cout<<s.vrh()<<std::endl;
}
template <typename tip> void test3(Stek<tip> &s){
    std::cout<<s.skini()<<std::endl;
}
template <typename tip> void test4(Stek<tip> &s){
    s.brisi();
    std::cout<<s.brojElemenata()<<std::endl;
}
template <typename tip> void test5(Stek<tip> &s,tip a){
    std::cout<<s.brojElemenata()<<std::endl;
    s.stavi(a);
    std::cout<<s.brojElemenata()<<std::endl;
}
        void pretraga(Stek<std::vector<int>> &s,int broj) {
            if(s.brojElemenata()==0) {std::cout<<"Nema elementa";}
            else{
                std::vector<int>pomocni=s.skini();
                if(pomocni.size()==0){
                    pretraga(s,broj);
                    s.stavi(pomocni);
                    return;
                }
                if(pomocni.size()==1){
                    if(pomocni[0]==broj){
                        std::cout<<"0 "<<s.brojElemenata();
                        s.stavi(pomocni);
                        return;
                    }
                    else {
                        pretraga(s,broj);
                        s.stavi(pomocni);
                        return;
                    }
                }
                int dno=0;
                int vrh=pomocni.size()-1;
                int srednji;
                while(vrh>=dno){
                    srednji=(dno+vrh)/2;
                    if(pomocni[srednji]==broj){
                        std::cout<<srednji<<" "<<s.brojElemenata();
                        s.stavi(pomocni);
                        return;
                    }
                    else if(pomocni[srednji]>broj){
                        vrh=srednji-1;
                    }
                    else{
                        dno=srednji+1;
                    }   
                }  
            }
        }
                        
                        
                        
                        
                        
                        
                        