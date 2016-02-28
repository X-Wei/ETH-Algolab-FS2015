#include <iostream>
#include <vector>
#include <algorithm>

#include <iostream>
#include <cassert>
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

void portlolios2(int n, int m){
    int c[n], r[n]; int v[n][n];
    rep(i,n) cin >> c[i] >> r[i];
    rep(i,n) rep(j,n) cin >> v[i][j];
    Program qp (CGAL::LARGER, true, 0, false, 0); // Ax>=b, x>=0
    
    // qp variables: xi
    int x[n]; rep(i,n) x[i]=(const int)i;
    
    rep(k,m){// read person k's C and V
        int C,V; cin >> C >> V;
        // first do a lp without considering V to get upper/lower bound of reward
        Program lp (CGAL::SMALLER, true, 0, false, 0); // min -sigma(xi*ri) st. sigma(xi*ci)<=C
        rep(i,n) lp.set_a(x[i], 0, c[i]);
        lp.set_b(0, C); // constraint 0: sigma(xi*ci)<=C
        rep(i,n) lp.set_c(x[i],-1*r[i]); // min -sigma(xi*ri)
        Solution s0 = CGAL::solve_linear_program(lp, ET());
        
        int hi = floor( -1*CGAL::to_double(s0.objective_value()) ); // reward upper bound
        int lo = 0;
        Program qp (CGAL::SMALLER, true, 0, false, 0);// min sigma(xi*xj*vij) st. sigma(xi*ci)<=C, sigma(xi*ri)>=minR
        rep(i,n) qp.set_a(x[i], 0, c[i]); // constraint 0: sigma(xi*ci)<=C
        rep(i,n) qp.set_a(x[i], 1, -1*r[i]); // constraint 1: -sigma(xi*ri)<=-minR
        rep(i,n) rep(j,i+1) qp.set_d(x[i], x[j], v[i][j]*2);// objective: sigma(xi*xj*vij)
        
        while(hi>=lo){ // binary search to find a max valide reward
            int minR = (hi+lo)/2;// this is the min reward to test
            qp.set_b(0,C);
            qp.set_b(1,-minR);
            Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
            if( CGAL::to_double(s.objective_value())<=V )// if with this minR we can achieve valid variance 
                lo = minR+1; // --> try a bigger minR
            else hi = minR-1; // else try a smaller minR
        } // after this binary search, solution is in hi
        cout << hi << endl;
    } //rep(k,m)
} // portlolios2()

int main(){
	int n,m;
	while(1){
		cin >> n >> m;
		if(n==0) return 0;
		portlolios2(n,m);
	}
    return 0;
}
