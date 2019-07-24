/*
	BOJ 14890 - 경사로 (***)
	*************************************************************************************
	시뮬레이션 문제이다. 문제를 잘 읽고 흐름을 생각하며 문제에서 주어진 조건을 정리한다.
	* same_high : 연속된 같은 높이의 갯수를 가지고 있는다.
	* working : 한칸 내려간경우, 경사로를 놓아야 하므로 경사로를 놓는 작업중임을 나타낸다.
	*	working 이 l 크기만큼 커지지 못한다면 경사로를 놓을 수 없다.
	1. 같은 칸을 세면서 이동한다.
	2. 높은 칸을 만나면 same_high가 l보다 크거나 같은지 확인하고, 크다면 다시 1로 초기화하고 쭉 이동
	3. 낮은 칸을 만나면 working 변수를 증가시켜 경사로를 놓는 중임을 나타낸다 (same_high는 0으로 바꾼다)
		경사로를 다 놓을떄까지는 same_high를 0으로 유지하고 working을 증가시킨다. 그래야 경사로를 중복해서
		같이 놓는 경우를 제거 할 수 있다.
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <math.h>

using namespace std;

int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };

int a[101][101];
int n, l;
void turn() {// 왼쪽에서 오른쪽으로만 확인 하기 때문에 배열을 90도 돌려서 한번더 확인
	int tmp[101][101];
	memcpy(tmp, a, sizeof(a));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[n - j + 1][i] = tmp[i][j];
		}
	}
}
int sol() {
	bool ok ;
	int cnt = 0;//성공 횟수
	for (int row = 1; row <= n; row++) {
		ok = 1;
		int same_high = 1; //연속적으로 같은 높이 갯수
		int working = 0; //낮은 곳을 만났을때 경사로 두기
		for (int col = 2; col <= n && ok; col++) {
			if (working > 0) { //한칸 내려갔기 때문에 경사로를 놓는 작업중이다.
				if (a[row][col] == a[row][col - 1]) {
					working++; //경사로를 놓는 작업 중에는 same_high는 변하지않는다 working만 변경
				}
				else { //경사로를 놓는도중 높이가 변함
					ok = 0;
				}
			}
			else { //경사로 놓는 작업중이 아님.
				if (a[row][col] == a[row][col - 1]) {
					same_high++;
				}
				else if (a[row][col] == a[row][col - 1] + 1) { //한칸 높아지는 경우
					if (same_high >= l) {// 연속된 높이가 l 보다 길었으므로 경사로를 놓을 수 있다.
						same_high = 1;
					}
					else {
						ok = 0;
					}
				}
				else if (a[row][col] == a[row][col - 1] - 1) { //한칸 낮아지는 경우 (경사로를 이제 놔야한다)
					working = 1; //경사로를 하나 놓는다.
					same_high = 0; //경사로를 놓는 중이기 떄문에 중복 경사로를 놓을수 없도록 0으로 만든다.
				}
				else { //높이가 2이상 차이
					ok = 0;
				}
			}
			//l만큼 경사로를 놓았다면 더이상 경사로를 놓지 않으므로 working 을 0으로 만든다.
			if (working == l) working = 0;
		}
		if (ok && working == 0) {
			//printf("row = %d\n", row);
			cnt++;
		}
	}
	return cnt;
}
int main(void) {
	cin >> n >> l;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	int ans = 0;
	ans += sol();
	turn();
	ans += sol();

	printf("%d", ans);

	return 0;
}
