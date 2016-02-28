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
typedef CGAL::Quadratic_program<double> Program;
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

bool seperates(int d){// whether polynomial of deg=d can seperate the h and t cells?
	Program lp (CGAL::LARGER, false, 0, false, 0); // A'X>=b	
	int C_abc=0; // lp var: poly coeff `C_abc`
	// add lp constraints
	forloop(a,0,d) forloop(b,0,d-a)	forloop(c,0,d-a-b){// a+b+c<=d
		rep(i,h){ // for i=1..h, Sigma(C_abc*xi^a*yi^b*zi*c) >= epsilon 
			long long XaYbZc = pow(xh[i], a) * pow(yh[i], b) * pow(zh[i], c);//Sigma(C_abc*XaYbZc) >= 1
			lp.set_a(C_abc, i, XaYbZc); lp.set_b(i,1); 
		}
		rep(j,t){ // for j=1..t, Sigma(C_abc*xj^a*yj^b*zj*c) <= -epsilon
			long long XaYbZc = pow(xt[j], a) * pow(yt[j], b) * pow(zt[j], c);//Sigma(C_abc*XaYbZc) <= -1
			lp.set_a(C_abc, j+h, XaYbZc);  lp.set_b(j+h,-1); lp.set_r(j+h,CGAL::SMALLER);
		}
		C_abc++; // index of lp var 
	}// for 0<=a+b+c<=d
	
	CGAL::Quadratic_program_options options; 
	options.set_pricing_strategy(CGAL::QP_BLAND);
	Solution s = CGAL::solve_linear_program(lp, ET(), options);
	assert (s.solves_linear_program(lp));
	if(s.status() == CGAL::QP_INFEASIBLE) return false;
	return true;
}

void radiation(){
	cin >> h >> t;
	rep(i,h) cin >> xh[i] >> yh[i] >> zh[i];
	rep(j,t) cin >> xt[j] >> yt[j] >> zt[j];
	if(seperates(0)) {cout << 0 << endl; return; }
	int hi=1, lo=0;// do a binary search to find min d
	/* ********* as seperates(d) for large d cost too much *********
	 * ==> before doing binary search we first use 2^n serach to find a suitable interval hi/lo*/
	while(seperates(hi)==false && hi<=30) hi*=2;
	lo = hi/2;
	while(hi>=lo){
		int d=(hi+lo)/2;
		if(seperates(d)) hi=d-1;
		else lo=d+1;
	}// binary search
	if(lo==30 && seperates(30)==false) cout << "Impossible!" << endl; 
	cout << lo << endl; 
}

int main(){
	int t; cin >> t;
	rep(i,t) radiation();
    return 0;
}
