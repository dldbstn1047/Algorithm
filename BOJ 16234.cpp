/*
BOJ 16234 인구이동 (***)
1. N <=50 인 N * N공간을 1차원 배열로 바꿔서 저장할때 배열 크기를 N * N 을 줘야하는데 N만큼 주어서 계속 틀렸었다...
2. 마지막 인구 이동 작업을 할떄 나라가 1개인 곳은 인구이동을 하지 않고 그냥 넘어가는 컷팅이 없으면 시간초과
3. 인접한 나라들끼리 연결해서 인구이동을 하는 아이디어는 BFS를 사용
*/
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;
int dy[4] = { 1, -1, 0, 0 };
int dx[4] = { 0, 0, 1, -1 };

int n, l, r;
int a[51][51];
void my_print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%4d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int sol() {
	pair<int, int> in, out;
	//vector<pair<int, int>> v[51 * 51 + 1];
	queue<pair<int, int>> q;
	int visit[51][51] = { 0, };
	int number = 0;
	int cnt[51*51 + 1] = { 0, }; //********** N이 최대 50 이므로 51*51 + 1만큼 줘야 한다. (나는 50밖에 안줬었음..) ************
	int sum[51*51 + 1] = { 0, };
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (visit[i][j] == 0) {
				number++;
				q.push(make_pair(i, j));
				visit[i][j] = number;
				cnt[number]++;
				sum[number] += a[i][j];
				//v[number].push_back(make_pair(i, j));
				while (!q.empty()) {
					out = q.front();
					q.pop();
					for (int d = 0; d < 4; d++) {
						in = out;
						in.first += dy[d];
						in.second += dx[d];
						if (0 < in.first && in.first <= n && 0 < in.second && in.second <= n && visit[in.first][in.second] == 0 &&
							l <= abs(a[in.first][in.second] - a[out.first][out.second]) && abs(a[in.first][in.second] - a[out.first][out.second]) <= r) {
							cnt[number]++;
							sum[number] += a[in.first][in.second];
							//v[number].push_back(make_pair(in.first, in.second));
							q.push(in);
							visit[in.first][in.second] = number;
						}
					}
				}
			}
		}
	}
	/***********
	통과되긴 하지만 n^2을 돌아서 자기 땅을 찾아야 하므로 오래 걸린다.
	vector에 해당 땅들을 저장 해두고 하는 방식으로 변경했지만 이게 더 빠름,
	vector에 저장하면 나라가 1개여도 백터에 넣고 찾는 작업이 있지만,
	for문으로 찾아서 컷팅을 하면 나라가 1개인 경우에는 아무 작업도 하지 않고
	넘어가기 때문에 더 빠르다.
	***********/
	for (int k = 1; k <= number; k++) {
		if (cnt[k] == 1) continue; //************************** 컷팅 작업 안하면 시간 초과.*******************
		int people = sum[k] / cnt[k];
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (visit[i][j] == k) {
					a[i][j] = people;
				}
			}
		}
	}

	/*
	for (int k = 1; k <= number; k++) { //********** 미리 좌표를 저장하고 인구를 이동시켰지만, 오히려 느려짐,,.
		int people = sum[k] / cnt[k];
		for (int i = 0; i < v[k].size(); i++) {
			a[v[k][i].first][v[k][i].second] = people;
		}
	}
	*/

	//printf("number = %d\n", number);
	//my_print();
	return number;
}
int main(void) {
	cin >> n >> l >> r;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	int cnt = 0;
	while ((n*n) != sol())
		cnt++;
	printf("%d", cnt);
	return 0;
}
