/*
	BOJ 14889 - 스타트와 링크 (*) - 조합수 줄임
	sol()메소드 조합수를 20C2 에서 10C2 * 2로 줄임
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

#define INF (int)2e9

int n;
int a[21][21];
int visit[21];
int MIN = INF;
void sol() {
	int team_a = 0, team_b = 0;
	vector<int> start, link;
	for (int i = 1; i <= n; i++) { //********** vector로 나누어 저장하고 조합을 돌린다.
		if (visit[i] == 0) start.push_back(i);
		else link.push_back(i);
	}

	for (int i = 0; i < start.size() - 1 ; i++) { //********** start와 link의 길이가 같다.
		for (int j = i + 1; j < start.size(); j++) {
			team_a += (a[start[i]][start[j]] + a[start[j]][start[i]]);
			team_b += (a[link[i]][link[j]] + a[link[j]][link[i]]);
		}
	}
	MIN = min(MIN, abs(team_a - team_b));
}
void dfs(int index, int cnt) {
	if (cnt == n / 2) {
		sol();
		return;
	}
	if (index > n) return;
	if (cnt > n / 2) return;

	visit[index] = 1;
	dfs(index + 1, cnt + 1);
	visit[index] = 0;

	dfs(index + 1, cnt);
}
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	dfs(1, 0);
	printf("%d", MIN);
	return 0;
}
