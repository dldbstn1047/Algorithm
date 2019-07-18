/*
BOJ 15686 - 치킨배달 (*)
치킨집에서 집까지 거리는 계산할 때 BFS를 사용 했지만, BFS를 사용하지않고 집위치를 기억해둔다음에 거리를 계산하는 식으로
속도를 개선할 수 있다. -> 치킨배달 (속도개선).cpp
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>


using namespace std;

int dy[4] = { 1, -1, 0, 0 };
int dx[4] = { 0, 0, 1, -1 };

#define INF (int)2e9
int MIN = INF;
int n, m;
int a[51][51];
vector<pair<int, int>> v;
vector<pair<int, int>> selected;
int get_distance(pair<int, int> a, pair<int, int> b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}
int bfs() {
	int sum = 0;
	pair<int, int > in, out;
	queue<pair<int, int>> q;
	int visit[51][51];
	memset(visit, -1, sizeof(visit));


	for (int i = 0; i < selected.size(); i++) {
		q.push(selected[i]);
		visit[selected[i].first][selected[i].second] = 0;
	}
	while (!q.empty()) {
		out = q.front();
		q.pop();
		if (a[out.first][out.second] == 1) {
			sum += visit[out.first][out.second];
		}
		for (int d = 0; d < 4; d++) {
			in = out;
			in.first += dy[d];
			in.second += dx[d];
			if (0 < in.first && in.first <= n && 0 < in.second && in.second <= n) {
				if (visit[in.first][in.second] == -1) {
					visit[in.first][in.second] = visit[out.first][out.second] + 1;
					q.push(in);
				}
			}
		}
	}

	return sum;
}
void dfs(int index) {
	if (m == selected.size()) {
		MIN = min(bfs(), MIN);
		return;
	}
	if (index >= v.size()) {
		return;
	}

	selected.push_back(v[index]);
	dfs(index + 1);
	selected.pop_back();

	dfs(index + 1);

}
int main(void) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] == 2) {
				v.push_back(make_pair(i, j));
			}
		}
	}
	dfs(0);
	printf("%d", MIN);
	return 0;
}
