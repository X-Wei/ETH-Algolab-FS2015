// example: decide whether there exists a disk that covers a given set
// of points R in the plane and is disjoint from another set of points B
#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <cmath>

// choose exact integral type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

// program and solution types
typedef CGAL::Quadratic_program<double> Program; // input type: double
typedef CGAL::Quadratic_program_solution<ET> Solution; // Exact internal type

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)


int main() {
	const int X = 0; // var index
	const int Y = 1; // var index
	const int Z2 = 2; // var index
	int p,a,b;
	while (1){
	  cin >> p;
	  if(p==0) return 0;
	  cin >> a >> b;
	  if(p==1){
		// general QP: ** min x'Dx + c'x + c0 st. Ax<=b, l<=x<=u **
		Program qp (CGAL::SMALLER, true, 0, false, 0); 
		qp.set_a(X,0,1);	qp.set_a(Y,0,1);	qp.set_b(0,4);	// constraint-0: x+y<=4
		qp.set_a(X,1,4);	qp.set_a(Y,1,2);	qp.set_b(1,a*b);// constraint-1: 4x+2y<=ab
		qp.set_a(X,2,-1);	qp.set_a(Y,2,1);	qp.set_b(2,1);	// constraint-2: -x+y<=1
		// obj: min -b*y + a*x^2
		qp.set_d(X,X,a*2);// a * x^2
		qp.set_c(Y,-b); //-b*y
		// solve the program, using ET as the exact type
		Solution s = CGAL::solve_quadratic_program(qp, ET());
		assert (s.solves_quadratic_program(qp));
		if (s.status() == CGAL::QP_INFEASIBLE) {cout << "no" << endl;continue;}
		else if (s.status() == CGAL::QP_UNBOUNDED) {cout<<"unbounded"<<endl; continue;}
		double obj = CGAL::to_double(s.objective_value())*-1;
		cout.precision(0);// avoid scientific notation
		cout << fixed <<floor(obj) << endl;
	  } // p=1
	  else{
		// general QP: ** min x'Dx + c'x + c0 st. Ax<=b, l<=x<=u **
		Program qp (CGAL::LARGER, false, 0, false, 0); 
		qp.set_u(X,true);	qp.set_u(Y,true); 				// x,y <= 0
		qp.set_l(Z2,true); // z^2>=0
		qp.set_a(X,0,1);	qp.set_a(Y,0,1);	qp.set_b(0,-4);	// constraint-0: x + y >= -4
		qp.set_a(X,1,4);	qp.set_a(Y,1,2);	qp.set_a(Z2,1,1);	qp.set_b(1,-a*b);// constraint-1: 4x + 2y + z2 >= -ab
		qp.set_a(X,2,-1);	qp.set_a(Y,2,1);	qp.set_b(2,-1);	// constraint-2: -x + y => -1
		// obj: min ax^2 + by + z^4
		qp.set_d(Z2,Z2,2); // z^4
		qp.set_d(X,X,a*2); // a*x^2
		qp.set_c(Y,b); // b*y
		Solution s = CGAL::solve_quadratic_program(qp, ET());
		assert (s.solves_quadratic_program(qp));
		if (s.status() == CGAL::QP_INFEASIBLE) {cout << "no" << endl;continue;}
		else if (s.status() == CGAL::QP_UNBOUNDED) {cout<<"unbounded"<<endl; continue;}
		double obj = CGAL::to_double(s.objective_value());
		cout.precision(0);// avoid scientific notation -- combine with cout.precision()
		cout << fixed << ceil(obj) << endl;
	  } // p=2
	}//while()
}// main()
