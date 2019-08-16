#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m, r;
int MAX;
int a[100][100];
void one(); //상하 반전
void two(); //좌우 반전
void three(); // 오른쪽 90도
void four(); // 왼쪽 90도
void five();
void six();
void my_print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << a[i][j] << " ";
		}
		cout << '\n';
	}
	cout << '\n';
}
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m >> r;
	MAX = n > m ? n : m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	int tmp;
	for (int i = 0; i < r; i++) {
		cin >> tmp;
		switch (tmp) {
		case 1: one(); break;
		case 2: two(); break;
		case 3: three(); break;
		case 4: four(); break;
		case 5: five(); break;
		case 6: six(); break;
		}
	}
	my_print();
	return 0;
}
void one() {
	int tmp[100];
	for (int i = 0; i < n / 2; i++) {
		memcpy(tmp, a[i], sizeof(a[i]));
		memcpy(a[i], a[n - 1 - i], sizeof(a[i]));
		memcpy(a[n - 1 - i], tmp, sizeof(tmp));
	}
}
void two() {
	for (int j = 0; j < m/2; j++) {
		for (int i = 0; i < n; i++) {
			int tmp = a[i][j];
			a[i][j] = a[i][m - 1 - j];
			a[i][m - 1 - j] = tmp;
		}
	}
}
void three() {
	int tmp[100][100];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tmp[j][n-1-i] = a[i][j];
		}
	}
	int t = n;
	n = m;
	m = t;
	memcpy(a, tmp, sizeof(a));
}
void four() {
	int tmp[100][100];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tmp[m - 1 - j][i] = a[i][j];
		}
	}
	int t = n;
	n = m;
	m = t;
	memcpy(a, tmp, sizeof(tmp));
}
void five() {
	int row[] = { 0, n / 2, n / 2, 0};
	int col[] = { 0, 0 , m / 2 , m / 2};

	int tmp = a[0][0];
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < m / 2; j++) {
			int tmp = a[row[0] + i][col[0] + j];
			for (int d = 0; d < 3; d++) {
				a[row[d] + i][col[d] + j] = a[row[d + 1] + i][col[d + 1] + j];
			}
			a[row[3] + i][col[3] + j] = tmp;
		}
	}
}
void six() {
	int row[] = { 0, 0, n / 2, n/2 };
	int col[] = { 0, m/2 , m / 2 , 0};

	int tmp = a[0][0];
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < m / 2; j++) {
			int tmp = a[row[0] + i][col[0] + j];
			for (int d = 0; d < 3; d++) {
				a[row[d] + i][col[d] + j] = a[row[d + 1] + i][col[d + 1] + j];
			}
			a[row[3] + i][col[3] + j] = tmp;
		}
	}
}
