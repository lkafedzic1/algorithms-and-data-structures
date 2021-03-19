#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include <ctime>

bool Prost(int n) {
    for(int i=2; i<n;i++)
        if(n%i==0)  return false;
    return true;
}

void Goldbach (int n, int& p, int& q) {
    if(n%2!=0 || n<=2) throw std::domain_error("Greska!");
    for(int i=2;i<n;i++) {
        for(int j=2;j<n;j++){
            if(Prost(i) && Prost(j) && (i+j)==n) {
                p=i; q=j;
            }
        }
    }
    
    }
    
int main() {
    int n(0);
    std::cout<<"Unesite broj n: ";
    std::cin>>n;
    int p(0), q(0);
    try{
        clock_t vrijeme1 = clock();
        Goldbach(n,p,q);
        clock_t vrijeme2 = clock();
        int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
        std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
        std::cout<<"p:"<<p<<",q:"<<q;
    }
    catch(std::domain_error e){
        std::cout<<e.what();
    }
    
}