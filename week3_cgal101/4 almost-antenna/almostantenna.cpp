#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <cmath>
#include <set>

// typedefs
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); i++)
#define rep(i,N) forloop(i,0,N-1)

long floor_to_double(const K::FT& x)// RECOMMENDED WAY TO ROUND DOWN TO INTEGER
{
	double a = std::floor(CGAL::to_double(x));
	while (a > x)
		a -= 1;
	while (a + 1 <= x)
		a += 1;
	return (long) a;
}
long ceiling_to_double(const K::FT& x)// RECOMMENDED WAY TO ROUND DOWN TO INTEGER
{
	double a = std::floor(CGAL::to_double(x));
	while (a < x)
		a += 1;
	while (a - 1 >= x)
		a -= 1;
	return (long) a;
}

void almost_antenna(int n) {
	long x, y;
	P points[n];
	rep(i,n) {
		cin >> x >> y;
		points[i] = K::Point_2(x, y);
	}
	if (n <= 2) {//special case
		cout << 0 << endl;
		return;
	}
	Min_circle mc(points, points + n, true);
	Traits::Circle c = mc.circle();
	K::FT min_r = c.squared_radius();
	if (mc.is_degenerate() == false) {// tries to remove one point iff mc is not degenerate (<=3 support points)
		//set<P> allpoints(points, points + n);
		for (int i = 0; i < mc.number_of_support_points(); i++) {
			P sp = mc.support_point(i);
			P new_points[n - 1];
			int j = 0;
			rep(i,n) {
				if (points[i] != sp)
					new_points[j++] = points[i];
			}
			//allpoints.erase(sp);// remove the ith support point
			//Min_circle mc2(allpoints.begin(), allpoints.end(), true);
			//allpoints.insert(sp);
			Min_circle mc2(new_points, new_points + n - 1, true);
			K::FT r = mc2.circle().squared_radius();
			if (r < min_r)
				min_r = r;
		}
	}// if mc not degenerate
	cout << ceiling_to_double(sqrt(min_r)) << endl;
}//almost_antenna(n)

int main() {
	int n;
	while (1) {
		cin >> n;
		if (n == 0)
			return 0;
		almost_antenna(n);
	}
}
