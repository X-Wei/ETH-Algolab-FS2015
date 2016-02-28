#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

/* - every time a meeple is moved by 2 steps: first by H, then by M
 * - every vertex in the graph has a min/max nb of moves (if S and M play both OPTIMALLY) to the target
 * store them into array best[],worst[]; 
 * best[n] = 0, worst[n] = 0
 * the DP relationship for vertex u0 is:
 * best[u0] = min(1+worst[v], for each out edge u0-->v)
 * worst[u0] = max(1+best[v], for each out edge u0-->v)
 * in the end , if best[red]<=best[black] --> H wins
 * */
int n,m;
int best[50001], worst[50001];
int u[50001],v[50001];

int worst_rec(int p);

int best_rec(int p){// the min nb of moves to target, if it is H's turn to move the red meeple at position p
    if(p==n) return 0;
    if(best[p]>-1) return best[p];
    int res=INT_MAX;
    rep(i,m){
        if(u[i]==p){// for p-->v
            res=min(res, 1+worst_rec(v[i]));
        }
    }
    best[p]=res;
    return res;
}

int worst_rec(int p){// the max nb of moves to target, if it is H's turn to move the black meeple at position p
    if(p==n) return 0;
    if(worst[p]>-1) return worst[p];
    int res=INT_MIN;
    rep(i,m){
        if(u[i]==p){// for p-->v
            res=max(res, 1+best_rec(v[i]));
        }
    }
    worst[p]=res;
    return res;
}

void greatgame(){
    cin >> n >> m;
    int r,b; cin >> r >> b;
    rep(i,m)  cin >> u[i] >> v[i];
    fill(best,best+n+1,-1);
    fill(worst,worst+n+1,-1);
    best[n]=0; worst[n]=0;
    //~ cout << best_rec(r) << "/" << best_rec(b)<<": ";
    int bestH=best_rec(r), bestM=best_rec(b);
    if(bestH<bestM) cout << 0 << endl;
    else if (bestH>bestM) cout << 1 << endl;
    else // if bestH==bestM, should consider the parity of the moves! 
    if (bestH%2==1) cout << 0 << endl;
    else cout << 1 << endl;
}// greatgame()

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    rep(i,t) greatgame();
    return 0;
}
