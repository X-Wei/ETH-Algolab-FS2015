#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Segment_2 Segment;
typedef K::Point_2 Point;

using namespace std;

#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

// choose exact integral type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<double> Solution;//THIS IS CRUCIAL!

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

int l,s,w;
Point stamps[200], lights[200];
Segment walls[2000];
int M[200];

bool have_wall(int i, int j){ // is there a wall between light i and stamp j?
    Segment seg(lights[i], stamps[j]);
    rep(k,w)
        if (CGAL::do_intersect(walls[k],seg)) return true;
    return false;
}

void light_stamps(){
    cin >> l >> s >> w;
    rep(i,l) cin >> lights[i];
    rep(j,s) {cin >> stamps[j]; cin >> M[j];}
    rep(k,w){
        cin >> walls[k];
    }
    Program lp (CGAL::SMALLER, true, 1, true, (1<<12) );// 1<=pi<=2^12, 1 <= sigma(pi/rij2) <= Mj
    // lp var: pi i=0..l
    // constraint i: 1 <= sigma(pi/rij2) <= Mj (2*s constraints in total)
    rep(j,s){
        rep(i,l){
            if(have_wall(i,j)) continue;
            double r2 = CGAL::to_double( CGAL::squared_distance(lights[i], stamps[j]) );
            lp.set_a(i, j*2, 1.0/r2);// constraint j*2: sigma(pi/rij2) <= Mj
            lp.set_a(i, j*2+1, -1.0/r2);// constraint j*2+1: -sigma(pi/rij2) <= -1
        }
        lp.set_b(j*2, M[j]);
        lp.set_b(j*2+1, -1);
    }
    double res;
    Solution s = CGAL::solve_linear_program(lp, res);
    assert (s.solves_linear_program(lp));
    if (s.is_infeasible()) cout << "no" << endl;
    else cout << "yes" << endl;
}

int main(){
    int t; cin >> t;
    rep(i,t) light_stamps();
    return 0;
}
