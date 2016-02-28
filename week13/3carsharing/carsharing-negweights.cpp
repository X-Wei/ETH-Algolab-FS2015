#include <iostream>
#include <vector>
#include <algorithm>
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

struct flowVertex{
    int station; int time;// station id and arrive/departure time
    int index;// vertex index in the flow graph
    flowVertex(int s, int t,int i)
        {station=s;time=t;index=i;}
    bool operator < ( const flowVertex & other ) const {
        return time < other.time;// for sorting
    }
};

void carsharing(){
    int N,S; cin >> N >> S;
    int l[S]; 
    rep(i,S) cin >> l[i];
    Graph G;// at most N*S vertices
    EdgeCapacityMap capacity = get(edge_capacity, G);
    EdgeWeightMap weight = get(edge_weight, G);
    ReverseEdgeMap rev_edge = get(edge_reverse, G);
    //~ ResCapacityMap res_capacity = get(edge_residual_capacity, G);
    EdgeAdder ea(G, capacity, weight, rev_edge);

    vector<flowVertex> vertices[S]; // use S vectors to store flow vertices for each station
    rep(i,N){// add N horizontal edges
        int i1=add_vertex(G),i2=add_vertex(G); 
        int si,ti,di,ai,pi; cin>>si>>ti>>di>>ai>>pi;
        flowVertex fv1(si-1,di,i1),fv2(ti-1,ai,i2);
        vertices[si-1].push_back(fv1); // ATTENTION: si ti are 1-based indexing!!
        vertices[ti-1].push_back(fv2);
        ea.addEdge(fv1.index, fv2.index, 1, -1*pi); // adding horizontal edges
    }
    // now add vertical edges for each station
    rep(i,S){//add vertical edges for station i
        vector<flowVertex>& vs = vertices[i];
        sort(vs.begin(), vs.end());//sort by time
        rep(j,vs.size()-1){
            ea.addEdge(vs[j].index, vs[j+1].index, 100, 0);// vertical edges
            if(vs[j].time==vs[j+1].time) // ***careful! if time are equal, the edge is bidirectional!!***
                ea.addEdge(vs[j+1].index, vs[j].index, 100, 0);// vertical edges
        }
    }
    // add source and sink for flow
    Vertex v_source = add_vertex(G);
    Vertex v_target = add_vertex(G);
    rep(i,S) {
        vector<flowVertex>& vs = vertices[i];
        if(vs.size()==0) continue;
        ea.addEdge(v_source, vs.front().index, l[i], 0);
        ea.addEdge(vs.back().index ,v_target, 100, 0);
    }
    // Option 1: Min Cost Max Flow with cycle_canceling
    int flow1 = push_relabel_max_flow(G, v_source, v_target);
    cycle_canceling(G);
    int cost1 = find_flow_cost(G);
    cout << -cost1 << endl;
    
}

int main(){
    int t; cin >> t;
    rep(i,t) carsharing();
    return 0;
}
