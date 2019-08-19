#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <limits.h>
#include <vector>

using namespace std;

int a[2001];
int b[2001];
int n;

int main(void) {
	//2017 KAKAO 1차 - 추석 트래픽
	return 0;
}
int solution(vector<string> lines) {
	n = lines.size();
	int yy, mm, dd, hh, MM, ss, zzz;
	double tmp;

	for (int i = 1; i <= n; i++) {
		sscanf(lines[i - 1].c_str(), "%d-%d-%d %d:%d:%d.%d %lfs", &yy, &mm, &dd, &hh, &MM, &ss, &zzz, &tmp);

		a[i] = hh * 3600;
		a[i] += (MM * 60);
		a[i] += (ss);
		a[i] *= 1000;
		a[i] += zzz;

		b[i] = (int)(tmp * 1000);
	}
	int MAX = -INT_MIN;
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		int start = a[i] - b[i] + 1;
		int end = start + 999;
		for (int j = 1; j <= n; j++) {
			int tmp_start = a[j] - b[j] + 1;
			int tmp_end = a[j];
			if (tmp_start < start && start <= tmp_end) cnt++;
			if (start <= tmp_start && tmp_start <= end) cnt++;
		}
		MAX = max(cnt, MAX);

		start = a[i];
		end = start + 999;
		cnt = 0;
		for (int j = 1; j <= n; j++) {
			int tmp_start = a[j] - b[j] + 1;
			int tmp_end = a[j];
			if (tmp_start < start && start <= tmp_end) cnt++;
			if (start <= tmp_start && tmp_start <= end) cnt++;
		}
		MAX = max(cnt, MAX);
	}

	int answer = MAX;
	return answer;
}
