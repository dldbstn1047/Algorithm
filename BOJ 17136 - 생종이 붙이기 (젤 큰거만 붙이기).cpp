/*
	BOJ 17136 - 생종이 붙이기  (*****)  19-08-05
	5*5가 들어간다고 무작정 5만 넣어보면 틀린다
	만약 6X6이 있다고 치면 이 코드에서는 5X5색종이를 넣고 나머지를 못채워서 -1(불가능)이 리턴된다.
	하지만 6X6은 3X3 4개로 충분히 채울 수 있다.
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define N 10

int a[11][11];
int paper[6]; //색종이 갯수
void my_print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%2d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
bool ok() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (a[i][j] == 1) return 0;
		}
	}
	return 1;
}
bool check(int row, int col, int len) { // 색종이 전체가 1인지 확인
	int tmp[11][11];
	memcpy(tmp, a, sizeof(a));
	for (int i = row, cnt1 = len; cnt1 >= 1; i--, cnt1--) {
		for (int j = col, cnt2 = len; cnt2 >= 1; j--, cnt2--) {
			if (tmp[i][j] == 1) {
				tmp[i][j] = 0;
			}
			else {
				return false;
			}
		}
	}
	memcpy(a, tmp, sizeof(a));
	return true;
}
int col_jump(int row, int col, int len) {//점프
	int cnt = len;
	for (int j = col; cnt > 0; j--, cnt--) {
		if (a[row][j] == 0) break;
	}
	return cnt;
}
void search(int len) { //색종이 길이를 인자로 받아서 해당 길이 색종이 탐색
	for (int row = len; row <= N; row++) {
		for (int col = len; col <= N;) {
			int c = col_jump(row, col, len);//점프 수를 알려줌 더해야 하는지 알려줌
			if (c == 0) { //col은 채워짐
				if (check(row, col, len)) {//전부다 채워지면
					if (--paper[len] == 0) return;
					col += len;
				}
				else {
					col++;
				}
			}
			else {
				col += c;
			}
		}
	}
}
int main(void) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= 5; i++) {
		paper[i] = 5;
	}
	int ret = 25;
	for (int len = 5; len > 0; len--) {
		search(len);
	}

	if (!ok())
		ret = -1;
	else
		for (int i = 1; i <= 5; i++) {
			printf("%d ", paper[i]);
			ret -= paper[i];
		}
	printf("\n");

	printf("%d", ret);
	return 0;
}
