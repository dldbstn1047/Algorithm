/*
	BOJ 14499 주사위 굴리기 (**)
	이것도 역시 시뮬레이션 이므로 근처 인덱스를 이동하는 주사위의 경우 for문을 이용하는것보다 그냥 바로 인덱스로
	연산을 하는 것이 빠르다.
	********** x, y 좌표가 주어지는데 0, 0 부터 주어진다. 나는 1 베이스 방식이므로 1씩 더해줘야 한다.
*/
#include <iostream>
#include <algorithm>

using namespace std;
int dy[5] = { 0, 0, 0, -1, 1 };
int dx[5] = { 0, 1, -1, 0, 0 };
int dice[5][4];
int a[21][21];
int n, m, x, y, k;
void my_print() {
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 4; j++) {
			printf("%2d", dice[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void move(int d) {
	if (d == 1) {//
		dice[2][0] = dice[4][2];
		dice[4][2] = dice[2][3];
		for (int i = 0; i < 3; i++) {
			dice[2][3 - i] = dice[2][2 - i];
		}
	}
	else if (d == 2) {
		for (int i = 0; i < 3; i++) {
			dice[2][i] = dice[2][i + 1];
		}
		dice[2][3] = dice[4][2];
		dice[4][2] = dice[2][0];
	}
	else if (d == 3) {
		for (int i = 0; i < 4; i++) {
			dice[i][2] = dice[i + 1][2];
		}
		dice[4][2] = dice[0][2];
	}
	else if (d == 4) {
		for (int i = 0; i < 4; i++) {
			dice[5 - i][2] = dice[4 - i][2];
		}
		dice[1][2] = dice[5][2];
	}

}
int main(void) {
	cin >> n >> m >> x >> y >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	int d;
	int ny = x+1;
	int nx = y+1;
	for (int i = 1; i <= k; i++) {
		cin >> d;
		ny += dy[d];
		nx += dx[d];
		if (!(0 < ny && ny <= n && 0 < nx && nx <= m)) {
			ny -= dy[d];
			nx -= dx[d];
			continue;
		}
		move(d);
		printf("%d\n", dice[2][2]);
		if (a[ny][nx] == 0) {
			a[ny][nx] = dice[4][2];
		}else {
			dice[4][2] = a[ny][nx];
			a[ny][nx] = 0;
		}
		//my_print();

	}
	return 0;
}
