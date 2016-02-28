#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)
struct flowVertex{
    int station; int time;// station id and arrive/departure time
    int index;// vertex index in the flow graph
    flowVertex(int s, int t,int i)
        {station=s;time=t;index=i;}
    bool operator < ( const flowVertex & other ) const {
        return time < other.time;// for sorting
    }
};
int main(){
    vector<int> arrvec[3];
    arrvec[0].push_back(1);
    cout << arrvec[0][0]<<endl;
    
    vector<flowVertex> vertices[2];
    flowVertex fv1(1,1,1);
    vertices[0].push_back(fv1);
    cout << vertices[0][0].station<<endl;
    
    return 0;
}
