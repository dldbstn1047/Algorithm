/*
	BOJ 17144 - 미세먼지 안녕! (***)
	단순 구현이지만 생각보다 골치아팠다. 사각형으로 1칸씩 이동하는 과정에서 애먹음..
	더 좋은 방법이 없나 생각해 봐야겠다.
	여기도 동시에 미세먼지가 펼쳐지기 떄문에 tmp 배열을 통해 다 퍼트리고 a배열에 적용한다.
*/
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };
int a[51][51];
int tmp[51][51]; //*********** 여기도 동시에 퍼지는거기 떄문에 tmp로 미세먼지를 퍼트리고 a로 옮긴다.
int r, c, t;
pair<int, int> s[2];
void my_print() {
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void up() { //위 미세먼지 기계
	int direction[4] = { 1, 0, 3, 2 };
	int ny = s[0].first - 1, nx = s[0].second;
	int pre_x, pre_y;
	for (int d = 0; d < 4; d++) {
		while (1) {
			pre_y = ny;
			pre_x = nx;
			ny += dy[direction[d]];
			nx += dx[direction[d]];
			a[pre_y][pre_x] = a[ny][nx];
			if (d == 0 && ny == 1) break;
			if (d == 1 && nx == c) break;
			if (d == 2 && ny == s[0].first) break;
			if (d == 3 && nx == 1) break;
		}
	}
	a[ny][nx + 1] = 0;
}
void down() { //아래 미세먼지 기계
	int direction[4] = { 3, 0, 1, 2 };
	int ny = s[1].first + 1, nx = s[1].second;
	int pre_x, pre_y;
	for (int d = 0; d < 4; d++) {
		while (1) {
			pre_y = ny; // 이전 자리
			pre_x = nx;
			ny += dy[direction[d]]; //다음자리
			nx += dx[direction[d]];
			a[pre_y][pre_x] = a[ny][nx];
			if (d == 0 && ny == r) break;
			if (d == 1 && nx == c) break;
			if (d == 2 && ny == s[1].first) break;
			if (d == 3 && nx == 1) break;
		}
	}
	a[ny][nx + 1] = 0;
	/**********
	따로 종료 조건을 둘 필요가 없다 for(d ..) 문을 돌고나면 자동으로 ny nx는 공기청정기 자리로 와있다.
	**********/
}
void mise(int row, int col) { // 미세먼지 펴지기
	int cnt = 0;
	for (int d = 0; d < 4; d++) {
		int ny = row, nx = col;
		ny += dy[d];
		nx += dx[d];
		if (0 < nx && nx <= c && 0 < ny && ny <= r && a[ny][nx] != -1) {
			cnt++;
			tmp[ny][nx] += a[row][col] / 5;
		}
	}
	tmp[row][col] += ( a[row][col] - (a[row][col] / 5) * cnt);
}
int main(void) {
	cin >> r >> c >> t;
	int index = 0;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> a[i][j];
			if (a[i][j] == -1) {
				s[index].first = i;
				s[index].second = j;
				index++;
			}
		}
	}
	for (int i = 1; i <= t; i++) {
		memset(tmp, 0, sizeof(tmp));
		for (int i = 1; i <= r; i++) { //미세 확산
			for (int j = 1; j <= c; j++) {
				if (a > 0) {
					mise(i, j);
				}
			}
		}
		memcpy(a, tmp, sizeof(a));
		up();
		down();
		//my_print();
	}
	int sum = 0;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if(a[i][j] != -1)
				sum += a[i][j];
		}
	}
	printf("%d", sum);
	return 0;
}
