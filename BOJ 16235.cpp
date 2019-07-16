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
vector<int> die[11][11];
int map[11][11];
void tree_sort() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (tree[i][j].size() == 0) continue;
			sort(tree[i][j].begin(), tree[i][j].end());
		}
	}
}
void winter() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] += a[i][j];
		}
	}
}
void fall() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (tree[i][j].size() == 0) continue;
			for (int k = 0; k < tree[i][j].size(); k++) {
				if (tree[i][j][k] % 5 == 0) {
					printf("new\n");
					int ny, nx;
					for (int d = 0; d < 8; d++) {
						ny = i; nx = j;
						ny += dy[d];
						nx += dx[d];
						if (0 < ny && ny <= n && 0 < nx && nx <= n) {
							tree[ny][nx].push_back(1);
						}
					}
				}
			}
		}
	}
}
void summer() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++){
			if (die[i][j].size() == 0) continue;
			for (int k = 0; k < die[i][j].size(); k++) {
				map[i][j] += (die[i][j][k] / 2);
			}
		}
	}
}
void spring() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			die[i][j].clear();
			if (tree[i][j].size() == 0) continue;
			int index = 0;
			vector<int> tmp;
			for (int k = 0; k < tree[i][j].size(); k++) {
				map[i][j] -= tree[i][j][k];
				if (map[i][j] < 0) {
					map[i][j] += tree[i][j][k];
					break;
				}
				tmp.push_back(tree[i][j][k] + 1);
			}
			tree[i][j] = tmp;
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
			printf("%3d", tree[i][j].size());
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


	for (int i = 1; i <= k; i++) {
		printf("1\n");
		tree_sort();
		spring();
		printf("2\n");
		my_print();
		summer();
		printf("3\n");
		my_print();
		fall();
		printf("4\n");
		my_print();
		winter();
		printf("5\n");
		my_print();
		printf("\n\n");
	}
	printf("%d", ret());

	return 0;
}
