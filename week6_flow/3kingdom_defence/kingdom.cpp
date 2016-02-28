#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
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

void kingdom(){
    int l,p,f,t,c,C;
    cin >> l >> p;
    Graph G(l);
	EdgeCapacityMap	capacity = get(edge_capacity, G);
	ReverseEdgeMap	rev_edge = get(edge_reverse, G);
	EdgeAdder ea(G,capacity, rev_edge);
    
    int gs[l],ds[l];
    rep(i,l) cin >> gs[i] >> ds[i];
    rep(i,p){// setting min edge flow, recalculat the stocks in each vertex!
        cin >> f >> t >> c >> C;
        gs[f] -= c; // let min capacity flow first through edge
        gs[t] += c;
        ea.addEdge(f,t,C-c);// new capacity limit is C-c
    }
    
    // now this is a circulation pb
    Vertex _source = add_vertex(G);
	Vertex sink = add_vertex(G);
    int supply=0, demand=0;
    rep(i,l) {
        if(gs[i]>ds[i]) 
            {ea.addEdge(_source, i, gs[i]-ds[i]); supply+=gs[i]-ds[i];}
        else if(gs[i]<ds[i]) 
            {ea.addEdge(i, sink, ds[i]-gs[i]); demand+=ds[i]-gs[i];}
    }
    int flow = push_relabel_max_flow(G, _source, sink);
    //~ cout << flow <<" "<< demand <<" "<< supply <<" ";
    cout << (flow==demand?"yes":"no") << endl;
    
}

int main(){
    int t;
    cin >> t;
    rep(i,t) kingdom();
    return 0;
}
