#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct _p { //pair로 하고 out거리에서 +1한것을 넣어도 해결된다 아무거나 OK
	int y;
	int x;
	int d;
}p;

#define INF (int)2e9
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };

int a[51][51];
int check[51][51];
int n, m;
int MIN = INF;
queue<p> q;
vector<pair<int, int>> virus, selected;
void bfs() {
	p s, in, out;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			check[i][j] = -1;
		}
	}
	// check배열은 bfs할때 virus로 부터 거리를 저장해두는 곳이다.
	// 0으로 초기화 하게 되면 거리 0 으로 virus시작 지점과 햇갈리게 되기 떄문에
	// -1로 초기화해서 사용하도록 한다.
	// *********** 나는 그냥 a배열에서 해결하려고 했었기 떄문에 bfs()거리 계산할때 많이 애먹었다.********** //
	for (int i = 0; i < selected.size(); i++) {
		s.y = selected[i].first;
		s.x = selected[i].second;
		s.d = 0;
		q.push(s);
		check[s.y][s.x] = s.d;
	}
	//********** BFS할때 시작지점이 여러개이면 모두다 q에 넣고 돌려도 모든 지점에서의 최단 거리가 나온다 **********//
	//********** 나는 for문으로 bfs를 시작 지점만큼 계속 하려고 하였다. 배워간다. **********//
	while (!q.empty()) {
		out = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			in = out;
			in.y += dy[d];
			in.x += dx[d];
			in.d++;
			if (0 < in.y && in.y <= n && 0 < in.x && in.x <= n) {
				if (a[in.y][in.x] != 1 && check[in.y][in.x] == -1) {
					check[in.y][in.x] = in.d;
					q.push(in);
				}
			}
		}
	}
	int MAX = 0;
	bool ok = true;
	for (int i = 1; i <= n && ok; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j] == 0) { //바이러스가 있는 지점은 비활성화 상태여도 바이러스가 있기 때문에
				if (check[i][j] == -1) {//MAX 거리를 계산할때 계산에 넣지 않고 0인 빈칸만 계산 한다.
					ok = false;
					break;
				}
				MAX = max(check[i][j], MAX);
			}
		}
	}

	if (ok) MIN = min(MAX, MIN);
}
void dfs(int index) {
	/*
	//********** if (index >= virus.size()) return;   : 실수한 부분
	dfs종료문이 먼저 오게 된다면 virus갯수와 virus를 선택하는 갯수가 같은 경우
	virus를 모두 선택하는 경우에서 bfs()를 실행하지않고 바로 return된다.
	bfs문을 먼저 돌아서 virus를 모두 선택하는 경우도 check를 하고
	dfs종료문을 넣도록 한다.
	*/

	if (selected.size() == m) {
		bfs();
		return;
	}
	if (index >= virus.size()) return; //dfs종료 문을 bfs() 뒤로 옮긴다.
	/* dfs종료문 없이
	for(int i = index + 1; i <= virus.size();i++){
		if(이미선택한 virus) continue;
		virus 선택
		dfs(index + 1);
		virus 선택 해제
	*/
	//위와 같은 경우는시간 초과가 난다.
	//조합의 경우의 수는 똑같을 거라고 생각 하는데 왜 시간 초과가 날까.

	selected.push_back(virus[index]);
	dfs(index + 1);
	selected.pop_back();

	dfs(index + 1);
}
int main(void) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] == 2)
				virus.push_back(make_pair(i, j));
		}
	}

	dfs(0);
	if (MIN == INF) MIN = -1;
	printf("%d", MIN);
	return 0;
}
