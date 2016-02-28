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

void portfolios(int n, int m){
	int c[n],r[n];
	int v[n][n];
	Program qp (CGAL::LARGER, true, 0, false, 0); // Ax>=b, 0<=x<=inf
	rep(i,n) cin >> c[i] >> r[i];
	rep(i,n) rep(j,n) cin >> v[i][j];

	int x[n]; rep(i,n) x[i]=i;// QP variables: x[i], i=1..n

	int constraint_index=0;
	rep(i,n) qp.set_a(x[i],constraint_index,-1*c[i]);// constraint 0: sigma(-ci*xi) >= -C
	constraint_index++;
	rep(i,n) qp.set_a(x[i],constraint_index,r[i]);// constraint 1: sigma(ri*xi) >= R
	constraint_index++;
	// objective : min sigma( xi*xj*vij )
	rep(i,n) rep(j,i+1) // j<=i for set_d(i,j,2dij)
		qp.set_d(x[i], x[j],  2*v[i][j]); //  2*vij*xi*xj 
	rep(k,m){
		int C,R,V; 
		cin >> C >> R >> V;
		
		constraint_index=0;
		qp.set_b(constraint_index++,-1*C);// constraint 0: sigma(-ci*xi) >= -C
		qp.set_b(constraint_index++,R);// constraint 1: sigma(ri*xi) >= R
		
		// solve the program, using ET as the exact type
		Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
		assert (s.solves_quadratic_program(qp));
		if (s.status() == CGAL::QP_INFEASIBLE) 
			{ cout << "No." << endl; continue;}
		assert (s.status() == CGAL::QP_OPTIMAL);
		if (CGAL::to_double(s.objective_value())<=V) cout << "Yes." << endl;
		else cout << "No." << endl;
	}
}

int main(){
	int n,m;
	while(1){
		cin >> n >> m;
		if(n==0) return 0;
		portfolios(n,m);
	}
    return 0;
}
