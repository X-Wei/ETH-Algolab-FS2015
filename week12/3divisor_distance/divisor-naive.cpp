#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

vector<int> prims;
vector<int> is_prim(100000001,-1);// -1/0/1, -1 for undefined
int n;

void find_prims(){//  find all prim numbers smaller than 10000=sqrt(10^8)
    is_prim[1]=-1;// 1 is not prime
    int p=2; 
    while(p<=100000000){
        is_prim[p]=1;
        prims.push_back(p); //cout << p << ",";
        for(int i=2;i*p<=100000000;i++) is_prim[i*p]=0;
        while(p<=100000000 && is_prim[p]!=-1) p++;
    }cout <<prims.size();
}

bool test_prim(int n){
    if(n<=10000) return is_prim[n];
    for(int i=0;prims[i]*prims[i]<=n;i++)
        if(n%prims[i]==0) return false;
    return true;
}

int bfs(int s, int t){// bfs from s to t in graph Gn
    vector<bool> vis(n, false); vis[s] = true; 
    queue<int> Q; queue<int> distQ; int ds=0;
    Q.push(s); distQ.push(0);
    while (!Q.empty()) {
        const int u = Q.front(); Q.pop();
        const int d = distQ.front(); distQ.pop();
        vector<int> successors;
        //~ if(is_prim
        //~ for (tie(ebeg, eend) = out_edges(u, G); ebeg != eend; ++ebeg) {
            //~ const int v = target(*ebeg, G);
            //~ if (residue[*ebeg] == 0 || vis[v]) continue;
            //~ vis[v] = true;
            //~ Q.push(v);
        //~ }
    }// while q
    return ds;
}// bfs

void divisor_dist(){
    int n,c; cin >> n >> c;
    
}

int main(){
    find_prims();
    int t; cin >> t;
    rep(i,t) divisor_dist();
    return 0;
}
