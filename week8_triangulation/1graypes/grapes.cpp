#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

int round_up(const K::FT& e) {
  double d = ceil(CGAL::to_double(e));
  while (d < e) d++;
  while (d - 1 >= e) d--;
  return d;
}

int main()
{
	cout.sync_with_stdio(false);
	int n;
	while(1){
		cin>>n;
		if(n==0) return 0;
		  // construct triangulation
		Triangulation t;
		Triangulation::Point pts[n];
		rep(i,n) {
			cin >> pts[i];
			t.insert(pts[i]);
		}
		K::FT best;
		bool isset=false;
		for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
			//~ cout << t.segment(e) << endl;
			//~ if(t.segment(e).vertex(1)!=pts[0] && t.segment(e).vertex(0)!=pts[0]) continue;
			if (!isset) {
				 best = t.segment(e).squared_length() * 2500;
				 isset = true; }
			best = min(best, t.segment(e).squared_length() * 2500);
		}
		cout.precision(0);
		cout << fixed << round_up(sqrt(best)) << endl;
		
	}// while(1)

}// main()
