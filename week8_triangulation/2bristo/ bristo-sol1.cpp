#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/squared_distance_2.h>
#include <typeinfo>
#include <map>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Face_handle  Face_handle;
typedef Triangulation::Vertex_handle  Vertex_handle;

using namespace std;

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

void bristo(int n){
    std::vector<K::Point_2> pts;// should NOT write n here!! will cause ERR/WA on judge (runs good locally)
    pts.reserve(n); // instead we can do this
    rep(i,n){
        K::Point_2 p;
        cin >> p;
        pts.push_back(p);
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    int m; cin >> m;
    std::vector<K::Point_2> newpts;
    map<K::Point_2, int> index;
    rep(j,m){
        K::Point_2 p;
        cin >> p;
        newpts.push_back(p);
        index[p]=j;
        //~ K::Point_2 nearest = t.nearest_vertex(p)->point();
        //~ cout << CGAL::squared_distance(p,nearest) << endl;
    }
    spatial_sort(newpts.begin(), newpts.end());// use spatial sort to speedup nearest-vertex finding --> for cases when m is large
    Face_handle fh;
    double res[m];
    rep(j,m){
				Vertex_handle vh = t.nearest_vertex(newpts[j],fh);
				res[index[newpts[j]]] = CGAL::to_double( CGAL::squared_distance(newpts[j],vh->point()) );
				fh = vh->face();
		}
		rep(j,m) cout << res[j] << endl;
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
