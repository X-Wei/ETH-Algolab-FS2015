#include <iostream>
#include <vector>
#include <algorithm>
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

void diet(int n, int m){
	int _min[n], _max[n];
	rep(i,n) 
		cin >> _min[i] >> _max[i];
	int C[m][n]; int p[m];
	rep(j,m){
		cin >> p[j];
		rep(i,n) cin >> C[j][i];
	}
	Program lp (CGAL::LARGER, true, 0, false, 0);// 0 <= aj <= inf
	int a[m]; rep(j,m) a[j]=j; // non-default entries (ie, lp variables): a[j] j=0..m-1
	// constraint: minj <= Sigma(j=1..m,aj*Cji) <= maxi for all i
	int constraint_index=0;
	rep(i,n){
		rep(j,m) lp.set_a(a[j],constraint_index, C[j][i]);
		lp.set_b(constraint_index, _min[i]);
		constraint_index++;
		rep(j,m) lp.set_a(a[j],constraint_index, -C[j][i]);
		lp.set_b(constraint_index, -1*_max[i]);
		constraint_index++;
	}
	// objective function: Sigma(j=1..m, pj*aj)
	rep(j,m) lp.set_c(a[j],p[j]);
	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_nonnegative_quadratic_program(lp, ET());
	assert (s.solves_quadratic_program(lp));
	if (s.status() == CGAL::QP_INFEASIBLE) 
		{cout << "No such diet." << endl; return;}
	assert (s.status() == CGAL::QP_OPTIMAL);
	cout << std::floor( CGAL::to_double(s.objective_value()) ) << endl;
}

int main(){
	int n,m;
	while(1){
		cin >> n >> m;
		if(n==0) return 0;
		diet(n,m);
	}
    return 0;
}
