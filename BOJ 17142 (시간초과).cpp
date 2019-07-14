#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define INF (int)2e9

int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };

int a[51][51];
int check[51][51];
int n, m;
int MIN = INF;
int virus_check[10];
vector<pair<int, int>> virus;
void bfs() {
	pair<int, int> in, out;
	queue<pair<int, int>> q;
	memset(check, -1, sizeof(check));
	for (int i = 0; i < virus.size(); i++) {
		if (virus_check[i] == 1) {
			q.push(virus[i]);
			check[virus[i].first][virus[i].second] = 0;
		}
	}
	while (!q.empty()) {
		out = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			in = out;
			in.first += dy[d];
			in.second += dx[d];
			if (0 < in.first && in.first <= n && 0 < in.second && in.second <= n) {
				if (check[in.first][in.second] == -1 && a[in.first][in.second] != 1) {
					check[in.first][in.second] = check[out.first][out.second] + 1;
					q.push(in);
				}
			}
		}
	}
	int MAX = 0;
	bool ok = true;
	for (int i = 1; i <= n && ok; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j] == 0) {
				if (check[i][j] == -1) {
					ok = false;
					break;
				}
				MAX = max(MAX, check[i][j]);
			}
		}
	}
	if (ok) MIN = min(MAX, MIN);

}
void dfs(int cnt) {
	if (cnt == m) {
		bfs();
		return;
	}

	for (int i = cnt; i < virus.size(); i++) { // 통과 코드랑 다른 부분.
		if (virus_check[i] == 1) continue;
		virus_check[i] = 1;
		dfs(cnt + 1);
		virus_check[i] = 0;
	}

}
int main(void) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] == 2)
				virus.push_back(make_pair(i, j));
		}
	}
	dfs(0);

	if (MIN == INF) MIN = -1;
	printf("%d", MIN);
	return 0;
}
