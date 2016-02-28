#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>	// tuples::ignore
#include <boost/graph/max_cardinality_matching.hpp>
using namespace std;
using namespace boost;

typedef	adjacency_list<vecS, vecS, undirectedS>	Graph;
typedef	graph_traits<Graph>::edge_descriptor	Edge;	// Edge type
typedef	graph_traits<Graph>::vertex_descriptor	Vertex;	// Edge type
typedef graph_traits<Graph>::edge_iterator	EdgeIt;	// Iterator

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

/*  König's theorem:
* In bipartite graphs, the size of minimum vertex cover is equal to the size of the maximum matching; 
* An alternative and equivalent form of this theorem is: the size of the maximum independent set plus the size of the maximum matching is equal to the number of vertices.
* for a max matching given ==> for each edge there exists a vertex from the min vertex set (cf. more flows ppt)
* ==> removing this vertex will remove all edges in graph ==> the resting vertices are from the independent set 
 * */

void knights(){
    int n; cin >> n;
    int a[n][n]; int holes=0;
    rep(i,n) rep(j,n) {cin >> a[i][j];if(a[i][j]==0) holes++;}
    Graph G(n*n); 
    const int dx[8]={-1,-1,1,1,-2,-2,2,2};
    const int dy[8]={-2,2,-2,2,-1,1,-1,1};
    rep(x,n) rep(y,n){
        rep(i,8){
            int newx=x+dx[i], newy=y+dy[i];
            if(a[x][y]==1 // don't forget this condition!!!
                && newx<n && newx>=0 && newy<n && newy>=0 
                && a[newx][newy]==1){
                add_edge(x+y*n, newx+newy*n, G);
            }
        }
    }// construct graph
    vector<Vertex> mate(n*n);
    checked_edmonds_maximum_cardinality_matching(G, &mate[0]);
    int matched = matching_size(G, &mate[0]);
    cout << n*n-holes-matched << endl;
}

int main(){
    int t; cin >> t;
    rep(i,t) knights();
    return 0;
}

