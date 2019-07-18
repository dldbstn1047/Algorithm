/*
BOJ 15686 - 치킨배달 (*)
거리를 빼면서 최솟값을 구할떄 어디를 기준으로 잡고 거리의 최소를 구할것인지 잘 생각 한다  ********* (중요) **********
집을 기준으로 잡고 최소거리의 치킨집을 찾아야 집이 중복이 되지 않는다. (집은 중복 불가, 치킨집은 중복 가능)
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define INF (int)2e9
int ans = INF;
int n, m;
int a[51][51];
vector<pair<int, int>> ch, home, selected;
int get_distance(pair<int, int> a, pair<int, int> b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}
int sol() {
	int sum = 0;
	int MIN = INF;
	/**********
	집에서 가장 가까운 치킨집을 골라서 치킨 거리를 만드는거기 떄문에 home이 밖 for문 ch가 안 for문이 되어야 한다.
	반대로되면 틀리다. -> 계속 가장 가까운 집만 찾아서 한집만 고정적으로 치킨거리가 계산됨.
	**********/
	for (int i = 0; i < home.size(); i++) { //집을 기준으로
		MIN = INF;
		for (int j = 0; j < selected.size(); j++) { //가장 가까운 치킨집을 찾는다
			MIN = min(get_distance(selected[j], home[i]), MIN);
		}
		sum += MIN;
	}
	/**********
	치킨집을 기준으로 가장 가까운 집을 찾으면 집이 중복이 되므로 계산되지 않는 집이 있다. (집은 중복되면 안된다)
	하지만 집을 기준으로 가장 가까운 치킨집을 찾으면 중복되는 집이 없고 치킨집만 중복이 된다 (치킨집은 중복 가능)
	**********/

	return sum;
}
void dfs(int index) {
	if (m == selected.size()) {
		ans = min(sol(), ans);
		return;
	}
	if (index >= ch.size()) {
		return;
	}

	selected.push_back(ch[index]);
	dfs(index + 1);
	selected.pop_back();

	dfs(index + 1);

}
int main(void) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] == 2) {
				ch.push_back(make_pair(i, j));
			}
			if (a[i][j] == 1) {
				home.push_back(make_pair(i, j));
			}
		}
	}
	dfs(0);
	printf("%d", ans);
	return 0;
}
