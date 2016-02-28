#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Vertex_iterator Vertex_iterator;
typedef Triangulation::Vertex_handle Vertex_handle; 

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

int round_up(const K::FT& e) {
    double d = std::ceil(CGAL::to_double(e)); 
    while(d < e) d++; while(d - 1 >= e) d--;  
    return d; 
}

void germs(int n){
    int l,b,r,t;
    cin >> l >> b >> r >> t;
    if(n==1){
        int x,y; cin >> x >> y;
    }
    vector<K::Point_2> pts;
    pts.reserve(n);
    rep(i,n){
        K::Point_2 p; 
        cin >> p;
        pts.push_back(p);
    }
    
    // construct triangulation
    Triangulation T;
    T.insert(pts.begin(), pts.end());
    vector<int> res;// put died time for each germ
    for (Vertex_iterator vi = T.finite_vertices_begin(); vi != T.finite_vertices_end(); ++vi){
        K::FT minlen = min( {vi->point().x()-l, r-vi->point().x(), 
                                t-vi->point().y(), vi->point().y()-b} );
        Triangulation::Edge_circulator ec = T.incident_edges(vi);// find all incident edges of vi
        do {
            if (T.is_infinite(ec)==false) {
                K::FT len = std::sqrt(T.segment(ec).squared_length());// length of the edge
                len/=2;
                minlen = min(len, minlen);
            }
        } while (++ec != T.incident_edges(vi));
        minlen = max(minlen, 0.5);
        int time = round_up( sqrt(minlen-0.5) ); // t*t+1/2=minlen
        res.push_back(time);
    }	
    sort(res.begin(), res.end());
    assert(res.size()==n);
    cout << res[0] << " " << res[n/2] << " " << res[n-1] << endl;
}

int main(){
    int n;
    while(1){
        cin >> n;
        if(n==0) return 0;
        germs(n);
    }
}
