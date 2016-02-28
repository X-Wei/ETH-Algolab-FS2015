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

long floor_to_double(const K::FT& x)// RECOMMENDED WAY TO ROUND DOWN TO INTEGER
{
	double a = std::floor(CGAL::to_double(x));
	while (a > x)
		a -= 1;
	while (a + 1 <= x)
		a += 1;
	return (long) a;
}

void firsthit(int n) {
	long x, y, a, b;
	cin >> x >> y >> a >> b;
	K::FT min_d = -1;
	R ray = R(P(x, y), P(a, b));
	P p0 = P(x, y), p1;
	long r, s, t, u;
	rep(_,n) {
		cin >> r >> s >> t >> u;
		S seg = S(P(r, s), P(t, u));
		if (CGAL::do_intersect(ray, seg)) {
			auto o = CGAL::intersection(ray, seg);
			if (const P* op = boost::get<P>(&*o)) {
				K::FT d = CGAL::squared_distance(p0, *op);
				if (min_d == -1 || d < min_d) {
					min_d = d;
					p1 = *op;
				}
			} else if (const S* os = boost::get<S>(&*o)) {
				K::FT d1 = CGAL::squared_distance(p0, os->source()), d2 =
						CGAL::squared_distance(p0, os->target());
				K::FT d = d1 > d2 ? d2 : d1;
				P p = d1 > d2 ? os->target() : os->source();
				if (min_d == -1 || d < min_d) {
					min_d = d;
					p1=p;
				}
			}
		}// if intersects
	}// repeat n times
	if (min_d == -1)
		cout << "no" << endl;
	else
		cout << floor_to_double(p1.x()) <<" "<< floor_to_double(p1.y()) << endl;
} // firsthit()


int main() {
	int n;
	while (1) {
		cin >> n;
		if (n == 0)
			return 0;
		firsthit(n);
	}
}

