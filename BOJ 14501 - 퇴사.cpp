/*
	BOJ 14501 - 퇴사 (*)
	dfs로하면 굉장히 간단하다. dp를 한번 알아보자.
*/
#include <iostream>
#include <algorithm>

using namespace std;

int n;
pair<int, int> a[16];
int MAX = -1;
void dfs(int index, int work, int sum) {
	//printf("index = %d   work = %d     sum = %d\n", index, work, sum);
	if (index > n) {
		if(work == 0)
			MAX = max(MAX, sum);
		return;
	}
	if (work == 0)
		dfs(index + 1, a[index].first - 1, sum + a[index].second);

	dfs(index + 1, max(work - 1, 0), sum);
}
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].first >> a[i].second;
	}

	dfs(1, 0, 0);
	printf("%d", MAX);
	return 0;
}
