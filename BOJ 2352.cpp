/*
BOJ 2352 - 반도체 설계
LIS 문제이다.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF (int)2e9
int a[40001];
vector<int> v;
int n;
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];

	v.push_back(-INF);
	vector<int>::iterator iter;
	for (int i = 1; i <= n; i++) {
		if (v[v.size() - 1] < a[i]) {
			v.push_back(a[i]);
		}
		else {
			iter = lower_bound(v.begin(), v.end(), a[i]);
			*iter = a[i];
		}
	}
	printf("%d", v.size() - 1);
	return 0;
}
