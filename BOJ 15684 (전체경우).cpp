#include <iostream>
#include <algorithm>

using namespace std;

#define INF (int)2e9
int n, m, h; //n 가로 , h 세로
int a[31][11];
int MIN = INF;
bool down() { //사다리 내리기
	for (int col = 1; col <= n; col++) {
		int x = col;
		for (int row = 1; row <= h; row++) {
			if (x != 1 && a[row][x - 1] == 1) {
				x--;
				continue; //********** 가로줄을 만나 이동했으면 continue를 해서 다음 칸으로 이동 해야댐
			}
			if (x != n && a[row][x] == 1) {
				x++;
				continue;
			}
		}
		if (col != x) return false;
	}
	return true;
}
void dfs(int cnt, int r) {
	if (cnt >= MIN) return;
	if (down()) MIN = min(MIN, cnt);
	if (cnt >= 3) return; //********** cnt >= 3 인 경우에는 for문을 돌아서 cnt->4 로 될 이유가 없다 바로 잘라준다.**********//

	for (int row = r; row <= h; row++) {//int row = r; 이거 작업 필수 안하면 시간초과
		for (int col = 1; col <= n; col++) {
			if (a[row][col] == 0 && a[row][max(col - 1, 1)] == 0 && a[row][min(col + 1, n)] == 0) {
				a[row][col] = 1;
				dfs(cnt + 1, row);
				a[row][col] = 0;
			}
		}
	}
}
int main(void) {
	cin >> n >> m >> h;
	int x, y;
	for (int i = 1; i <= m; i++) {
		cin >> y >> x;
		a[y][x] = 1;
	}
	dfs(0, 1);

	if (MIN == INF) MIN = -1;
	printf("%d", MIN);
	return 0;
}
