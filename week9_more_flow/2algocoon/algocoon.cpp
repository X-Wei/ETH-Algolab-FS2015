#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <queue>

using namespace std;
using namespace boost;

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;
typedef graph_traits<Graph>::edge_iterator	EdgeIt;	// Iterator
typedef	graph_traits<Graph>::out_edge_iterator			OutEdgeIt;

// Custom EdgeAdder that encapsulates the references to the graph and its
// property maps and always creates reverse edges with corresponding capacities.
struct EdgeAdder {
	EdgeAdder(Graph & G, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge) 
		: G(G), capacity(capacity), rev_edge(rev_edge) {}

	void addEdge(int u, int v, long c) {
		Edge e, reverseE;
		tie(e, tuples::ignore) = add_edge(u, v, G);
		tie(reverseE, tuples::ignore) = add_edge(v, u, G);
		capacity[e] = c;
		capacity[reverseE] = 0;
		rev_edge[e] = reverseE;
		rev_edge[reverseE] = e;
	}
	Graph &G;
	EdgeCapacityMap	&capacity;
	ReverseEdgeMap	&rev_edge;
};

void algocoon(){
    int n,m,a,b,c;
    cin >> n >> m;
    Graph G(n);
	EdgeCapacityMap	capacity = get(edge_capacity, G);
	ReverseEdgeMap	rev_edge = get(edge_reverse, G);
	ResidualCapacityMap	res_capacity = get(edge_residual_capacity, G);
	EdgeAdder ea(G,capacity, rev_edge);
    rep(i,m){
        cin >> a >> b >> c;
        ea.addEdge(a, b, c);
    }
    long mincost=LONG_MAX;
    int s=0;
    int bestt=0,bests;
    // for s=0, t=1...n-1, find maxflow, select the best mincut
    
    forloop(t,1,n-1){
        long flow = push_relabel_max_flow(G, s, t);
        if(flow<mincost)
            {mincost=flow; bests=s;bestt=t;}
        // ** remark: ST cut might not be optimal: maybe TS cut is optimal!!!!!**
        flow = push_relabel_max_flow(G, t, s);
        if(flow<mincost)
            {mincost=flow; bests=t;bestt=s;}
    }
    cout << mincost << endl;
    
    push_relabel_max_flow(G, bests, bestt);
    // now that we have found the best s-t cut, and the minflow is from S to T, so I will take the vertices in S!!
    // doing a BFS on residual graph will get the S set
    vector<bool> vis(num_vertices(G), false);// mark all vertices as unvisited
    vis[bests] = true; // if i is in set S, vis[i]=true; else vis[i]=false
    std::queue<int> Q; // need to specify the STD!!
    Q.push(bests);// BFS from source
    while(!Q.empty()){
        const int u = Q.front(); Q.pop();
        OutEdgeIt ebeg, eend;
        for(tie(ebeg,eend)=out_edges(u,G); ebeg!=eend; ++ebeg){
            const int v = target(*ebeg, G);// edge = u--v
            if(vis[v]==false && res_capacity[*ebeg]>0)// the BFS is in residual graph...
                {Q.push(v); vis[v]=true;}
        }
    }// BFS on Gf
    // now we have the mincut (S,T) represented by vis[.]
    vector<int> res;
    rep(i,n) 
        if(vis[i]) res.push_back(i);
    cout << res.size();
    rep(i, res.size()) cout << " " << res[i];
    cout << endl;
    
}

int main(){
    int t;
    cin >> t;
    rep(i,t) 
        algocoon();
    return 0;
}
