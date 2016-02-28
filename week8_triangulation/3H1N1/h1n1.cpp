#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <queue>
#include <map>

using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation:: Finite_faces_iterator Finite_faces_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef K::Point_2 Point;
//~ enum Color {Black=0,White=1}; typedef std::map<Face_handle,Color> Colormap;
typedef std::map<Face_handle,bool> Colormap;

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

void h1n1(int n){
    vector<Point> pts;
    pts.reserve(n);
    rep(i,n){ // infected people
        Point p;
        cin >> p;
        pts.push_back(p);
    }
    // construct triangulation
    Triangulation T;
    T.insert(pts.begin(), pts.end());
    Colormap res_cache;
    
    int m; cin >> m;
    rep(i,m){ // users
        int x,y;
        long long d;
        cin >> x >> y >> d;
        Point p(x,y);
        // check initial position
        if( CGAL::squared_distance(T.nearest_vertex(p)->point(),p)<d ) // nearest vertex distance
            {cout<< "n"; continue;}
        Face_handle fh0 = T.locate(p); // the face that p is in
        // caching will not work because the ds are different! 
        // --> need to map each fh to the max d that allows to reach from fh to inf face
        //~ if( res_cache.count(fh0)==1 ) { // if result cached before
            //~ {cout << (res_cache[fh0]?'y':'n'); continue;}
        // otherwise do a BFS to try to get to an infinite face
        bool success=false;
        queue<Face_handle> q; 
        Colormap visited;
        q.push(fh0); visited[fh0]=true;
        while(!q.empty()){
            Face_handle fh = q.front(); q.pop();
            if(T.is_infinite(fh))
                {success=true;break;}
            rep(i,3){
                Face_handle nextfh = fh->neighbor(i);
                if( T.segment(fh,i).squared_length()>=4*d && visited.count(nextfh)==0 )
                    { 	if( T.is_infinite(nextfh) ) {success=true; break;}
                        q.push(nextfh); visited[nextfh]=true;
                    }
            } // go over adj faces
        } // bfs
        res_cache[fh0]=success;
        cout << (success?"y":"n");
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    int n;
    while(1){
        cin >> n;
        if(n==0) return 0;
        h1n1(n);
    }
    return 0;
}
