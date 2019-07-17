/*
BOJ 16235 - 나무 재테크 (***)
예제 8번이 자꾸 79가 나오다가 어느 순간 85(정답)이 나옴.... Summer연산을 안해주고 있었음,,
이것도 단순 구현이라 어려운 부분은 없었음,,
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int n, m, k;
int a[11][11];
vector<int> tree[11][11];
int map[11][11];
void fall_winter() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] += a[i][j]; //a배열만큼 양분 주기
			if (tree[i][j].size() == 0) continue;
			for (int k = 0; k < tree[i][j].size(); k++) {
				if (tree[i][j][k] % 5 == 0) {
					int ny, nx;
					for (int d = 0; d < 8; d++) {
						ny = i; nx = j;
						ny += dy[d];
						nx += dx[d];
						if (0 < ny && ny <= n && 0 < nx && nx <= n) {
							tree[ny][nx].push_back(1); //8방향 나무 추가
						}
					}
				}
			}
		}
	}
}
void spring_summer() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (tree[i][j].size() == 0) continue;
			vector<int> tmp;//양분먹고 성장하는 나무 임시 저장할 공간
			sort(tree[i][j].begin(), tree[i][j].end()); //크기가 작은 나무부터 정렬
			int k =0;
			for (; k < tree[i][j].size();k++) {
				map[i][j] -= tree[i][j][k];
				if (map[i][j] < 0) { //남은 양분이 음수가 되면 먹지 못하므로 하나 되돌아가서 종료
					map[i][j] += tree[i][j][k];
					break;
				}
				tmp.push_back(tree[i][j][k] + 1);
			}
			for (; k < tree[i][j].size();k++) { //남은 나무들은 다 죽어서 양분이됨.
				map[i][j] += (tree[i][j][k] / 2);
			}
			tree[i][j] = tmp; //양분먹고 성장한 나무배열 복사
		}
	}
}
int ret() {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cnt += tree[i][j].size();
		}
	}
	return cnt;
}
void my_print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%2d",tree[i][j].size());
		}
		printf("\n");
	}
	printf("\n");
}
int main(void) {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			map[i][j] = 5;
		}
	}
	int x, y, z;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y >> z;
		tree[x][y].push_back(z);
	}


	for (int i = 0; i < k; i++) {
		spring_summer();
		fall_winter();
		//my_print();
	}
	printf("%d", ret());
	return 0;
}
