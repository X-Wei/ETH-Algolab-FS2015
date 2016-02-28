#include <iostream>
#include <algorithm>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

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

void phantom(){
    int n,m,s,d; cin >>n >>m >>s >>d;
    // Create Graph and Maps
	Graph G(n*2); // create graph with 2n vertices: 
    // ** "parallel" graph of 2 layers, vertex i in layer 1 --> vertex i+n in layer 2 **
	EdgeCapacityMap	capacity = get(edge_capacity, G);
	ReverseEdgeMap	rev_edge = get(edge_reverse, G);
	//~ ResidualCapacityMap	res_capacity = get(edge_residual_capacity, G);
	EdgeAdder ea(G,capacity, rev_edge);
    rep(i,n)//adding the link: vertex i in layer 1 --> vertex i+n (i') in layer 2
        ea.addEdge(i, i+n, 1);// mirror vertex i'=i+n
    rep(_,m){ 
        int u,v; cin >> u >> v;
        /* **************************edge u->v ==> transform to u->u'->v->v' **************************
         *              ==> so that if edge uv is taken, vertex u and v('s vertical edge) is also taken!*/
        ea.addEdge(u+n, v, 1);
    }
    Vertex _source = add_vertex(G);
	Vertex sink = add_vertex(G);
    rep(i,s){// reading start points
        int si; cin >> si;
        ea.addEdge(_source, si, 1);
    }
    rep(i,d){// reading destination points
        int di; cin >> di;
        ea.addEdge(di+n, sink, 1);
    }
    // the maxflow gives nb of edge-disjoint paths in G, which is nb of vertex-disjoint paths in original graph --> this is the answer
    long flow2 = push_relabel_max_flow(G, _source, sink);
    cout << flow2 << endl;
}

int main(){
	int t; cin >> t;
	rep(i,t) phantom();
    return 0;
}
