/*
	BOJ 14502 - 연구소 (*)
	bfs와 dfs가 섞긴 문제.
	********** 바이러스가 퍼지지 않은 공간의 갯수를 세기 때문에 입력시 미리 안정역역(0)의 갯수를 새는게 더 좋다.
	********** 벽을 3개 세울것이기 떄문에 안전영역의 갯수를 셋다면 3을 뺀다.
	********** 그리고선 bfs로 확장할때 바이러스가 퍼질때마다 1씩 감소 시킨다.
	64C3 * 64
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

int a[9][9];
int n, m;
int MAX = -1;
int cnt = 0;
vector<pair<int, int>> v;

void bfs() {
	int tmp = cnt;
	int check[9][9] = { 0, };
	queue<pair<int, int>> q;
	pair<int, int> in, out;
	for (int i = 0; i < v.size(); i++) {
		q.push(v[i]);
		check[v[i].first][v[i].second] = 1;
	}

	while(!q.empty()) {
		out = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			in = out;
			in.first += dy[d];
			in.second += dx[d];
			if (0 < in.first && in.first <= n && 0 < in.second && in.second <= m &&
				a[in.first][in.second] == 0 && check[in.first][in.second] == 0 ) {
				q.push(in);
				check[in.first][in.second] = 1;
				tmp--; //안전영역에 바이러스가 퍼질때마다 1씩 감소
			}
		}
	}
	MAX = max(tmp, MAX);//남은 안전영역끼리 계산
}
void dfs(int cnt, int row) {
	if (cnt >= 3) {
		bfs();
		return;
	}

	for (int i = row; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == 1) continue;
			a[i][j] = 1;
			dfs(cnt + 1, i);
			a[i][j] = 0;
		}
	}
}
int main(void) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
			if (a[i][j] == 2) v.push_back(make_pair(i, j));
			if (a[i][j] == 0) cnt++;
		}
	}
	cnt -= 3; //벽을 3개 세울것이기 떄문에 미리 3을 뺀다.
	dfs(0, 1);
	printf("%d", MAX);
	return 0;
}
