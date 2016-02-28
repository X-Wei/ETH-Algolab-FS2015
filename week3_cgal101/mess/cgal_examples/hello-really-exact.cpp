#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <iostream>
#include <cmath>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;

double floor_to_double(const K::FT& x)// RECOMMENDED WAY TO ROUND DOWN TO INTEGER
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

int main()
{
  K::Point_2 p(2,1), q(1,0), r(-1,-1);
  K::Line_2 l(p,q);
  K::FT d = sqrt(CGAL::squared_distance(r,l));
  std::cout << d << std::endl;
  std::cout << floor_to_double(d) << std::endl;
}
