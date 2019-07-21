/*
SS 2105 - 디저트 카페 (****)
굉장히 짜증나는 시뮬레이션 문제였다. 시간복잡도에 대한 고민이 너무 많았었음
좀 생각할거 많은 시뮬레이션 연습으로 좋았다.
1. MAX값을 계산하는 곳에서 B(1)로 맥스가 안나올거같으면 바로 컷팅
2. dfs로 들어온 값을 이번의 방문할 카페로 정하고 다음 방문할것을 파라미터로 전달하여 다음 dfs 호출
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

int dy[5] = { 0, 1, 1, -1, -1 };
int dx[5] = { 0, 1, -1, -1, 1 };
using namespace std;

#define INF (int) 2e9

int a[21][21];
int desert[101];
int n;
int MAX = -INF;
void sol(int row, int col, int one_cnt, int two_cnt) {//3, 4 방향으로 움직이며 다시 출발점으로 돌아가는 함수
	if (MAX >= (one_cnt + two_cnt)  + (one_cnt + two_cnt - 2)) return; //********** 바로 컷팅
	if (one_cnt == 1) return;
	int tmp_desert[101];
	memcpy(tmp_desert, desert, sizeof(desert));
	int ny = row, nx = col;
	int cnt[2] = { one_cnt - 1, two_cnt -1 };
	int d[2] = { 3, 4 };
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= cnt[i]; j++) {
			ny += dy[d[i]];
			nx += dx[d[i]];
			if (!(0 < ny && ny <= n && 0 < nx && nx <= n)) return;
			if (tmp_desert[a[ny][nx]] == 1) return;
			tmp_desert[a[ny][nx]] = 1;
		}
	}
	MAX = (one_cnt + two_cnt) + (one_cnt + two_cnt - 2);
}
void dfs(int row, int col, int one_cnt, int two_cnt, int direction) {

	if (desert[a[row][col]] == 1) return;//들어온 값을 이번 방문좌표로 정한다.
	desert[a[row][col]] = 1;
	if (direction == 1) {
		int d[2] = { 1,2 };
		for (int i = 0; i < 2; i++) {
			int ny = row, nx = col;
			ny += dy[d[i]]; //다음 들어갈 좌표를 파라미터로 보낸다.
			nx += dx[d[i]];
			if (0 < ny && ny <= n && 0 < nx && nx <= n) {
				dfs(ny, nx, one_cnt + 1, two_cnt, d[i]);
			}
		}
	}
	if (direction == 2) {
		int ny = row, nx = col;
		ny += dy[2];
		nx += dx[2];
		if (0 < ny && ny <= n && 0 < nx && nx <= n)
			dfs(ny, nx, one_cnt, two_cnt + 1, 2);
		sol(row, col, one_cnt, two_cnt + 1); //방향이 2이면 2방향으로 한번더가는것과 MAX값 계산 둘다 한다.
	}
	desert[a[row][col]] = 0;
}
int main(void) {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		//memset(desert, 0, sizeof(desert)); //desert배열은 dfs가 리턴하면서 다시 0 으로 만들기 때문에 초기화 필요 X
		//memset(a, 0, sizeof(a)); //a 배열은 덮어씌어지기 떄문에 초기화 필요 X
		MAX = -INF;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> a[i][j];
			}
		}

		for (int i = 1; i < n; i++) {
			for (int j = 1; j <= n; j++) {
				dfs(i, j, 0, 0, 1);
			}
		}
		if (MAX == -INF) MAX = -1;
		printf("#%d %d\n", t, MAX);
	}
	return 0;
}
