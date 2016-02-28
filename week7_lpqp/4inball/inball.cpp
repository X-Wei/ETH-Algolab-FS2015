#include <iostream>
#include <vector>
#include <algorithm>
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

int round_down(const CGAL::Quotient<ET>& e) {
	double d = std::floor(CGAL::to_double(e));
	while(d > e) d--; while(d + 1 <= e) d++; return d; 
}

void inball(int n){
	int d; cin >> d;
	Program lp (CGAL::SMALLER, false, 0, false, 0); // Ax<=b
	// lp variables
	int x[d]; rep(i,d) x[i]=(const int)i;// x is position of center
	const int R = d; // R is radius
	
	lp.set_l(R,true,0);// R>=0
	lp.set_c(R,-1); // objective: min -R (ie. max R)
	
	int constraint_index=0;
	rep(i,n){
		int a[d]; int b; int norm=0;
		rep(j,d) {cin >> a[j];norm+=a[j]*a[j];}
		norm = std::sqrt(norm); // distance of point x0 to line a'x-b=0 is: `|a'x0-b|/norm(a)` 
		cin >> b; 
		
		// constraint for center: sigma(aj*xj)<=b
		rep(j,d) lp.set_a(x[j],constraint_index,a[j]);
		lp.set_a(R,constraint_index,0);
		lp.set_b(constraint_index,b);
		constraint_index++;
		
		// constraint for radius: |sigma(aj*xj)-b|/norm >= R , ie. b - sigma(aj*xj) >= norm*R
		rep(j,d) lp.set_a(x[j],constraint_index,a[j]); 
		lp.set_a(R,constraint_index,norm); // sigma(aj*xj) + norm*R <= b
		lp.set_b(constraint_index, b);	
		constraint_index++;
	}
	
	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_linear_program(lp, ET());// do NOT use solve_nonnegative_quadratic_program as in portfolio.cpp!!!
	assert (s.solves_quadratic_program(lp));

	// output
	if (s.status() == CGAL::QP_INFEASIBLE) {cout << "none" << endl; return;}
	if (s.status() == CGAL::QP_UNBOUNDED) {cout << "inf" << endl; return;}
	assert (s.status() == CGAL::QP_OPTIMAL);
	cout << round_down( -1*s.objective_value() ) << endl;
}

int main(){
	int n;
	while(1){
		cin >> n;
		if(n==0) return 0;
		inball(n);
	}
    return 0;
}
