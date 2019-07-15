/*
 단순구현 문제 (**)
 같은 범위를 반복해서 움직이는 물고기가 일정 기준 마다 자기자기로 돌아온다는 것만
 눈치 채고 %연산으로 움직이는 과정을 줄여준다면 문제없이 해결 가능.
 **구조체에 대입을 할때 {} 로 순서를 맞추면 한번에 대입이 가능하다.
 **상어가 같은 자리에 오면 큰애가 잡아먹으므로 바로 a배열에 상어를 이동하는것이 아니라
 **임시 배열을 만들어서 다 이동한 후 a에 복사한다.
 **아직 움직이지 않은 상어가 미리 먹혀버릴수도 있기 떄문에 (상어는 동시에 움직인다)
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;

typedef struct _p {
	int s;
	int d;
	int z;
}p;
int dy[5] = { 0, -1, 1, 0, 0 }; //위1 아래2 오른쪽3 왼쪽4
int dx[5] = { 0, 0, 0, 1, -1 };
p a[101][101];
p tmp[101][101]; //********** 상어는 동시에 움직 이기때문에, 먼저 움직인 상어가
int ans;		//********** 아직 움직이지 않은 기존 상어는 잡아먹지않도록 움직인 상어는
int R, C, M;	//********** tmp 배열에 저장하고 모든 상어가 다 움직인 이후 a에 복사
void my_print() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			printf("%2d", a[i][j].z);
		}
		printf("\n");
	}
	printf("\n");

}
void fish_move(int row, int col) {
	int r = row, c = col;
	int d = a[row][col].d;
	int z = a[row][col].z;
	int s = a[row][col].s;
	int distance;

	/**********
	같은 공간을 계속 반복 하기 떄문에 일정 수 마다 자기 자리로 온다
	예를 들어 6칸 이면 10의 배수로 계속 같은 자리에온다
	s값 만큼 전부 이동할 필요 없이 %연산을 통해 조금만 이동하면 된다.
	**********/
	if (d == 1 || d == 2)
		distance = s % ((R - 1) * 2); //이동거리 줄이기 (반복구간 컷팅)
	else if (d == 3 || d == 4)
		distance = s % ((C - 1) * 2);

	while (distance-- > 0) {
		if (d == 1 && r == 1) d = 2; //뒤돌기
		if (d == 2 && r == R) d = 1;
		if (d == 3 && c == C) d = 4;
		if (d == 4 && c == 1) d = 3;
		r += dy[d];
		c += dx[d];
	}
	if (tmp[r][c].z < z) {
		tmp[r][c] = { s, d, z };
	}

}
void fish_search() {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (a[i][j].z > 0) {
				fish_move(i, j);
			}
		}
	}
	memcpy(a, tmp, sizeof(a));
}
void chatch(int col) {
	for (int row = 1; row <= R; row++) {
		if (a[row][col].z > 0) {//상어 있음
			ans += a[row][col].z;
			a[row][col] = { 0, 0, 0 };
			break; //한마리만 잡는다.
		}
	}
}
void man_move() {
	for (int col = 1; col <= C; col++) {
		chatch(col);
		fish_search();
	}
}
int main(void) {
	cin >> R >> C >> M;
	int r, c, s, d, z; // s = 속력 , d = 방향 , z = 크기
	for (int i = 1; i <= M; i++) {
		cin >> r >> c >> s >> d >> z;
		a[r][c] = { s, d, z };
	}

	man_move();
	printf("%d", ans);
	return 0;
}
