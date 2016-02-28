#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

int n;
int v[1000];
int dp[1000][1000];

int rec(int i, int j){// coins are vi...vj, return 0's max/min profit (depends on which round this is)
    if(i>j) return 0;
    int r = n-(j-i+1); // which round is it ?? -- this can be deduced, so no need to add another dimension!!!!!
    if(dp[i][j]>-1) return dp[i][j];
    int res;
    int pleft=v[i]+rec(i+1,j), pright=v[j]+rec(i,j-1);
    if(r%2==0) res = max(pleft,pright);
    else res = min(rec(i+1,j),rec(i,j-1));
    dp[i][j]=res;
    return res;
}

void coins(){
    cin >> n;
    rep(i,n) cin >> v[i];
    rep(i,n) rep(j,n) dp[i][j]=-1;
    cout << rec(0,n-1) << endl;
}

int main(){
    int t; cin >> t;
    rep(i,t) coins();
    return 0;
}
