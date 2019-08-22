#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
int index = 1;
char buf[100200];
int max_size;
bool get(int num, int n) {
	vector<char> v;
	int d = 0;
	while (num != 0) {
		d = num % n;
		if (d == 10) v.push_back('A');
		else if (d == 11) v.push_back('B');
		else if (d == 12) v.push_back('C');
		else if (d == 13) v.push_back('D');
		else if (d == 14) v.push_back('E');
		else if (d == 15) v.push_back('F');
		else v.push_back(d + '0');
		num /= n;
	}
	for (int i = v.size() - 1; i >= 0; i--) {
		buf[index++] = v[i];
		if (index > max_size) return false;
	}
	return true;

}
string solution(int n, int t, int m, int p) {
	max_size = m * t;
	char ret[1001] = { 0, };
	buf[index++] = '0';
	int num = 1;
	while (get(num++, n));

	int ret_index = 0;
	int cnt = 0;
	ret_index += p;
	while (cnt < t) {
		ret[cnt++] = buf[ret_index];
		ret_index += m;
		if (ret_index > max_size) break;
	}
	ret[cnt] = '\0';
	string answer = ret;
	return answer;
}
int main(void) {
	//solution(2, 4, 2, 1);
	return 0;
}
