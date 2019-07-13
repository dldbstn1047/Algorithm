#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct _p {
	int y;
	int x;
	int d;
}p;

#define INF (int)2e9
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };

int a[51][51];
int check[51][51];
int n, m;
int MIN = INF;
queue<p> q;
vector<pair<int, int>> virus, selected;
void bfs() {
	p s, in, out;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			check[i][j] = -1;
		}
	}
	for (int i = 0; i < selected.size(); i++) {
		s.y = selected[i].first;
		s.x = selected[i].second;
		s.d = 0;
		q.push(s);
		check[s.y][s.x] = s.d;
	}
	while (!q.empty()) {
		out = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			in = out;
			in.y += dy[d];
			in.x += dx[d];
			in.d++;
			if (0 < in.y && in.y <= n && 0 < in.x && in.x <= n) {
				if (a[in.y][in.x] != 1 && check[in.y][in.x] == -1) {
					check[in.y][in.x] = in.d;
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
				MAX = max(check[i][j], MAX);
			}
		}
	}

	if (ok) MIN = min(MAX, MIN);
}
void dfs(int index) {
	if (selected.size() == m) {
		bfs();
		return;
	}

	if (index < virus.size()) {
		selected.push_back(virus[index]);
		dfs(index + 1);
		selected.pop_back();

		dfs(index + 1);
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
