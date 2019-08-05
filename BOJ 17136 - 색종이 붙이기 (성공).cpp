/*
	BOJ - 17136 색종이 붙이기 (*****)
	1.index++을 통해서 dfs() 안에 2중 포문 없애기
	2. 어떤 칸을 덮는 문제의 경우 6X6 이라고치면 5X5를 바로 덮는게 아니다. 3X3 4개로 꽉 채워 덮을 수 있다.
	결국 모든 색종이를 다 한번씩 덮고 넘어가야 한다.

	https://baelanche.tistory.com/176 - 참고 사이트
*/
#include <algorithm>
#include <iostream>
#include <memory.h>

using namespace std;
#define N 10

int paper[6];
int a[11][11];
int total;
int MIN = 987654321;
void my_print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%2d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int check(int row, int col, int len) { //색종이를 덮을 수있으면 len*len 출력 아니면 0 출력
	int tmp[11][11];
	memcpy(tmp, a, sizeof(a));
	for (int i = row, cnt1 = 1; cnt1 <= len; i++, cnt1++) {
		for (int j = col, cnt2 = 1; cnt2 <= len; j++, cnt2++) {
			if (a[i][j] == 0) return 0;
			else if(a[i][j] == 1){
				tmp[i][j] = 0;
			}
		}
	}
	memcpy(a, tmp, sizeof(a));
	return len * len;
}
void dfs(int index, int paper_cnt) { //색종이 길이를 인자로 받아서 해당 길이 색종이 탐색

	if (index >= 100) {
		MIN = min(paper_cnt, MIN);
		return;
	}
	if (paper_cnt >= MIN) //********* 5X5 자리에 5x5를 넣어서 완성을 시켰다면 그 다음에 더 작은 색종이를 안 넣어봐도 되도록 함
		return;
	int i = index / 10 + 1; //********** dfs안에 for문은 없애도록 하자.. 너무 많이 도는 경우가 많다.
	int j = index % 10 + 1; //**********
			if (a[i][j] == 1) { /******************************
				index가 지나간 자리에는 0은 없다 , 1을 다 잡아서 0 으로 만든다.
				len이 1로 되어서 해당 자리를 0 으로 만들고 dfs를 들어간다. 그리고 만약 완성이 되질 않고 나오면,
				해당 자리가 1이 다시 복원되고 그 뒤로 넘어가서 dfs를 다시 호출하는 부분이 없다.
				더이상 들어가지 않는다.
				********************************************/
				for (int len = 5; len > 0; len--) { //5x5 크기 부터 놓아본다.
					if ((i + len - 1) > N || (j + len - 1) > N) continue;
					if (paper[len] == 0) continue;
					int tmp[11][11];
					memcpy(tmp, a, sizeof(a));
					if (check(i, j, len)) {
						paper[len]--;
						dfs(index + len, paper_cnt + 1);
						memcpy(a, tmp, sizeof(a));
						paper[len]++;
					}
				}
			}
			else dfs(index + 1, paper_cnt); //색종이를 놓지 않아도 되는 자리면 넘어간다.

}
int main(void) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> a[i][j];
			if (a[i][j] == 1) total++;
		}
	}
	for (int i = 1; i <= 5; i++) paper[i] = 5;

	dfs(0, 0);

	if (MIN == 987654321) MIN = -1;
	printf("%d", MIN);
	return 0;
}
