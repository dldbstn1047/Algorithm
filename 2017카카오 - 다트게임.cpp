#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


int solution(string a) {
	int index = 0,  now = -1;
	int num[4] = { 0, };
	for (int i = 0; i < a.size() ; i++) {
		if( '0' <= a[i] && a[i] <= '9'){
			if (a[i] == '1') {
				if (a[i + 1] == '0') {
					now = 10;
					i++;
				}
				else {
					now = 1;
				}

			}else
				now = a[i] - '0';
		}
		if (now != -1) {
			num[++index] = now;
			now = -1;
			continue;
		}
		if (a[i] == 'S') { num[index] = (int)pow(num[index], 1); continue; }
		if (a[i] == 'D') { num[index] = (int)pow(num[index], 2); continue; }
		if (a[i] == 'T') { num[index] = (int)pow(num[index], 3); continue; }

		if (a[i] == '*') {
			num[index -1] *= 2;
			num[index] *= 2;
			continue;
		}
		if (a[i] == '#') {
			num[index] *= -1;
			continue;
		}

	}
	int answer = 0;
	for (int i = 1; i <= index; i++) {
		printf("%d ", num[i]);
		answer += num[i];
	}
	return answer;
}
int main(void) {
	return 0;
}
