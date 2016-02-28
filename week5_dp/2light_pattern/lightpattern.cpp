#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

/* - The order of switching operations does not matter, i.e. we can toggle lights in arbitrary order
 * - Each flipping operation should be done at most once. If we do it more often, we only get additional costs.
 * ==> go from right to left, subproblem: 
 *      turn bulbs0...i-1 into desired pattern, when bulbs0...i-1 is the same as origional OR flipped
 *      ==> dp[i][flipped]
 * */

int n, k, x; // decalre as global to make dp rec function have less parameters, and save time/code
int PATTERN[16];
int BULBS[100000];
int dp[100001][2];
// dp[i][1(0)] = min nb of seconds to make the bulb1...i into order when bulb0..i is flipped(not flipped) from BULBS

int dp_rec(int i, bool flipped){// invariant: i is always a multiple of k!
    // return min nb of seconds to make the bulb1...i into desired pattern when bulb1..i is flipped(not flipped) from `BULBS`
    if( i<=0 ) return 0;
    if( dp[i][flipped]>-1) return dp[i][flipped];
    int err_cnt=0; 
    rep(j,k){// how many errors are there in interval [i-k+1,...,i]?
        int bulbj = BULBS[i-j-1]; // ***have to -1 since BULBS index from 0!! -> ith bulb's index should be i-1!!***
        if(flipped) bulbj = (bulbj+1)%2;
        if(PATTERN[j]!=bulbj) err_cnt++;
    }
    //~ cout << i << (flipped?" y ":" n ") << err_cnt << endl;
    // **we can either fix the errors in interval, or first flip all to the left of i, then fix them**
    int res = min(err_cnt+dp_rec(i-k,flipped), k-err_cnt+1+dp_rec(i-k,!flipped));
    dp[i][flipped] = res;
    return res;
}

void light(){
    cin >> n >> k >> x;
    rep(i,n)
        cin >> BULBS[i]; 
    for (int i = 0; i < k; ++i) {
        PATTERN[i] = (x>>i)&1;// pattern[j] is the jth least signbit of x (pattern[0] is the bulb at *rightmost*
    }

    rep(i,n+1) rep(j,2) dp[i][j]=-1;
    cout << dp_rec(n,false) << endl;
}

int main(){
    int t;
    cin >> t;
    rep(i,t) light();
    return 0;
}
