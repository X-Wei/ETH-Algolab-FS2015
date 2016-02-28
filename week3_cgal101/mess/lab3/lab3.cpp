#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <type_traits>
#include <CGAL/intersections.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); i++)
#define rep(i,N) forloop(i,0,N-1)

void hit(int n) {
	long x, y, a, b, r, s, t, u;
	cin >> x >> y >> a >> b;
	R ray(P(x, y), P(a, b));
	bool ret = false;
	rep(_,n)
	{
		cin >> r >> s >> t >> u;
		S seg(P(r, s), P(t, u));
		if (!ret && CGAL::do_intersect(ray, seg)) {
			ret = true;
		}
	}
	if (ret)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
} //hit()

double floor_to_double(const K::FT& x) {
	double a = std::floor(CGAL::to_double(x));
	while (a > x)
		a -= 1;
	while (a + 1 <= x)
		a += 1;
	return a;
}

void antenna(int n) {
	long x, y;
	P citizens[n];
	rep(i,n)
	{
		cin >> x >> y;
		citizens[i] = P(x, y);
	}
	Min_circle mc(citizens, citizens + n, true);
	Traits::Circle c = mc.circle();
	K::FT r2 = c.squared_radius();
	long r = sqrt(CGAL::to_double(r2));
	if (r * r < floor_to_double(r2))
		r += 1;
	cout << r << endl;
} //antenna()

void firsthit(int n) {
	long x, y, a, b, r, s, t, u;
	cin >> x >> y >> a >> b;
	P start = P(x, y);
	R ray(start, P(a, b));
	double mindist = -1;
	P firsthit;
	rep(_,n)
	{
		cin >> r >> s >> t >> u;
		S seg(P(r, s), P(t, u));
		if (CGAL::do_intersect(ray, seg)) {
			auto o = CGAL::intersection(ray, seg);
//			P intp;
//			if (const P* op = boost::get<P>(&*o));
//				intp = op;
//			P intp = CGAL::intersection(ray, seg);
//			double d2 = CGAL::to_double(CGAL::squared_distance(intp, start));
//			if (mindist < 0 || d2 < mindist) {
//				mindist = d2;
//				firsthit = intp;
//			}
		} //if intersect
	} //rep
	if (mindist == -1)
		cout << "no" << endl;
	else
		cout << firsthit.x() << ' ' << firsthit.y() << endl;
} // firsthit()

void almostantenna(int n) {
	long x, y;
	P citizens[n];
	rep(i,n)
	{
		cin >> x >> y;
		citizens[i] = P(x, y);
	}
	Min_circle mc(citizens, citizens + n, true);
	Traits::Circle c = mc.circle();
	P p = mc.Support_point_iterator;
	while(p){
		cout << p.x() <<" "<< p.y()<<endl;
		p++;
	}
	K::FT r2 = c.squared_radius();
	long r = sqrt(CGAL::to_double(r2));
	if (r * r < floor_to_double(r2))
		r += 1;
	cout << r << endl;
} //almostantenna()

int main() {
	int n;
	cin >> n;
	while (n != 0) {
//		hit(n);
//		antenna(n);
		firsthit(n);
		cin >> n;
	}
	return 0;
}
