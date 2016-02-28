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
typedef Triangulation::Face_handle Face_handle;
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
	map<Vertex_handle,int> diedtime;// mapping each cell to its dead time
	
	for (Edge_iterator e = T.finite_edges_begin(); e != T.finite_edges_end(); ++e){
		K::FT len = std::sqrt(T.segment(e).squared_length());// length of the edge
		K::FT minlen = len/2; // length for collision along this edge
		Face_handle fh=e->first; int i=e->second;
		Vertex_handle vh1=fh->vertex(fh->cw(i));// ending points vh1, vh2 of edge e
		Vertex_handle vh2=fh->vertex(fh->ccw(i));
		K::FT minlen1 = min( {minlen, vh1->point().x()-l, r-vh1->point().x(), 
								t-vh1->point().y(), vh1->point().y()-b} );
		minlen1 = max(minlen1, 0.5);
		K::FT minlen2 = min( {minlen, vh2->point().x()-l, r-vh2->point().x(), 
								t-vh2->point().y(), vh2->point().y()-b} );
		minlen2 = max(minlen2, 0.5);
		
		int time1 = round_up( sqrt(minlen1-0.5) ); // t*t+1/2=minlen
		int time2 = round_up( sqrt(minlen2-0.5) ); 
		
		if(diedtime.count(vh1)==0 || diedtime[vh1]>time1) 
			diedtime[vh1]=time1;
		if(diedtime.count(vh2)==0 || diedtime[vh2]>time2) 
			diedtime[vh2]=time2;
	}
	vector<int> res;// put died time for each germ
	for(map<Vertex_handle,int>::iterator it=diedtime.begin(); it!=diedtime.end(); it++)
		res.push_back(it->second);
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
