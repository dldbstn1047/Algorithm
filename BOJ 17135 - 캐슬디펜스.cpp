/*
	BOJ 17135 - 캐슬 디펜스  19-08-03
	1. 적들이 아래로 당겨지는거 대신 row를 마지막 n 부터 1씩 깍으면서 궁수의 위치를 이동 시켰다 (적들 움직이는 연산 스킵)
	2. tmp로 임시 저장하는 것과  visit배열을 햇갈려서 틀렸었다..
	3. 공격당한 적을 -row로 바꿔 어느 라운드에 공격을 당했는지 표시한다. (만약 같은 라운드라면 중복 공격으로 처리 )
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

int dy[3] = { 0, -1, 0 };
int dx[3] = { -1, 0, 1 };

int n, m, d;
int a[16][16];
int tmp[16][16];
int visit[16][16];
int MAX;
int e_max; //적의 최대 갯수
vector<int> man;
void my_pinrt() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			printf("%2d", tmp[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int atack(int row) {
	queue<pair<int, int>> q;
	pair<int, int> out, in;
	int cnt = 0;

	for (int i = 0; i < 3; i++) {
		while (!q.empty()) q.pop(); //다음 아쳐 공격할때 큐 비우기
		memset(visit, 0, sizeof(visit));

		q.push(make_pair(row, man[i]));
		visit[row][man[i]] = 1;
		while (!q.empty()) {
			out = q.front();
			q.pop();
			if (tmp[out.first][out.second] == 1 || tmp[out.first][out.second] == -row) { //이번턴에 공격할 애
				//*************************************************************************
				//if (tmp[out.first][out.second] == 1 || tmp[out.first][out.second] < 0) {
				//위와 같이 하면은 이전에 잡힌 애를 잡아도 멈추기 때문에 -row로 주어서 이번에 잡힌 애를 또잡는경우(같은 것을 잡음)
				//에만 공격중 중지하도록 해야 한다.
				if (tmp[out.first][out.second] == 1) { //아직 공격당한 적이 아니라면
					tmp[out.first][out.second] = -row;
					cnt++;
				}
				break; //공격은 1번만 가능 ! 종료
			}
			if (visit[out.first][out.second] == d) continue;
			for (int d = 0; d < 3; d++) {
				in = out;
				in.first += dy[d];
				in.second += dx[d];
				if (0 < in.first && 0 < in.second && in.second <= m && visit[in.first][in.second] == 0) {
					visit[in.first][in.second] = visit[out.first][out.second] + 1;
					q.push(in);
				}
			}
		} // end q while
	}//end for
	/*
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (tmp[i][j] == -row) cnt++; //이번 라운드 공격
		}
	}
	*/
	return cnt;
}
void dfs(int index) {
	if (index > m + 1 || man.size() > 3) return; //왜 m + 1 인가??

	if (man.size() == 3) {
		memcpy(tmp, a, sizeof(a));
		int sum = 0;
		for (int row = n; row > 0; row--) {
			sum += atack(row);
			if (sum == e_max) break;
		}
		//my_pinrt();
		MAX = max(MAX, sum);
		//*********************************************진짜 뭐하는건지 싶었다....
		//memcpy(a, tmp, sizeof(a)); //tmp로 잘했는데 왜 a에다가 tmp를 복사해 ㅡㅡ 하
		return;
	}

	man.push_back(index);
	dfs(index + 1);
	man.pop_back();

	dfs(index + 1);

}
int main(void) {
	cin >> n >> m >> d;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
			if (a[i][j] == 1) e_max++;
		}
	}

	dfs(1);
	printf("%d", MAX);
	return 0;
}
