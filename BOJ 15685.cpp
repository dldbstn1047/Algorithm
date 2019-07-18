/*
BOJ 15685 - 드래곤 커브
방향들을 저장하고 역순으로 +1 씩하면서 그려가면 된다.
********** 입력으로 (0,0)의 좌표가 주어지고, (0, 0)부터 시작 하는 문제이기 떄문에 ************
********** 조심한다.. 이걸로 틀리면 너무 억울 **********
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef struct _p {
	int x;
	int y;
	int d;
	int g;
}p;
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };
int n;
int a[101][101];
vector<p> start;
vector<int> v;
void sol(int now_g,int max_g, pair<int, int> last) {
	if (now_g == max_g) return;

	for (int i = v.size() - 1; i >= 0; i--) { //마지막 아이부터 역순으로 다시 그려야함
		int nd = (v[i] + 1) % 4; //방향  + 1
		last.first += dy[nd];
		last.second += dx[nd];
		a[last.first][last.second] = 1;
		v.push_back(nd); //그렸으면 그린 방향 다시 저장
	}
	sol(now_g + 1, max_g, last); //마지막 지점 다시 전달

}
int main(void) {
	cin >> n;
	int x, y, d, g;
	for (int i = 1; i <= n; i++) {
		cin >> x >> y >> d >> g;
		start.push_back({ x, y, d, g });
	}
	for (int i = 0; i < start.size(); i++) {
		v.clear();
		//0세대 그리기
		int y = start[i].y;
		int x = start[i].x;
		int d = start[i].d;
		int g = start[i].g;
		a[y][x] = 1;
		y += dy[d];
		x += dx[d];
		a[y][x] = 1;
		v.push_back(d);
		sol(0, g, make_pair(y, x));
	}
	int cnt = 0;
	/********** i = 1, j = 1 하면 틀린다... 너무 억울 할거같은데 이거 **********/
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 100; j++) {
			if (a[i][j] == 1 && a[i + 1][j] == 1 && a[i][j + 1] == 1 && a[i + 1][j + 1] == 1) cnt++;
		}
	}
	printf("%d", cnt);
	return 0;
}
