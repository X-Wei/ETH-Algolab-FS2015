#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

//~ template <int n>
//~ int get_cost(int (&cost)[n][n], int i, int j, int (&Sa)[n], int (&Sb)[n])
int get_cost(int** cost, int i, int j, int* Sa, int* Sb)// min cost for a having i+1 remaining, b having j+1 remaining
{
    if(cost[i][j]!=-100000) return cost[i][j];
    if(i==0 || j==0) { 
        cost[i][j] = (Sa[i]-i-1)*(Sb[j]-j-1);
        return cost[i][j];
    }
    int mincost = 99999999;
    forloop(ka,1,i){
        int kb = 1;
        int c = get_cost(cost, i-ka, j-kb, Sa, Sb) + (Sa[i]-Sa[i-ka]-ka)*(Sb[j]-Sb[j-kb]-kb);
        if(c<mincost) mincost = c;
    }
    forloop(kb,1,j){
        int ka = 1;
        int c = get_cost(cost, i-ka, j-kb, Sa, Sb) + (Sa[i]-Sa[i-ka]-ka)*(Sb[j]-Sb[j-kb]-kb);
        if(c<mincost) mincost = c;
    }
    //~ forloop(ka,1,i)// take ka from a, kb from b
        //~ forloop(kb,1,j){
            //~ int c = get_cost(cost, i-ka, j-kb, Sa, Sb) + (Sa[i]-Sa[i-ka]-ka)*(Sb[j]-Sb[j-kb]-kb);
            //~ if(c<mincost) mincost = c;
        //~ }
    cost[i][j] = mincost;
    return mincost;
}

void dhl(){
    int n;
    cin >> n;
    int a[n], b[n], Sa[n], Sb[n];
    int s=0;
    rep(i,n) {cin >> a[i]; s+=a[i]; Sa[i]=s;}
    s=0;
    rep(i,n) {cin >> b[i]; s+=b[i]; Sb[i]=s;}
    //~ int cost[n][n];
    //~ rep(i,n) rep(j,n)
        //~ cost[i][j] = -1;
    int **cost;
    cost = new int *[n];
    rep(i,n){
        cost[i] = new int[n];
        rep(j,n) cost[i][j] = -100000;
    }
    cout << get_cost(cost, n-1, n-1, Sa, Sb) << endl;
    rep(i,n) delete cost[i];
}

int main(){
    int t; 
    cin >> t;
    rep(_,t)
        dhl();
    return 0;
}
