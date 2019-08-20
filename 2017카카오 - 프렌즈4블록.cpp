#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>>
using namespace std;

int solution(int m, int n, vector<string> a) {
	bool check = false;
	int tmp[30][30];
	int cnt = 0;
	do
	{
		memset(tmp, 0, sizeof(tmp));
		check = false;
		for (int i = 0; i < m - 1; i++) { //4개 제거
			for (int j = 0; j < n - 1; j++) {
				char c = a[i][j];
				if (c == '#') continue;
				if (a[i][j] == c && a[i + 1][j] == c && a[i][j + 1] == c && a[i + 1][j + 1] == c) {
					check = true;
					tmp[i][j] = tmp[i + 1][j] = tmp[i][j + 1] = tmp[i + 1][j + 1] = -1; //실제배열 아닌 tmp에 표시
				}
			}
		}
		for (int i = 0; i < m; i++) { //갯수세기
			for (int j = 0; j < n; j++) {
				if (tmp[i][j] == -1) {
					cnt++;
					a[i][j] = '#'; //4개 모인거 제거 하면서 갯수 세기
				}
			}
		}

		for (int row = m - 1; row >= 0; row--) { //빈칸 내리기
			for (int col = 0; col < n; col++) {
				if (a[row][col] == '#') {
					for (int tmp_row = row; tmp_row >= 0; tmp_row--) {
						if (a[tmp_row][col] != '#') {
							a[row][col] = a[tmp_row][col];
							a[tmp_row][col] = '#';
							break;
						}
					}
				}
			}
		}


	} while (check);

	int answer = cnt;
	return answer;
}
int main(void) {

	return 0;
}
