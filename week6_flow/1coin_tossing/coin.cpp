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
        if(c==0) return;
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

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

void coin(){
    int n,m;
    cin >> n >> m;
    // Create Graph and Maps
	Graph G(n+m);// **vertex 0~m-1: rounds; vertex m~m+n-1: players**
    // !!player K is vertex K+m!!
	EdgeCapacityMap	capacity = get(edge_capacity, G);
	ReverseEdgeMap	rev_edge = get(edge_reverse, G);
	ResidualCapacityMap	res_capacity = get(edge_residual_capacity, G);
	EdgeAdder ea(G,capacity, rev_edge);
    
    int a,b,c;
    rep(i,m){
        cin >> a >> b >> c;
        if(c==1 || c==0) // a won
            ea.addEdge(i,a+m,1);
        if(c==2 || c==0) // b won
            ea.addEdge(i,b+m,1);
    }
    
    int s[m];
    int sum=0;
    rep(i,n){
        cin >> s[i]; // score for each player
        sum += s[i];
    }
    //~ if(m!=sum){cout<< "no" << endl;
        //~ return;}
    
    // Add source and sink
	Vertex _source = add_vertex(G);
	Vertex _sink = add_vertex(G);
    rep(i,m) ea.addEdge(_source,i,1);
    rep(i,n) {if(s[i]>0) ea.addEdge(i+m,_sink,s[i]);}
    long flow = push_relabel_max_flow(G, _source, _sink);
    cout << (flow==m?"yes":"no") << endl;
}

int main(){
    int t;
    cin >> t;
    rep(_,t)
        coin();
    return 0;
}
