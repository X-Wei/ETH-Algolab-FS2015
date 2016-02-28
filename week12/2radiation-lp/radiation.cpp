#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

// choose exact floating-point type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET; 
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;// we have to use ET as the numbers can be 2^300!
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

/* lp var: poly coeff `C_abc`, NO objective (just test feasible)
 * st.  for i=1..h, Sigma(C_abc*xi^a*yi^b*zi*c) >= 1 a+b+c<=d
 * 		for j=1..t, Sigma(C_abc*xj^a*yj^b*zj*c) <= -1
 * */
int h,t;
int xh[50],yh[50],zh[50];
int xt[50],yt[50],zt[50];
ET pow_xh[50][31], pow_yh[50][31], pow_zh[50][31];// precompute the powers of x y z
ET pow_xt[50][31], pow_yt[50][31], pow_zt[50][31];

bool seperates(int d){// whether polynomial of deg=d can seperate the h and t cells?
    Program lp (CGAL::LARGER, false, 0, false, 0); // A'X>=b	
    int C_abc=0; // lp var: poly coeff `C_abc`
    // add lp constraints
    forloop(a,0,d) forloop(b,0,d-a)	forloop(c,0,d-a-b){// a+b+c<=d
        rep(i,h){ // for i=1..h, Sigma(C_abc*xi^a*yi^b*zi*c) >= epsilon 
            ET XaYbZc = pow_xh[i][a] * pow_yh[i][b] * pow_zh[i][c];//Sigma(C_abc*XaYbZc) >= 1
            lp.set_a(C_abc, i, XaYbZc); lp.set_b(i,1); 
        }
        rep(j,t){ // for j=1..t, Sigma(C_abc*xj^a*yj^b*zj*c) <= -epsilon
            ET XaYbZc = pow_xt[j][a] * pow_yt[j][b] * pow_zt[j][c];//Sigma(C_abc*XaYbZc) <= -1
            lp.set_a(C_abc, j+h, XaYbZc);  lp.set_b(j+h,-1); lp.set_r(j+h,CGAL::SMALLER);
        }
        C_abc++; // index of lp var 
    }// for 0<=a+b+c<=d
    
    CGAL::Quadratic_program_options options; 
    options.set_pricing_strategy(CGAL::QP_BLAND);// avoid cycling
    Solution s = CGAL::solve_linear_program(lp, ET(), options);
    assert (s.solves_linear_program(lp));
    if(s.status() == CGAL::QP_INFEASIBLE) return false;
    return true;
}

void radiation(){
    //~ ios_base::sync_with_stdio(false);// will cause problem!!?
    cin >> h >> t;
    rep(i,h) cin >> xh[i] >> yh[i] >> zh[i];
    rep(j,t) cin >> xt[j] >> yt[j] >> zt[j];
    rep(i,h){
        ET pwx=ET(1), pwy=ET(1), pwz=ET(1);
        rep(d,31){
            pow_xh[i][d]=pwx; // pow_xh[i][d] = xh[i]^d
            pwx *=xh[i];
            pow_yh[i][d]=pwy;  
            pwy *=yh[i];
            pow_zh[i][d]=pwz; 
            pwz *=zh[i];
            //~ cout << pwx << " "<< pwy << " "<< pwz << " "<<endl;
        }
    }
    rep(i,t){
        ET pwx=ET(1), pwy=ET(1), pwz=ET(1);
        rep(d,31){
            pow_xt[i][d]=pwx; // pow_xh[i][d] = xh[i]^d
            pwx *=xt[i];
            pow_yt[i][d]=pwy;  
            pwy *=yt[i];
            pow_zt[i][d]=pwz; 
            pwz *=zt[i];
        }
    }
    if(seperates(0)) {cout << 0 << endl; return; }
    int hi=1, lo=0;// do a binary search to find min d
    /* ********* as seperates(d) for large d cost too much *********
     * ==> before doing binary search we first use exponential serach to find a suitable interval hi/lo*/
    while(seperates(hi)==false && hi<=30) hi*=2;
    if(hi==1) {cout << 1 << endl; return; }
    hi = min(hi,30); // EVIL IN DETAIL...
    lo = hi/2+1;
    while(hi>=lo){
        int d=(hi+lo)/2;
        if(seperates(d)) hi=d-1;
        else lo=d+1;
    }// binary search is SUBTLE! be careful!!
    //~ if(lo>=30 && seperates(30)==false) cout << "Impossible!" << endl; 
    if(lo>30) cout << "Impossible!" << endl;
    else cout << lo << endl; 	
    
}// radiation()

int main(){
    int t; cin >> t;
    rep(i,t) radiation();
    return 0;
}
