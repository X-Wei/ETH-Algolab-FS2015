#include <iostream>
#include <algorithm>
using namespace std;

int x, y;
int t, n, c;
int dp[10000001];

int dist(int a, int b){
	if(a == b) return 0;
	if(dp[b] == 0){ // prime number
		return 1+dist(1, a);
	}
	if(dp[b] >= a){
		return 1+dist(a, dp[b]);
	}
	else{
		return 1+dist(dp[b], a);
	}
}

int main() {
	for(int i=2; i<=10000000/2; ++i){
		int maxj = min(i, 10000000/i);
		for(int j=2; j<=maxj; ++j){
			dp[i*j] = i;
		}
	}
	cin >> t;
	while(t --){
		cin >> n >> c;
		while(c --){
			cin >> x >> y;
			cout << dist(min(x,y), max(x, y)) << endl;
		}
	}
	return 0;
}
