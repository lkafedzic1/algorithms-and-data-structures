#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;
template <typename Tip>
void bubble_sort(Tip* niz, int vel) {
    for(int i=vel-1; i>=1; i--) {
        for(int j=1;j<=i;j++) {
            if(niz[j-1]>niz[j]) {
               swap(niz[j-1], niz[j]);
            }
        }
    }
} 

template<typename Tip>
void selection_sort(Tip* niz, int vel) {
Tip min=niz[0];
int mini=0;
    for (int i=0; i<vel-1;i++) {
        min=niz[i];
        mini=i;
        for(int j=i+1;j<vel;j++) {
            if (min>niz[j]) {
                min=niz[j];
                mini=j;
            }
        }
        swap(niz[i],niz[mini]);
    }
}
template<typename Tip>
int particija(Tip* niz, int prvi, int posljednji) {
    Tip pivot=niz[prvi];
    int i=prvi+1;
    while (i<=posljednji && niz[i]<pivot) {
        i++;
    }
    for (int j=i+1; j<=posljednji; j++) {
        if(niz[j]<pivot) {
            swap(niz[i++],niz[j]);
        }
    }
    swap(niz[prvi], niz[i-1]);
    return i-1;
}

template<typename Tip>
void quicksort(Tip* niz, int prvi, int posljednji) {
        if(prvi < posljednji) {
            int pi = particija(niz,prvi,posljednji);
            quicksort(niz,prvi,pi-1);
            quicksort(niz,pi+1,posljednji);
        }
}
template <typename Tip>
void quick_sort(Tip* niz, int vel) {
    quicksort(niz,0,vel-1);
}


template<typename Tip>
void merge2(Tip* niz, int vel, int l, int u, int pi) {
    int i=l, j=pi+1, k=0;
    Tip* a= new Tip[u-l+1];
    while(i<=pi && j<=u)
    {
        if(niz[i]<=niz[j]) a[k++]=niz[i++];
        else a[k++]=niz[j++];
    }
    while(i<=pi) a[k++]=niz[i++];
    while(j<=u) a[k++]=niz[j++];
    k=0;
    for(int i=l; i<=u; ++i) niz[i]=a[k++];
    delete [] a;
}
template<typename Tip>
void merge_sort(Tip* niz, int vel, int l=-1, int u=-1) {
    if(l==-1 && u==-1) { l=0; u=vel-1;}
    if(l<u) {
        int pi=l+(u-l)/2;
        merge_sort(niz,vel,l,pi);
        merge_sort(niz,vel,pi+1,u);
        merge2(niz,vel,l,u,pi);
    }
}
void ucitaj(string filename, int*& niz, int &vel) {
    ifstream ulaz;
    ulaz.open(filename+".txt");
    int kapacitet(1000);
    niz = new int[kapacitet];
    int i(0), broj(0);
    while (!ulaz.eof()) {
        if(i==kapacitet) {
            kapacitet*=2;
            int* niz2 = new int [kapacitet];
            for(int j=0;j<i;j++) {
                niz2[j]=niz[j];
            }
            delete[] niz;
            niz=niz2;
            niz2=nullptr;
        }
        ulaz>>broj;
        niz[i++]=broj;
    }
    vel=--i;
    ulaz.close();
}
void generisi(string filename, int vel)
{
    ofstream izlaz;
    izlaz.open(filename+".txt");
    for(int i=0; i<vel; i++)
    {
        izlaz<<rand()<<" ";
    }
    izlaz.close();
}
void f(string filename, int vel) {
    int* niz;
    ucitaj(filename,niz,vel);
    cout<<"Meni: /n"<<"Unesite: 1 - za bubble sort/n2 - za selection sort/n3 - za quick sort/4 - za merge sort";
    int opcija;
    cin>>opcija;
    clock_t start(clock()), finish;
    switch(opcija) {
        case 1:
            bubble_sort(niz,vel);
            finish=clock();
            break;
        case 2:
            selection_sort(niz,vel);
            finish=clock();
            break;
        case 3:
            quick_sort(niz,vel);
            finish=clock();
            break;
        case 4:
            merge_sort(niz,vel);
            finish=clock();
            break;
    }
    cout<<"Funkcija se izvršavala: "<<finish-start<<" milisekundi. ";
    for(int i=1;i<vel;i++) {
        if(niz[i-1]>niz[i]) {
            cout<<"Niz nije sortiran. "; 
            break;
        }
        cout<<"Niz je sortiran. ";
    }
    ofstream izlaz;
    izlaz.open("izlazna.txt");
    for(int i=0;i<vel-1;i++) {
        izlaz<<niz[i]<<" ";
    }
}
int main() {
    cout<<"Unesite naziv datoteke i velicinu niza: ";
    string naziv;
    cin>>naziv;
    int vel(0);
    cin>>vel;
    generisi(naziv,vel);
    f(naziv,vel);
    return 0;
}