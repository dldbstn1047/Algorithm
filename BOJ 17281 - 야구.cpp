/*
	BOJ - 17281 야구  19-08-02
	오바임.. 한번 선수들 순서 배치를 완료 하면 모든 이닝이 같은 순서였다...
	이닝 마다 새롭게 배치 하는줄,,
*/
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

int a[51][10];
int n;
int MAX;
int check[10];
int v[51][10];
void my_print() {
	printf("\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 9; j++) {
			printf("%d ", v[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int sol() {
	int out = 0;
	int sum = 0;
	int ret = 0;
	int bit = 0;
	int i = 1;
	int row = 1;
		for (;row <= n; i = (i == 9) ? 0 : i + 1) {
			if (v[row][i] == 0) {
				out++;
				if (out == 3) {
					row++;
					ret += sum;
					sum = 0;
					out = 0;
					bit = 0;
				}
			}
			else if (v[row][i] == 1) {
				if ((bit & 4) > 0) sum++;
				bit = bit << 1;
				bit += 1;
			}
			else if (v[row][i] == 2) {
				if ((bit & 4) > 0) sum++;
				if ((bit & 2) > 0) sum++;
				bit = bit << 2;
				bit += 2;
			}
			else if (v[row][i] == 3) {
				if ((bit & 4) > 0) sum++;
				if ((bit & 2) > 0) sum++;
				if ((bit & 1) > 0) sum++;
				bit = 4;
			}
			else if (v[row][i] == 4) {
				sum++;
				if ((bit & 4) > 0) sum++;
				if ((bit & 2) > 0) sum++;
				if ((bit & 1) > 0) sum++;
				bit = 0;
			}
	}
		return ret;
}
void dfs(int index) {

	if (index > 9) { //모두 배치 완료
		MAX = max(MAX, sol());
		return;
	}

	if (index == 4) {
		dfs(5);
		return;
	}
	for (int i = 2; i <= 9; i++) {
		if (check[i] == 1) continue;
		check[i] = 1;
		for (int row = 1; row <= n; row++) {
			v[row][index] = a[row][i];
		}
		dfs(index + 1);
		check[i] = 0;
		for (int row = 1; row <= n; row++) {
			v[row][index] = -1;
		}
	}
}
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> a[i][j];
		}
	}
	memset(v, -1, sizeof(v));
	check[1] = 1;
	for (int row = 1; row <= n; row++) {
		v[row][4] = a[row][1];
	}
	dfs(1);

	printf("%d", MAX);
	return 0;
}
