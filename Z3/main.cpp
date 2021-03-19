#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void radixSort(vector<int> &a) {
    int mx(a[0]), pos(1);
    for(int i=1;i<a.size();i++) {
            if(a[i]>mx) mx=a[i];
    }  
    vector<vector<int>> pom(10);
    while(mx/pos > 0) {
        for(int i=0;i<10;i++)  {
            pom[i].clear();
        }
        for(int i=0; i<a.size();i++) {
           pom[(a[i]/pos)%10].push_back(a[i]);
        }
        a.clear();
        for(int i=0;i<10;i++) 
            for(int j=0;j<pom[i].size();j++) 
                a.push_back(pom[i][j]);
    pos*=10;
    }
}
void popraviDolje(vector<int>& a, int velicina, int i) {
    int v(0),d(0);
    while(!((i>=velicina/2) && (i<=velicina-1))) {
        v=2*i+1;
        d=2*i+2;
        if(d<velicina && a[d]>a[v]) 
            v=d;
        if(a[i]>a[v]) return;
        swap(a[i],a[v]);
        i=v;
    }
}
void stvoriGomilu(vector<int> &a) {
    int velicina(a.size());
    for(int i=velicina/2; i>=0; i--)
        popraviDolje(a,velicina,i);
}
void popraviGore(vector<int>& a, int i) {
    while(i!=0 && a[i]>a[(i-1)/2]) {
        swap(a[i],a[(i-1)/2]);
        i=(i-1)/2;
    }
}
void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina) {
    a.push_back(umetnuti);
    popraviGore(a,velicina);
    velicina++;
}
int izbaciPrvi(vector<int> &a, int &velicina) {
    --velicina;
    swap(a[0],a[velicina]);
    if(velicina!=0)
        popraviDolje(a,velicina,0);
    return a[velicina];
}
void gomilaSort(vector<int> &a) {
    stvoriGomilu(a);
    int velicina(a.size());
    for(int i=0;i<=a.size()-2;i++) {
        izbaciPrvi(a,velicina);
    }
}
int main() {
    return 0;
}
