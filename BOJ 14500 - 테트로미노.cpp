/*
	BOJ 14500 - 테트로미노 (**)
	뻐큐모양의 특수한 경우 for문을 도는것 보다 그냥 배열인덱스로 한번에 찍어준다.
	배열의 접근은 가장 빠르게 접근 할수 있으므로 (인접한 메모리) 빠른 속도가 가능.
*/
#include <iostream>
#include <algorithm>

using namespace std;

int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };
int a[501][501];
int visit[501][501];
int n, m;
int MAX = -1;

void func(int row, int col) { //예외경우는 따로 만든다, 모든경우를 이렇게 만들어서 해도 괜찮다.
	if (row != 1 && col != 1 && col != m)
		MAX = max(MAX, a[row][col] + a[row - 1][col] + a[row][col - 1] + a[row][col + 1]);

	if (row != 1 && col != m && row != n)
		MAX = max(MAX, a[row][col] + a[row - 1][col] + a[row + 1][col] + a[row][col + 1]);

	if (row != n && col != 1 && col != m)
		MAX = max(MAX, a[row][col] + a[row + 1][col] + a[row][col + 1] + a[row][col - 1]);

	if (row != 1 && col != 1 && row != n)
		MAX = max(MAX, a[row][col] + a[row - 1][col] + a[row][col - 1] + a[row + 1][col]);
}
void dfs(int cnt, int row, int col, int sum) { //사각형의 경우bfs로 안되므로 dfs로 해야한다.
	if (cnt >= 4) {
		MAX = max(MAX, sum);
		return;
	}

	for (int d = 0; d < 4; d++) {
		int ny = row + dy[d];
		int nx = col + dx[d];
		if (0 < ny && ny <= n && 0 < nx && nx <= m && visit[ny][nx] == 0) {
			visit[ny][nx] = 1;
			dfs(cnt + 1, ny, nx, sum + a[ny][nx]);
			visit[ny][nx] = 0;
		}
	}
}

int main(void) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			visit[i][j] = 1;
			dfs(1, i, j, a[i][j]);
			func(i, j);
			visit[i][j] = 0;
		}
	}
	printf("%d", MAX);
	return 0;
}
