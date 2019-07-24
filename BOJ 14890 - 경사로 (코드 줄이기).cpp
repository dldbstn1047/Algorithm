/*
	BOJ 14890 - 경사로 (코드 줄이기)
	이전 코드의 working을 없애고 same_high로만 결정한다. working의 과정을 same_high에서 음수로 처리한다.
	그리고 여러 if과정을 && 연산으로 묶는다 ( 연산 방향 -> ) / (&&, ||은 이미 답이결정나면 뒷 연산 안함)
	1. row를 2n 크기로 잡고 (n+1 ~ 2n)에는 (1 ~ n)을 90도 회전한것을 넣는다.
	2. 가로로 확인하면서 같은 높이면 same_high 를 1씩 늘린다
	3. 한칸 위로 올라간다면, same_high가 l보다 크거나 같은지 검사한다. 안되면 경사로를 못 놓으므로 탈락
	4. 한칸 아래로 간다면, l만큼 경사로를 놓고 다시 same_high를 증가시켜야 하기 때문에
		l 에서 1을뺸 값을 음수로해서 same_high에 넣어준다.
	5. same_high가 음수인경우 경사로를 놓는 중이므로 경사로의 높이가 바뀌면 안된다. 4번에 same_high >= 0 조건추가
	6. for 문는 마지막에 증감연산자 까지 하고 밖으로 나오므로 j가 마지막 값인 n 보다 크면서
		same_high >= 0이면 성공이다 (same_high가 음수라면 경사로를 놓는 중)
*/
#include <iostream>
#include <algorithm>

using namespace std;

int n, l;
int a[201][101];
int main(void) {
	cin >> n >> l;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i + n][j] = a[j][i]; //세로 처리
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n * 2; i++) {
		int same_high = 1;
		int j;
		for (j = 2; j <= n; j++) {
			if (a[i][j - 1] == a[i][j]) same_high++;
			else if (a[i][j - 1] + 1 == a[i][j] && same_high >= l) same_high = 1;
			else if (a[i][j - 1] - 1 == a[i][j] && same_high >= 0) same_high = 1 - l;
			else break;
		}
		if (j > n && same_high >= 0) cnt++;
	}
	printf("%d", cnt);
	return 0;
}
