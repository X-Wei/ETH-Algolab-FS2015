#include <iostream>
#include <algorithm>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

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

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

void tetris(){
    int w,n; cin >> w >> n;
    Graph G(w+w-2);
    EdgeCapacityMap	capacity = get(edge_capacity, G);
    ReverseEdgeMap	rev_edge = get(edge_reverse, G);
    ResidualCapacityMap	res_capacity = get(edge_residual_capacity, G);
    EdgeAdder ea(G,capacity, rev_edge);
    forloop(v,1,w-1){
        ea.addEdge(v+w, v, 1); // v_in(index=v+w) ----> v_out(index=v), capacity=1
    }
    rep(i,n) { 
        int u,v; cin>>u>>v;// u_out --> v_in
        if(v!=w) ea.addEdge(u, v+w, 1);// u_out --> v_in
        else ea.addEdge(u, v, 1);
    }
    long flow2 = push_relabel_max_flow(G, 0, w);
    cout << flow2 << endl;
}

int main(){
    int t; cin >> t;
    rep(i,t) tetris();
    return 0;
}
