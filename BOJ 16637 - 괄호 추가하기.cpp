/*
	BOJ - 17070 파이프 옮기기 1 (*) 19-08-05
	간단했다..
*/
#include <iostream>
#include <algorithm>

using namespace std;

int n;
int a[17][17];
int cnt;
void dfs(int row, int col, int d) { // d = 1 가로, 2 대각, 3 세로

	if (row == n && col == n) {
		cnt++;
		return;
	}
	if (d == 1) {
		if (col != n && a[row][col+1] == 0) dfs(row, col + 1, 1);
		if (row != n && col != n && a[row + 1][col + 1] == 0 && a[row + 1][col] == 0 && a[row][col + 1] == 0) dfs(row + 1, col + 1, 2);
	}
	else if (d == 2) {
		if (col != n && a[row][col + 1] == 0) dfs(row, col + 1, 1);
		if (col != n && row != n && a[row + 1][col + 1] == 0 && a[row+1][col] == 0 && a[row][col+1] == 0) dfs(row + 1, col + 1, 2);
		if (row != n && a[row + 1][col] == 0) dfs(row + 1, col, 3);
	}
	else if (d == 3) {
		if (col != n && row != n && a[row + 1][col + 1] == 0 && a[row + 1][col] == 0 && a[row][col + 1] == 0) dfs(row + 1, col + 1, 2);
		if (row != n && a[row + 1][col] == 0) dfs(row + 1, col, 3);
	}
}
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	dfs(1, 2, 1);

	printf("%d", cnt);
	return 0;
}
