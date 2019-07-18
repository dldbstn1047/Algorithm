/*
BOJ 15684 - 사다리 조작 (****)
1번 - 사다리를 최대 1개, 2개, 3개 놓을수 있는 경우를 정해서 검사 (해당코드)
2번 - 사다리 갯수의 상관없이 전체 경우의수 다 검사
결국 1번 2번 전체 경우의수는 같다. 하지만 2번의 경우 컷팅 if(cnt ==3) return 작업을 하지 않아서 cnt가 4일때도
N * H 만큼 for 문이 도는 경우가 발생했다.
********** 코드를 깔끔하게 정리 할라고 하지 말고 제대로 컷팅 작업을 해야 한다.
********** DFS 종료 조건에서 새로 들어와서 바로 나가버리는것 말고 아에 안들어가게 하는 작업을 생각해보자.
*/
#include <iostream>
#include <algorithm>

using namespace std;
#define INF (int)2e9
int n, m, h; //n 가로 , h 세로
int a[31][11];
int MIN = INF;
void my_print() {
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
bool down() { //사다리 내리기
	//printf("in down\n");
	for (int col = 1; col <= n; col++) {
		int x = col;
		for (int row = 1; row <= h; row++) {
			if (x != 1 && a[row][x-1] == 1) {
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
void dfs(int now, int end, int r) {
	/**********
	사다리를 1개, 2개, 3개일때 나눠서 검사한다.
	**********/
	if (now == end) {
		if (down())
			MIN = end;
		return;
	}

	for (int row = r; row <= h; row++) {
		for (int col = 1; col <= n; col++) {
			if (a[row][col] == 0 && a[row][max(col - 1, 1)] == 0 && a[row][min(col + 1, n)] == 0) {
				a[row][col] = 1;
				dfs(now + 1, end, row);
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
	for (int end = 0; end <= 3 && MIN == INF; end++) { //사다리1개일떄, 2개일때, 3개일떄 를 나눠서 검사
		dfs(0, end, 1);
	}

	if (MIN == INF) MIN = -1;
	printf("%d", MIN);
	return 0;
}
