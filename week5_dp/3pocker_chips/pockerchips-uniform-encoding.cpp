#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

const int MAXSZ=2000000;
int dp[MAXSZ];// product(mi+1) < 2^19=524288
int *chips[5];// chips[i][j] to check color
int n,B;

int encode(const int* k){// encoding: state = k1 + k2*B + k3*B^2+...
    int b=1; int state=0;
    rep(i,n) 
        {state += k[i]*b; b*=B;}
    return state;
}

int dp_rec(int state){
    if(state<=0) return 0;
    if(dp[state]>-1) return dp[state];
    int k[n];// k1..kn are the index of top chip in each stack, ENCODED in the number state
    int b=1; //state = m1 + m2*B + m3*B^2+...
    int color[n];
    rep(i,n) {// decode state
        k[i]=(state%(b*B))/b;
        b *= B;
        color[i]=(k[i]>0 ? chips[i][k[i]] : -1);// color of stack i's top is: chips[i][k[i]]
    } 
    // now we have the top indices in k[], we do dp to check all combinations 2^5=32 at most (some combinations are invalid)
    int res = -1;
    rep(i,n){// if we take ki (and maybe some other chips), what is the maximum? 
        if(k[i]==0) continue;
        k[i]-=1;// only take k[i] --> recieve 0 point
        res = max(res, dp_rec(encode(k)));
        k[i]+=1;// recover state
        vector<int> cand;// see how many chips are in same color of ki, put into a vector
        rep(j,n) 
            if(j!=i&&k[j]>0&&color[j]==color[i]) 
                cand.push_back(j);// cand[c] is the cth stack index that have same color chip as stack-i
        int sz = cand.size(); if(sz==0) continue;
        k[i]-=1;// take ki, plus any subset from cand
        int bitmask = (1<<sz) -1;// all subsets of cand: encoded into a sigle number bitmask=1<<sz-1, 
        while(bitmask>0){// each bitmask-->a subset
            int nb_taken=1; 
            rep(c,sz) if( (bitmask&(1<<c)) > 0 ) {k[cand[c]]--; nb_taken++;}
            int reward = 1<<(nb_taken-2); //reward = 2^(nb_taken-2) 
            res = max(res, reward+dp_rec(encode(k)));
            rep(c,sz) if( (bitmask&(1<<c)) > 0 ) k[cand[c]]++;// recover state
            --bitmask;
        }
        k[i]+=1;// recover state -- never forget!
    }
    dp[state]=res;
    return res;
}

void pocker_chips(){
    cin >> n;
    int m[n]; int maxm=-1;
    rep(i,n){
        cin >> m[i]; maxm = max(m[i], maxm);
        chips[i]=new int[m[i]+1];//chips[i][j] j in 1-based indexing!!
    }
    rep(i,n) forloop(j,1,m[i]) cin >> chips[i][j];// color of chipij
    //~ int m[]={3,9,8,7,0}; n=5; int maxm=9; // just for testing encoding...
    B = maxm+1; 
    int state = encode(m);
    rep(i,MAXSZ) dp[i]=-1;
    cout << dp_rec(state) << endl;
    rep(i,n) delete chips[i];
}

int main(){
    int t; cin >> t;
    rep(i,t) pocker_chips();
    return 0;
}
