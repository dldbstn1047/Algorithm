/*
	BOJ 16637 - 괄호추가하기
	dfs방식으로 좀 코드를 개선했다.
*/
#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

int n;
char a[21];
int MAX = INT_MIN;
int excute(int a, int b, char op) { return op == '+' ? a + b : op == '-' ? a - b : a * b; }
int cal(int s, int e) {

	int ret = a[s] - '0';

	for (int i = s + 2; i <= e; i+=2) {
		ret = excute(ret, a[i] - '0' , a[i - 1]);
	}

	return ret;
}
void dfs(int s, int mid_sum) {
	if (s > n) {  // s >= n 을 하게 되면 마지막것이 계산이 안된다.
		MAX = max(mid_sum, MAX);
		return;
	}
	/*******************************************************************************************************************************/
	for (int i = s; i <= min(s + 2, n); i += 2) { //이 for문은 괄호를 짝직는 역할 // 최대 s+2 라는것은 괄호안에서 연산 1번밖에 안된다.
		dfs(i + 2, excute(mid_sum, cal(s, i), a[s-1])); //cal은 괄호를 먼저 계산 하는 역할
	}													//a[s-1]인 이유를 괄호를 먼저 계산한 후 '(' (여는괄호) 전 oper를 가지고 나머지와
														//계산해야 하기 때문
}
int main(void) {
	cin >> n >> (a + 1);
	a[0] = '+';
	dfs(1, 0);

	printf("%d", MAX);
	return 0;
}
