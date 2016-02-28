#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <cmath>

// typedefs
typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); i++)
#define rep(i,N) forloop(i,0,N-1)


long floor_to_double(const K::FT& x)// RECOMMENDED WAY TO ROUND DOWN TO INTEGER
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return (long)a;
}
long ceiling_to_double(const K::FT& x)// RECOMMENDED WAY TO ROUND DOWN TO INTEGER
{
  double a = std::floor(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return (long)a;
}

void antenna(int n){
	long x,y;
	K::Point_2 P[n];
	rep(i,n){
		cin>>x>>y;
		P[i] = K::Point_2(x,y);
	}
	Min_circle mc(P, P+n, true);
	Traits::Circle c = mc.circle();
	K::FT r = c.squared_radius();
	cout<<ceiling_to_double(sqrt(r))<<endl;
}//antenna(n)

int main()
{
	int n;
	while(1){
		cin>>n;
		if(n==0) return 0;
		antenna(n);
	}
}
