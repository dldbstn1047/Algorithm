/*
	BOJ 14888 - 연산자끼워넣기(*)
*/
#include <iostream>
#include <algorithm>
#include <vector>

#define INF (int)2e9
using namespace std;

int n;
int op[5]; // + - * / 순
int a[12];
int MAX = -INF;
int MIN = INF;
vector<int> v;
void sol() {
	int ret = a[1];
	for (int i = 1; i < v.size(); i++) {
		if (v[i] == 1) {
			ret += a[i+1];
		}
		else if (v[i] == 2) {
			ret -= a[i+1];
		}
		else if (v[i] == 3) {
			ret *= a[i+1];
		}
		else if (v[i] == 4) {
			ret /= a[i+1];
		}
	}
	MIN = min(MIN, ret);
	MAX = max(MAX, ret);
}
void dfs(int index) {
	if (index > n - 1 ) {
		sol();
		return;
	}

	for (int i = 1; i <= 4; i++) {
		if (op[i] == 0) continue;
		op[i]--;
		v.push_back(i);
		dfs(index + 1);
		v.pop_back();
		op[i]++;
	}

}
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= 4; i++) {
		cin >> op[i];
	}
	v.push_back(-1); // 인덱스 1로 시작하기 위함
	dfs(1);
	printf("%d\n%d", MAX, MIN);
	return 0;
}
