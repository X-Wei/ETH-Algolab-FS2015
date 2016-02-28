#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

// Graph typedefs
typedef	adjacency_list_traits<vecS, vecS, directedS>	Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, int,
		property<edge_residual_capacity_t, int,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
typedef	graph_traits<Graph>::edge_descriptor			Edge;
typedef graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::out_edge_iterator			OutEdgeIt;
typedef property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;

// Custom Add Edge for flow problems
void addEdge(int from, int to, int c, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {
	Edge e, reverseE;
	tie(e, tuples::ignore)		= add_edge(from, to, G);
	tie(reverseE, tuples::ignore)	= add_edge(to, from, G);
	capacity[e]		= c;
	capacity[reverseE]	= 0;
	rev_edge[e]		= reverseE;
	rev_edge[reverseE]	= e;
}

void satellites(){
    int g,s,l,gi,sj;
    cin >> g >> s >> l;
    Graph G(g+s);// ground-i=i; satellite-j=j+g
	EdgeCapacityMap		capacity = get(edge_capacity, G);
	ReverseEdgeMap		rev_edge = get(edge_reverse, G);
	ResidualCapacityMap	residue = get(edge_residual_capacity, G);
    Vertex _source = add_vertex(G);
	Vertex sink = add_vertex(G);
    rep(i,g) 
        addEdge(_source, i, 1, capacity, rev_edge, G);
    rep(j,s) 
        addEdge(j+g, sink, 1, capacity, rev_edge, G);    
    rep(i,l){
        cin >> gi >> sj;
        addEdge(gi, sj+g, 1, capacity, rev_edge, G);    
    }
    // Find a min cut via maxflow
    push_relabel_max_flow(G, _source, sink);
    
    // then do a BFS on residual graph
    vector<bool> vis(num_vertices(G), false);// mark all vertices as unvisited
    vis[_source] = true; 
    std::queue<int> Q; // need to specify the STD!!
    Q.push(_source);// BFS from source
    while(!Q.empty()){
        const int u = Q.front();
        Q.pop();
        OutEdgeIt ebeg, eend;
        for(tie(ebeg,eend)=out_edges(u,G); ebeg!=eend; ++ebeg){
            const int v = target(*ebeg, G);// edge = u-->v
            if(vis[v]==false && residue[*ebeg]>0)// the BFS is in residual graph...
                {Q.push(v); vis[v]=true;}
        }
    }// while Q not empty
    
    // min vertex cover = unvisited vertices in L, visited vertices in R
    vector<int> gs,ss;
    rep(i,g+s){
        if(i<g && vis[i]==false) gs.push_back(i);
        if(i>=g && vis[i]==true) ss.push_back(i-g);
    }
    cout << gs.size() << " " << ss.size() << endl;
    rep(i,gs.size()) cout << gs[i] << " ";
    rep(i,ss.size()) cout << ss[i] << " ";
    cout << endl;
}

int main(){
    int t;
    cin >> t;
    rep(i,t) 
        satellites();
    return 0;
}
