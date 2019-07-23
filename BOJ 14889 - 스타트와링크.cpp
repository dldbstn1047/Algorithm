/*
	BOJ 14889 - 스타트와 링크 (*)
	sol()메소드 에서 20C2만큼 돌면서 계산을 한다 하지만 2 * 10C2 로 줄일수 있다.
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define INF (int)2e9

int n;
int a[21][21];
int visit[21];
int MIN = INF;
void sol() {
	int team_a = 0, team_b = 0;
	int ret;
	for (int i = 1; i < n; i++) { //********** 20C2번 반복한다.
		for (int j = i + 1; j <= n; j++) {
			if (visit[i] == 0 && visit[j] == 0) {
				team_a += a[i][j];
				team_a += a[j][i];
				continue;
			}
			if (visit[i] == 1 && visit[j] == 1) {
				team_b += a[i][j];
				team_b += a[j][i];
			}
		}
	}
	ret = team_a - team_b;
	ret = ret > 0 ? ret : (-1)*ret;
	MIN = min(MIN, ret);
}
void dfs(int index, int cnt) {
	if (cnt == n / 2) {
		sol();
		return;
	}
	if (index > n) return;
	//if (cnt > n/2) return;

	visit[index] = 1;
	dfs(index + 1, cnt + 1);
	visit[index] = 0;

	dfs(index + 1, cnt);
}
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	dfs(1, 0);
	printf("%d", MIN);
	return 0;
}
