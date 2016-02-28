#include <iostream>
#include <cstdlib>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace boost;
using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor,
                property <edge_weight_t, long> > > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type       EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator


struct EdgeAdder {
    EdgeAdder(Graph & G, EdgeCapacityMap &capacity, EdgeWeightMap &weight, ReverseEdgeMap &rev_edge) 
        : G(G), capacity(capacity), weight(weight), rev_edge(rev_edge) {}

    void addEdge(int u, int v, long c, long w) {
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacity[e] = c;
        weight[e] = w;
        capacity[reverseE] = 0;
        weight[reverseE] = -w;
        rev_edge[e] = reverseE; 
        rev_edge[reverseE] = e; 
    }
    Graph &G;
    EdgeCapacityMap &capacity;
    EdgeWeightMap &weight;
    ReverseEdgeMap  &rev_edge;
};

void realestate(){
    int N,M,S;
    cin >> N >> M >> S;
    Graph G(S+M+N);// S+N+M+2 vertices in this flow graph
    Vertex v_src = add_vertex(G), v_sink = add_vertex(G);
    EdgeCapacityMap capacity = get(edge_capacity, G);
    EdgeWeightMap weight = get(edge_weight, G);
    ReverseEdgeMap rev_edge = get(edge_reverse, G);
    ResCapacityMap res_capacity = get(edge_residual_capacity, G);
    EdgeAdder ea(G, capacity, weight, rev_edge);
    
    rep(i,S){ 
        int l; // limit for each state
        cin >> l;
        ea.addEdge(v_src,i,l,0);// limit for state i
    }
    rep(i,M){
        int s; // s = the state of i
        cin >> s; // s-i -- s is 1 based!
        ea.addEdge(s-1,i+S,1,0);// state i's vertex index is i+S
    }
    int bids[N][M];
    int maxb = -1;
    rep(i,N) rep(j,M){
        int b;
        cin >> b;
        if(maxb<b) maxb=b;
        bids[i][j]=b;
        //~ ea.addEdge(j+S,i+S+M,1,-b);// buyer i bid b for site j
    } 
    rep(i,N) rep(j,M)
        ea.addEdge(j+S,i+S+M,1,-bids[i][j]+maxb);// buyer i bid b for site j
    rep(i,N) 
        ea.addEdge(i+S+M,v_sink,1,0);// buyer i can only buy 1 site!
    
    //~ // Option 1: Min Cost Max Flow with cycle_canceling
    //~ int flow1 = push_relabel_max_flow(G, v_src, v_sink);
    //~ cycle_canceling(G);
    //~ int cost1 = find_flow_cost(G);
    //~ cout << flow1 << ' ' << -cost1 << endl;
    
    // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights
    successive_shortest_path_nonnegative_weights(G, v_src, v_sink);
    int cost2 = find_flow_cost(G);
    int flow2 = 0;
    OutEdgeIt e, eend;// Iterate over all edges leaving the source
    for(tie(e, eend) = out_edges(vertex(v_src,G), G); e != eend; ++e) {
        flow2 += capacity[*e] - res_capacity[*e];
    }
    cost2 -= flow2*maxb;
    cout << flow2 << ' ' << -cost2 << endl;
}// realestate()

int main(){
    int t;
    cin >> t;
    rep(i,t) realestate();
    return 0;
}
