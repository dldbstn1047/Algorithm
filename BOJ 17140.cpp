/*
전반적으로 단순 구현 문제 였다. (**)
하지만 문제조건을 꼼꼼히 읽지 않아서 특정 케이스에서 틀렸다.
문제를 꼼꼼히 읽도록 하자.
카운트를 위해 count[101]배열을 두고 index가 해당숫자를 표현하고, 값에 해당 숫자의 갯수를 저장하였다.
count 배열을 1부터 차례대로 검사한다면 sort없이 2개의 오름차순 조건(숫자,count) 을 만족할 수 있다.
시간복잡도는 100*100*100*100 = 1억, BIG-O(n^4) n<=100 이지만
입력이 무조건 3*3이므로 최적화를 해주면 0.5초만에 가능 하다고 판단.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int a[101][101];
int r, c, k;
int row_size=3, col_size=3;
void my_print() {
	for (int i = 1; i <= row_size; i++) {
		for (int j = 1; j <= col_size; j++) {
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void C() {
	for (int col = 1; col <= col_size; col++) {
		int count[101] = { 0, };
		int count_MAX = -1;
		int a_MAX = -1;
		for (int row = 1; row <= row_size; row++) {
			if (a[row][col] == 0) continue;
			count[a[row][col]]++;
			a_MAX = max(a_MAX, a[row][col]);
			count_MAX = max(count_MAX, count[a[row][col]]);
		}
		int index = 0;
		for (int i = 1; i <= count_MAX; i++) {
			for (int j = 1; j <= a_MAX; j++) {
				if (count[j] == i) {
					a[++index][col] = j;
					a[++index][col] = count[j];
				}
			}
		}
		for (int i = index + 1; i <= row_size; i++) {
			a[i][col] = 0;
		}
		row_size = max(row_size, index);
	}
}
void R() {
	for (int row = 1; row <= row_size; row++) {
		int count[101] = { 0, }; //********** count 배열을 for문 밖에 선언 했었다가 count가 계속 겹치는 문제가 발생
		int count_MAX = -1;
		int a_MAX = -1;
		for (int col = 1; col <= col_size; col++) {
			if (a[row][col] == 0) continue; //0은 무시
			count[a[row][col]]++;
			a_MAX = max(a_MAX, a[row][col]); //a배열에 있는 가장 큰 숫자 찾기
			count_MAX = max(count_MAX, count[a[row][col]]);//가장큰 카운트 찾기 1부터 100까지 다 돌지 않게 하기 위함.
		}
		int index = 0;
		for (int i = 1; i <= count_MAX; i++) { //********** 숫자가 오름 차순으로 정렬되어야 하는데
			for (int j = 1; j <= a_MAX; j++) {//********** 처음에는 내림차순 정렬을 해버렷다. 문제 잘 읽자..
				if (count[j] == i) {
					a[row][++index] = j; //숫자먼저
					a[row][++index] = count[j];//그다음 숫자 갯수
				}
			}
		}
		/**********
		a배열에 연산 결과의 숫자를 덮어 씌었지만 미쳐 덮어지지 않은 숫자를 제거하지 않았었다.
		남은 자리는 0으로 채워야 하는 조건이 있었는데 문제를 꼼꼼히 읽지 않았던것이다.
		문제를 잘 읽도록 하자.
		**********/
		for (int i = index + 1; i <= col_size; i++) {
			a[row][i] = 0;
		}
		col_size = max(col_size, index);
	}
}
int main(void) {
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> a[i][j];
		}
	}
	int cnt = 0;
	while (cnt <= 100) {
		if (a[r][c] == k) break; //연산을 하지 않고도 완성될 수 있음으로 먼저 검사하고 연산 시작
		cnt++;
		if (row_size >= col_size)
			R();
		else
			C();
		//my_print();
	}
	if (cnt > 100) cnt = -1;
	printf("%d", cnt);
	return 0;
}
