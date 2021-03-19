#include <iostream>
using namespace std;

template <typename Tip>
void modifikovani_bubble_sort(Tip* niz, int vel) {
    //int kr=0;
    for(int i=vel-1; i>=0; i--) {
       // bool pr=false;
        for(int j=1;j<=i;j++) {
            //if(pr==false && j==kr) break;
            
            
            if(niz[j-1]>niz[j]) {
                auto pom=niz[j-1];
                niz[j-1]=niz[j];
                niz[j]=pom;
            //    pr=true;
            }
            
            
           // if (pr=false) kr=j-1;
        }

        
    }
    
}

int main() {
    int niz[9]={3,600,7,2,100,6,4,9,1};
    
    //3,2,4,5,6,7  vel=6
    
    for(int i=0;i<9;i++) cout<<niz[i]<<" ";
    cout<<endl;
    modifikovani_bubble_sort(niz,9);
    for(int i=0;i<9;i++) cout<<niz[i]<<" ";
    return 0;
}
