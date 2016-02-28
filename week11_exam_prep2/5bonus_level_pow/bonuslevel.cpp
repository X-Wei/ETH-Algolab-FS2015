#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

//~ int best[1000000];//best[d][r1][r2]=best[d+r1*100+r2*10000]
int best[200][100][100];
int a[100][100];
int n;

int best_rec(int d, int r1, int r2){    
    int c1=d-r1; int c2=d-r2;
    if(r1>=n || r2>=n || c1>=n || c2>=n) return 0;
    if(d==2*n+1 && r1==n-1 && r2==n-1) return a[n-1][n-1];
    if(best[d][r1][r2]>-1) return best[d][r1][r2];
    
    int res=0;
    res = max(res, best_rec(d+1,r1,r2));
    res = max(res, best_rec(d+1,r1,r2+1));
    res = max(res, best_rec(d+1,r1+1,r2));
    res = max(res, best_rec(d+1,r1+1,r2+1));
    res += a[r1][c1]; 
    if(r1!=r2) res+=a[r2][c2];
    best[d][r1][r2]=res;
    return res;
}

void bonus_level(){
    //~ fill(best,best+1000000,-1);
    rep(d,200) rep(r1,100) rep(r2,100) best[d][r1][r2]=-1;
    cin >> n;
    rep(i,n) rep(j,n) cin >> a[i][j];
    cout << best_rec(0,0,0) << endl;
}

int main(){
    int t; cin >> t;
    rep(i,t) bonus_level();
    return 0;
}
