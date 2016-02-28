#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/squared_distance_2.h>
#include <typeinfo>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

using namespace std;

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

void bristo(int n){
    std::vector<K::Point_2> pts;
    pts.reserve(n); // instead we can do this
    rep(i,n){
        K::Point_2 p;
        cin >> p;
        pts.push_back(p);
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    int m; cin >> m;
    rep(j,m){
        K::Point_2 p;
        cin >> p;
        K::Point_2 nearest = t.nearest_vertex(p)->point();
        cout << CGAL::squared_distance(p,nearest) << endl;
        //~ double d = CGAL::to_double(CGAL::squared_distance(p,nearest));
        //~ cout<<std::fixed<<setprecision(0)<<d<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(0);
    int n;
    while(1){
        cin >> n;
        if(n==0) return 0;
        bristo(n);
    }
}
