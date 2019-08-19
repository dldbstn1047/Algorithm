#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <limits.h>

using namespace std;
#define BUF_SIZE 86400000
string str[11] = { " ",
"2016-09-15 20:59:57.421 0.351s",
"2016-09-15 20:59:58.233 1.181s",
"2016-09-15 20:59:58.299 0.8s",
"2016-09-15 20:59:58.688 1.041s",
"2016-09-15 20:59:59.591 1.412s",
"2016-09-15 21:00:00.464 1.466s",
"2016-09-15 21:00:00.741 1.581s",
"2016-09-15 21:00:00.748 2.31s",
"2016-09-15 21:00:00.966 0.381s",
"2016-09-15 21:00:02.066 2.62s" };
int n = 10;

int main(void) {
	int yy, mm, dd, hh, MM, ss, zzz;
	double tmp;
	int req_time;
	int MAX = -1;
	int buf[BUF_SIZE] = { 0, };
	for (int i = 1; i <= n; i++) {
		sscanf(str[i].c_str(), "%d-%d-%d %d:%d:%d.%d %lfs", &yy, &mm, &dd, &hh, &MM, &ss, &zzz, &tmp);
		printf("%d %d %d %d %d %d %d %f\n", yy, mm, dd, hh, MM, ss, zzz, tmp);
		long end = hh * 3600;
		end += (MM * 60);
		end += ss;
		end *= 1000;
		end += zzz;
		req_time = (int)(tmp * 1000);

		printf("%ld\n", end);
		for (long j = end - req_time + 1 - 999; j <= end; j++) {
			if (j < 0 || j >= BUF_SIZE) continue;
			buf[j]++;
			MAX = max(buf[j], MAX);
		}
	}

	printf("%d", MAX);

	return 0 ;
}
