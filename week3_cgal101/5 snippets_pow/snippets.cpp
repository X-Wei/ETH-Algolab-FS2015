#include <iostream>
#include <cmath>
#include <queue> // std::priority_queue
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); i++)
#define rep(i,N) forloop(i,0,N-1)

void snippets() {// solution not using a pq
	int n;
	cin >> n;
	int m[n];
	rep(i,n)
		cin >> m[i];
	int** p = new int*[n];
	rep(i,n) {
		p[i] = new int[m[i]];
		rep(j,m[i])
			cin >> p[i][j];
	}
	int indices[n];// index of each word, initialize to 0
	rep(i,n)
		indices[i] = 0;
	int mind = 2147483640;
	while (1) {
		int min = 2147483640, max = -2147483640, mini = 0;
		rep(i,n) {
			int pos = p[i][indices[i]];
			if (pos < min) {
				min = pos;
				mini = i;
			}
			if (pos > max)
				max = pos;
		}
		if (max - min + 1 < mind)
			mind = max - min + 1;
		if (indices[mini] < m[mini])
			indices[mini]++;
		else
			break;

	}
	cout << mind << endl;
}

struct MyCmpStruct{
    // pair: <wordid, index>, compare by index
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs){
        return (lhs.second > rhs.second);// <w1, p1> is smaller than <w2,p2> if p1>p2 -- we want MIN pq!
    }
};

void snippets2() {// solution using a pq
    int n; cin >> n;
    int m[n];
    rep(i,n) 
        cin >> m[i];
    int* p[n];
    int maxpos = -1;
    rep(i,n) {
        p[i] = new int[m[i]];
        rep(j,m[i]) cin >> p[i][j];
        maxpos = max(maxpos, p[i][0]);
    }
    vector<int> index(n,0);
    int min_d = INT_MAX;
    priority_queue<pair<int,int>, vector<pair<int,int> >, MyCmpStruct> pq;// index with minimum position is on top
    rep(i,n) pq.push( make_pair(i,p[i][index[i]]) );
    while (1) {
        int i = pq.top().first, minpos = pq.top().second; // ith word has minimum position
        int d = maxpos - minpos + 1; // maxpos-minpos
        min_d = min(d,min_d);
        index[i]++;// will move this i's index forward
        if(index[i]==m[i]) break; // if cannot move min_i, then finish
        int newpos = p[i][index[i]];
        maxpos = max(newpos, maxpos);
        pq.pop();
        pq.push( make_pair(i,newpos) );
    }
    cout << min_d << endl;
    rep(i,n) delete p[i];
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	rep(_,t)
		snippets2();
	return 0;
}
