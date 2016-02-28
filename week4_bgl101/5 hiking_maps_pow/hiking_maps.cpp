#include <iostream>
#include <queue> // std::priority_queue
#include <vector>
#include <climits>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

bool in_triangle(const vector<Point>& v, const Point& p){
	for(int i=0; i<=4; i+=2){ // i=0,2,4
		if( CGAL::left_turn(v[i], v[i+1], v[(i+2)%6]) ){// canNOT just write left_trun==left_turn --> colinear situation!!
			if( CGAL::right_turn(v[i], v[i+1], p) ) return false;
		}else if( CGAL::left_turn(v[i], v[i+1], p) ) return false;
	}
	return true;
}

struct MyCmpStruct{
    // pair: <segid, mapid>, compare by mapid
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs){
        return (lhs.second > rhs.second);// <s1, m1> is smaller than <s2,m2> if m1>m2 -- we want MIN pq!
    }
};

void hiking(){
	int n,m;// m-1 legs, n map triangles
	cin >> m >> n;
	vector<Point> pts; pts.reserve(m);
	rep(i,m){ 
		Point p; cin >> p;
		pts.push_back(p);
	}
	vector<int> seg_maps[m-1];
	rep(i,m-1) seg_maps[i]=vector<int>(0);
	rep(i,n){
		vector<Point> v; Point vi;
		rep(j,6) {cin>>vi; v.push_back(vi);}
		rep(j,m-1){
			if( in_triangle(v,pts[j]) && in_triangle(v,pts[j+1]) )
				seg_maps[j].push_back(i);// map i contains segment j
		}
	}// seg_maps[i] = mapids that contains seg-i, in ascending order
	// doing similar to snippets, find best cost
	int min_d = INT_MAX;
	vector<int> index(m-1,0); 
	priority_queue<pair<int,int>, vector<pair<int,int> >, MyCmpStruct> pq;// <segid, mapid> with minimum position(mapid) on top
	int maxpos=-1;
    rep(i,m-1){
		pq.push( make_pair(i,seg_maps[i][index[i]]) );
		maxpos = max(maxpos, seg_maps[i][0]);
	}
	while (1) {
        int i = pq.top().first, minpos = pq.top().second; // ith seg has minimum mapid
        int d = maxpos - minpos + 1; // maxpos-minpos
        min_d = min(d,min_d);
        index[i]++;// will move this i's index forward
        if(index[i]==seg_maps[i].size()||min_d==1) break; // if cannot move min_i, then finish
        int newpos = seg_maps[i][index[i]];
        maxpos = max(newpos, maxpos);
        pq.pop();
        pq.push( make_pair(i,newpos) );
    }
    cout << min_d << endl;
}// hiking()

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; cin >> t;
	rep(i,t) hiking();
    return 0;
}
