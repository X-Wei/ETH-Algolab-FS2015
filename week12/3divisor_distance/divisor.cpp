#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cassert>
using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

const int N=10000000;
const int sqrtN=3200;
int lpd[N+1];// largest proper divisor
int n;

vector<int> prims;
vector<int> is_prim(sqrtN+1,-1);// -1/0/1, -1 for undefined

void find_prims(){//  find all prim numbers smaller than 10000=sqrt(10^8)
    is_prim[1]=-1;// 1 is not prime
    int p=2; 
    while(p<=sqrtN){
        is_prim[p]=1;
        prims.push_back(p); //cout << p << ",";
        for(int i=2;i*p<=sqrtN;i++) is_prim[i*p]=0;
        while(p<=sqrtN && is_prim[p]!=-1) p++;
    }
    //~ cout<<"prims found" <<prims.size()<<endl;
}

void init_lpd(){
    //~ forloop(i,2,N/2){
        //~ int maxj=min(i,N/i);
        //~ forloop(j,2,maxj) lpd[i*j]=i;// as i++ each time, this lpd will be updated to larger value
    //~ }
    // use prim numbers to find lpd more quickly!
    for(int i=prims.size()-1; i>=0; --i){
        int p = prims[i];
        for(int j=2;j*p<=N;j++) lpd[j*p]=max(p,j);
    }
}

int dist(int i, int j){// condition: i<=j
    assert(i<=j);
    if(i==j) return 0;
    if(lpd[j]==0)// prime number
        return 1+dist(1,i);
    if(lpd[j]<i) return 1+dist(lpd[j],i);
    else return 1+dist(i,lpd[j]);
    return 0;
}

void divisor_dist(){
    int n,c; cin >> n >> c;
    int s,t;
    rep(i,c) { 
        cin >> s >> t; 
        if(s>t) cout << dist(t,s) << endl;
        else cout << dist(s,t) << endl;
    }
}

int main(){
    find_prims();
    init_lpd();
    int t; cin >> t;
    rep(i,t) divisor_dist();
    return 0;
}
