/*
	BOJ 16926 - 배열돌리기1
	숫자를 벡터에 한번에 넣어서 바꾸는 법이 아닌 한칸씩 이동하는 방법이다.
*/
#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
long r;
int a[301][301];
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m >> r;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	//int tmp = (n + m) * 2 - 4;
	//int rotate = r % tmp;
	int rotate = r;
	int MIN = n > m ? m : n;
	MIN /= 2;
	for (int c = 0; c < rotate; c++) { //회전수
		for (int i = 0; i < MIN ; i++) { // 외각부터
			int y = i;
			int x = i;
			int ny = i;
			int nx = i;
			int tmp = a[i][i];
			for (int d = 0; d < 4; d++) {
				int limit = (d % 2 == 0 ? (m - 1) - 2 * i : (n - 1) - 2 * i);
				for (int j = 0;  j < limit ; j++) {
					ny = y + dy[d];
					nx = x + dx[d];
					a[y][x] = a[ny][nx];
					y = ny;
					x = nx;
				}
			}
			a[i + 1][i] = tmp;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << a[i][j] << " ";
		}
		cout << '\n';
	}

	return 0;
}
