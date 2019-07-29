/*
	BOJ 13458 - 시험감독 (*)
	long 형으로 해야 한다.
*/
#include <iostream>
#include <algorithm>

using namespace std;

long a[1000001];
int n;
long b, c;
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	cin >> b >> c;

	long cnt = 0;
	for (int i = 1; i <= n; i++) {
		a[i] -= b;
		cnt++;
		if (a[i] <= 0) continue;
		if (a[i] % c > 0) {
			cnt += (a[i] / c);
			cnt++;
		}
		else {
			cnt += a[i] / c;
		}
	}
	printf("%ld", cnt);

	return 0;
}
