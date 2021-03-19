#include <iostream>
using namespace std;

template <typename Tip>
void insertionSort(Tip* niz, int vel) {
    for(int i=1; i<vel;i++) {      //i=4
        for(int j=i-1;j>=0;j--) {  //j=3, j=2, j=1
            if (niz[i]<niz[j]) {
                Tip pom=niz[i];
                niz[i]=niz[j];
                niz[j]=pom;
                i--;
            }
        }
    }
}
#include <iostream>
int main() {
    // 3 2 100 6 4 9 1 // vel=7
    // 2 3 6 100 4 9 1
    // 2 3 6 4 100 9 1
    // 2 3 4 6 100...
    
    int niz[9]={3,600,7,2,100,6,4,9,1};
    for(int i=0;i<9;i++) cout<<niz[i]<<" ";
    cout<<endl;
    insertionSort(niz,9);
    for(int i=0;i<9;i++) cout<<niz[i]<<" ";
    std::cout << "Tutorijal 6, Zadatak 5";
    return 0;
}
