/*
SS 1949 - 등산로 조성 (**)
문제 조건이좀 난해했다 최고높은 봉우리를 깎으면 그 봉우리가 최고가 아니게 되는건데 그 봉우리를 최고로 잡아야 문제가 풀린다.
등산로의 높이별로 좌표를 저장해서, 1층부터 최고점을 찾으면서 찾아논 데이터를 가지고 1층 2층 3층 .. 차례대로 계산했다.

*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };


int a[9][9];
int check[9][9];
int n, k;
int MAX = -1;
int h_max, h_min;
int original_max;
vector<pair<int, int>> v[22]; //각 index는 층을 나타내고 그 vector에 좌표가 들어있다.
void check_clear() {
	for(int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			check[i][j] = 1; //기본적으로 모두 1칸의 등산로는 가지고 있다.
		}
	}
}
void vector_clear() {
	for (int i = 0; i < 22; i++) {
		v[i].clear();
	}
}
void make_vector() {
	h_max = -1;
	h_min = 21;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j] <= 0) continue;
			v[a[i][j]].push_back(make_pair(i, j));
			h_min = min(h_min, a[i][j]);
			h_max = max(h_max, a[i][j]);
		}
	}
}
void sol() {
	if (v[h_max].size() > 5) return;
	for (int i = h_min; i <= h_max; i++) {
		for (int j = 0; j < v[i].size(); j++) {
			int tmp_max = -1;
			int y = v[i][j].first;
			int x = v[i][j].second;
			for (int d = 0; d < 4; d++) {// 4방향중 가장 긴 등산로를 가지고 있는 장소를 찾는다
				int ny = y, nx = x;
				ny += dy[d];
				nx += dx[d];
				if (0 < ny && ny <= n && 0 < nx && nx <= n && a[y][x] > a[ny][nx]) { //자기보다 낮은 장소로만 등산로 조성 가능
					tmp_max = max(tmp_max, check[ny][nx]);
				}
			}
			if(tmp_max != -1) // 가장 긴 등산로에 저장
				check[y][x] += tmp_max;
			if (i == original_max) { //최고점의 봉우리 일때만 MAX값을 갱신.
				MAX = max(MAX, check[y][x]);
			}
		}
	}
}
int main(void) {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n >> k;
		original_max = -1; //깍아 내리기전 최고 봉우리 높이 저장
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> a[i][j];
				original_max = max(a[i][j], original_max);
			}
		}
		MAX = -1;
		for (int m = 1; m <= k; m++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					check_clear();
					vector_clear();
					a[i][j] -= m;
					make_vector();
					sol();
					a[i][j] += m;
				}
			}
		}
		printf("#%d %d\n", t, MAX);
	}
	return 0;
}
