#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

inline bool isOn(int x, int pos, int k) {
	int a = k-(pos%k)-1;
	return (x & (1 << a)) != 0;  
}

void testcase() {
	int n, k, x, xInv;
	std::cin >> n >> k >> x;
	std::vector<bool> bulbs(n);
	std::vector<int> minSteps0(n);
	std::vector<int> minSteps1(n);

	for (int i=0; i<n; i++) {
		bool a;
		std::cin>>a;
		bulbs[i] = a;
	}

	minSteps0[0] = isOn(x,0,k)==bulbs[0] ? 0 : 1;
	minSteps1[0] = isOn(x,0,k)!=bulbs[0] ? 0 : 1;
	for (int i=1; i<n; i++) {
		if (i%k==k-1) {
			minSteps0[i] = isOn(x,i,k)==bulbs[i] ? 
				minSteps0[i-1] : 
				1+std::min(minSteps0[i-1],minSteps1[i-1]);
			minSteps1[i] = isOn(x,i,k)!=bulbs[i] ? 
				minSteps1[i-1] : 
				1+std::min(minSteps0[i-1],minSteps1[i-1]);
		} else {
			minSteps0[i] = isOn(x,i,k)==bulbs[i] ? minSteps0[i-1] : 1+minSteps0[i-1];
			minSteps1[i] = isOn(x,i,k)!=bulbs[i] ? minSteps1[i-1] : 1+minSteps1[i-1];
		}
	}
	/* // Debug information
	for (int i=0; i<n; i++) {
		std::cout << bulbs[i]?"1":"0";
	}
	std::cout << "\n";
	for (int i=0; i<n; i++) {
		std::cout << isOn(x,i,k)?"1":"0";
	}
	std::cout << "\n-----\n";
	for (int i=0; i<n; i++) {
		std::cout << minSteps0[i];
	}
	std::cout << "\n";
	for (int i=0; i<n; i++) {
		std::cout << minSteps1[i];
	}
	std::cout << "\n";//*/
	std::cout << minSteps0[n-1] << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int c;
	std::cin >> c;
	for (int i=0; i<c; i++) {
		testcase();
	}
}
