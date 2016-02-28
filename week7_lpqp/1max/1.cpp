#include <iostream>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>
#include <CGAL/Quotient.h>
#include <cmath>

using namespace std;

typedef CGAL::Gmpzf ET; 
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

Solution sol;

int round_up(const CGAL::Quotient<ET>& e) {
  double d = std::ceil(CGAL::to_double(e));
  while (d < e) d++;
  while (d - 1 >= e) d--;
  return d;
}

int round_down(const CGAL::Quotient<ET>& e) {
  double d = std::floor(CGAL::to_double(e));
  while(d > e) d--;
  while(d + 1 <= e) d++;
  return d;
}

void opt_one(int a, int b) {
  Program qp(CGAL::SMALLER, true, 0, false, 0);
  int x = 0, y = 1;
  //objective function
  //ax^2
  qp.set_d(x, x, 2*a);
  //-by
  qp.set_c(y, -b);

  //first condition
  //1x
  qp.set_a(x, 0, 1);
  //1y
  qp.set_a(y, 0, 1);
  //4
  qp.set_b(0, 4);

  //second condition
  //4x
  qp.set_a(x, 1, 4);
  //2y
  qp.set_a(y, 1, 2);
  //ab
  qp.set_b(1, a*b);

  //third condition
  //-x
  qp.set_a(x, 2, -1);
  //y
  qp.set_a(y, 2, 1);
  //1
  qp.set_b(2, 1);
  sol = CGAL::solve_nonnegative_quadratic_program(qp, ET());
}

int opt_two(int a, int b) {
  Program qp(CGAL::LARGER, false, 0, false, 0);

  int x = 0, y = 1, z = 2;

  qp.set_u(x, true);
  qp.set_u(y, true);
  qp.set_u(z, false);
  qp.set_l(z, true);

  //objective function
  //ax^2
  qp.set_d(x, x, 2*a);
  //z^2
  qp.set_d(z, z, 2);
  //linear part
  qp.set_c(y, b);

  //first condition
  //x
  qp.set_a(x, 0, 1);
  //y
  qp.set_a(y, 0, 1);
  //-4
  qp.set_b(0, -4);

  //second condition
  //4x
  qp.set_a(x, 1, 4);
  //2y
  qp.set_a(y, 1, 2);
  //z
  qp.set_a(z, 1, 1);
  //-ab
  qp.set_b(1, -a*b);

  //third condition
  qp.set_a(x, 2, -1);
  qp.set_a(y, 2, 1);
  qp.set_b(2, -1);
  
  sol = CGAL::solve_quadratic_program(qp, ET());
}

int main() {
  int p, a, b; 
  while (true) {
    cin >> p;
    if (p == 0)
      break;
    cin >> a >> b;
    bool one;
    if (p == 1) {
      opt_one(a, b);
      one = true;
    } else if (p == 2) {
      opt_two(a, b);
      one = false;
    }

    if (sol.is_infeasible())
      cout << "no";
    else if (sol.is_unbounded())
      cout << "unbounded";
    else if (sol.is_optimal()) {
      if (one) 
        cout << round_down(-sol.objective_value()); //NOTE the -
      else  {
        cout << round_up(sol.objective_value());
        //auto it = sol.variable_values_begin();
        //ET x = *it;
        //ET y = *(it + 1);
        //ET z = *(it + 2);
        //cout << round_down(a*pow(x, 2)+b*y+pow(z, 4));
      }
    }
    cout << endl;
  } 
}
