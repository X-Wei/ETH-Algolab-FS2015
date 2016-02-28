#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); i++)
#define rep(i,N) forloop(i,0,N-1)

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

void hit(int n) {
	long x, y, a, b;
	cin >> x >> y >> a >> b;
	R ray = R(P(x, y), P(a, b));
	long r, s, t, u;
	bool hit = false;
	rep(_,n) {
		cin >> r >> s >> t >> u;
		if (hit == false) {
			S seg = S(P(r, s), P(t, u));
			if (CGAL::do_intersect(ray, seg))
				hit = true;
		}
	}
	cout<<(hit?"yes":"no")<<endl;
} // hit()


int main() {
	int n;
	while (1) {
		cin >> n;
		if(n==0) return 0;
		hit(n);
	}
}



