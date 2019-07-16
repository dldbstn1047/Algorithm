/*
BOJ 16236 - 아기상어 (**)
가장 가까운 물고기를 먹는 문제인데 (위 왼 오 아래) 순으로 BFS돌다가 가장 먼저 만나느 물고기는 먹으면 틀린다!!!
최단거리로 먹을수 있는 물고기를 모두 표시한 후 for문 돌면서 가장 위면서 왼쪽에 있는 물고기를 찾아야 한다.
distance변수를 두고 가장 먼저 먹게되는 물기기와의 거리를 저장한다. 그리고 그 다음부터 distance보다
먼 거리에 있는 물고기는 무시 하는 방법은 맨뒤에 추가 코드
*/
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

#define INf (int)2e9
using namespace std;

int dy[4] = { -1, 0, 0, 1 };
int dx[4] = { 0, -1, 1, 0 };

int eating_cnt;
int shark_size = 2;
int cnt;
pair<int, int> shark;
int a[21][21];
int visit[21][21];
int n;
void my_print() {
	printf("%d\n", cnt);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
bool bfs() {
	//my_print();
	pair<int, int> in, out;
	queue<pair<int, int>> q;
	memset(visit, -1, sizeof(visit));
	q.push(shark);
	visit[shark.first][shark.second] = 0;
	int eat[21][21] = { 0, };
	int MIN = 987654321;
	while (!q.empty()) {
		out = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			in = out;
			in.first += dy[d];
			in.second += dx[d];
			if (0 < in.first && in.first <= n && 0 < in.second && in.second <= n) {
				if (visit[in.first][in.second] == -1 && a[in.first][in.second] <= shark_size) {
					visit[in.first][in.second] = visit[out.first][out.second] + 1;
					q.push(in);
					if (0 < a[in.first][in.second] && a[in.first][in.second] < shark_size) {//먹는다.
						eat[in.first][in.second] = visit[in.first][in.second];
						MIN = min(MIN, eat[in.first][in.second]); //가장 가까이 있는 물고기와의 거리 저장
					}
				}
			}
		}
	}
	/**********
	같은 거리라면 맨위, 위가 같다면 왼쪽의 조건으로 인해 dy, dx 배열을 (위 왼 오 아래) 순으로 배치하였지만,
	해당대로 바로 bfs를 통해 가장 먼저 만나는 애를 먹어버리면 특정 케이스에서 틀리게 나온다 (이유는 모르곘다..)
	그래서 따로 배열에 가장 최단거리로 먹을수 있는 물고기들을 모두 표시하고 2중 for문으로 검사를 해야 정확하게 풀린다.
	**********/
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (eat[i][j] == MIN) { //최단거리인 물고기중에 오른쪽 위에 있는애 고르기
				cnt += MIN;
				eating_cnt++;
				if (eating_cnt == shark_size) {
					shark_size++;
					eating_cnt = 0;
				}
				a[i][j] = 0;
				shark.first = i;
				shark.second = j;
				return true;
			}
		}
	}
	return false; //bfs를 전부 돌아도 먹은 물고기가 없으면 종료
}
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] == 9) {
				shark.first = i;
				shark.second = j;
				a[i][j] = 0;
			}
		}
	}
	while (bfs());
	printf("%d", cnt);
	return 0;
}
/*
p in, out;
	queue<p> q;
	int visit[N + 1][N + 1] = { 0, };
	int can[N + 1][N + 1] = { 0, };
	int distance = 10000; //일단 10000으로 둔다.

	q.push(s);
	visit[s.y][s.x] = 1;
	while(!q.empty()){
		out = q.front();
		q.pop();
		for (int d = 0; d < 4; d++){
			in = out;
			in.y += dy[d];
			in.x += dx[d];
			in.d++;
			if (0 < in.y && in.y <= n && 0 < in.x && in.x <= n && visit[in.y][in.x] == 0 &&
				a[in.y][in.x] <= size && in.d <= distance){ //최단거리로 업데이트된 distance보다 큰 거리(d)는 무시
				if (0 < a[in.y][in.x] && a[in.y][in.x] < size){
					distance = in.d; //BFS이기 떄문에 가장 먼저 먹은애와의 거리 (d)가 최단 거리이다.
					can[in.y][in.x] = in.d;
				}
				q.push(in);
				visit[in.y][in.x] = 1;
			}
		}
	}
*/
