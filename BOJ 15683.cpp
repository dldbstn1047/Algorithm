/*
	BOJ 15683 - 감시 (**)
	n * m 사이에서 6(벽)을 만날떄 까지 직진해서 check를 1로 바꾸는 함수를 만들어서 CCTV번호마다 활용 함
	1. 기존 a 배열이 아닌 check 배열을 만들어서 a[i][j]가 0(빈공간)인 부분에서만 check[i][j] 가 변하지않은 부분을 찾는다.
	2. cctv를 입력받을떄 좌표를 저장해서 n*m 반복 -> cctv수 로 속도를 줄임
*/
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;
#define INF (int)2e9
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };
typedef struct _p {
	int y;
	int x;
	int num;
}cctv;
int n, m;
int a[9][9];
int check[9][9];//**********  a배열말고 check배열에 감시한 영역 체크
vector<cctv> v, five_v;
int MIN = INF;
void my_print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			printf("%3d", check[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void go(int row, int col, int d) { //d방향으로 직진하면서 check를 채움
	int ny = row, nx = col;
	while (1) {
		ny += dy[d];
		nx += dx[d];
		if (ny <= 0 || ny > n || nx <= 0 || nx > m) return;
		if (a[ny][nx] == 6) return;
		check[ny][nx] = 1;

	}
}
void sol() {//모든 cctv의 감시가 시작되었을떄 사각지대 체크
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == 0 && check[i][j] == 0) cnt++; //a배열이 0인 부분만
		}
	}
	MIN = min(cnt, MIN);
}
void dfs(int index) {
	//my_print();

	if (index >= v.size()) {
		sol();
		return;
	}
	int tmp_check[9][9];
	int row = v[index].y;
	int col = v[index].x;
	int num = v[index].num;
	int next_index = index + 1;
	for (int d = 0; d < 4; d++) {
		memcpy(tmp_check, check, sizeof(check)); //기존 check 배열 임시저장
		if (num == 1) {
			go(row, col, d);
			dfs(next_index);
		}
		else if (num == 2) {
			go(row, col, d);
			go(row, col, (d + 2) % 4);
			dfs(next_index);
		}
		else if (num == 3) {
			go(row, col, d);
			go(row, col, (d + 1) % 4);
			dfs(next_index);
		}
		else if (num == 4) {
			go(row, col, d);
			go(row, col, (d + 1) % 4);
			go(row, col, (d + 2) % 4);
			dfs(next_index);
		}

		memcpy(check, tmp_check, sizeof(check));//check배열 되돌리기
	}
}
int main(void) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
			if(1 <= a[i][j] && a[i][j] < 5)
				v.push_back({ i, j, a[i][j] });
			if (a[i][j] == 5)
				five_v.push_back({ i, j, a[i][j] });
		}
	}
	for (int i = 0; i < five_v.size(); i++) { //CCTV가 5번인 경우 회전할 필요 없다.
		for (int d = 0; d < 4; d++)
			go(five_v[i].y, five_v[i].x, d);
	}
	dfs(0);
	printf("%d", MIN);
	return 0;
}
