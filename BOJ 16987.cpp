/*
BOJ 16987 - 계란으로 계란치기
DFS문제이다. 아무계란도 치지 않고 continue;로 넘어갔을 경우 dfs()를 새로 들어가지 않아서 틀렸었다.
아무계란도 치지 않을떄에도 다음계란을 들고 다시 다른 계란을 칠 준비를 해야 한다.
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
int MAX ;
pair<int, int > a[9]; //first : 내구도  second : 무게
void my_print() {
	for (int i = 1; i <= n; i++) {
		printf("%4d", a[i]);
	}
	printf("\n");
}
void dfs(int index, int cnt) {
	//my_print();
	if (index > n) {
		MAX = max(MAX, cnt);
		return;
	}
	bool ok = true; //친 계란이있는지 없는지 체크
	for (int i = 1; i <= n; i++) {
		if (i == index) continue; //든 계란을 칠수는 없다.
		if (a[index].first <= 0) {//든 계란의 내구도가 0 보다 작으면 이미 깨진거다.
			dfs(index + 1, cnt); //다음 계란으로 이동
			return;
		}
		if (a[i].first <= 0) continue; //칠 계란의 내구도가 0 이하이면 이미 깨진거다.
		int tmp = 0;
		ok = false; //하나라도 계란을 쳤으면 false /**********
		a[index].first -= a[i].second; // i번째 계란을 친다.
		a[i].first -= a[index].second;

		if (a[index].first <= 0) tmp++; // 든 계란의 내구도가 0 보다 작아지면 깨진거다.
		if (a[i].first <= 0) tmp++; //맞은 계란의 내구도가 0보다 작아지면 깨진거다.

		dfs(index + 1 , cnt + tmp);
		a[index].first += a[i].second; //쳤던 계란 복구
		a[i].first += a[index].second;
	}
	if (ok) dfs(index + 1, cnt); //아무 계란을 치지 않아도 다음 계란을 든다. /**********
}
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].first >> a[i].second;
	}
	dfs(1, 0);
	printf("%d", MAX);
	return 0;
}
