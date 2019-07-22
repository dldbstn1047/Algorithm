/*
	BOJ 14891 - 톱니바퀴 (*)
	1. 바퀴를 돌릴떄 중간중간 바꾸는게 아니라 임시 배열에 바꾸고 옮기기
	2. 노트에 인덱스 0부터라고 썼으면 코드도 0부터 해야지 코드는 1부터 해서 햇갈리게 하지말고
*/
#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <math.h>

using namespace std;

int a[5][10];
int tmp[5][10];
int k;
void my_print() {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			printf("%d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void turn(int number, int turn_direction) {
	if (turn_direction == 1) { //시계 8번 - > 1번으로
		tmp[number][0] = tmp[number][8];
		for (int i = 0; i < 8; i++) {
			a[number][i+1] = tmp[number][i];
		}
	}
	else {
		tmp[number][9] = tmp[number][1];
		for (int i = 2; i < 10; i++) {
			a[number][i-1] = tmp[number][i];
		}
	}
}
void sol(int number, int turn_direction) {
	memcpy(tmp, a, sizeof(a));
	turn(number, turn_direction);
	int next_turn = turn_direction;
	for (int i = number - 1; i > 0; i--) { //타겟에서 왼쪽으로 검사 하는 부분
		if (tmp[i][3] != tmp[i + 1][7]) {//다르면 회전
			next_turn *= -1;
			turn(i, next_turn);
		}
		else break;
	}
	next_turn = turn_direction;
	for (int i = number + 1; i <= 4; i++) { //타겟에서 오른쪽으로 검사
		if (tmp[i - 1][3] != tmp[i][7]) {
			next_turn *= -1;
			turn(i, next_turn);
		}
		else break;
	}
}
void answer() {
	int ret = 0;
	for (int i = 0; i < 4; i++) {
		if (a[i + 1][1] == 1) {
			ret += (int)pow(2, i);
		}
	}
	printf("%d", ret);
}
int main(void) {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			scanf("%1d", &a[i][j]);
		}
	}
	cin >> k;
	int number, turn_direction;
	for (int i = 1; i <= k; i++) {
		cin >> number >> turn_direction;
		sol(number, turn_direction);
		//my_print();
	}
	answer();
	return 0;
}
