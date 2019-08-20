#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
	vector<string> answer;
	vector<int> tmp;
	for (int i = 0; i < n; i++) {
		tmp.push_back(arr1[i] | arr2[i]);
	}
	for (int c = 0; c < n; c++) {
		string str;
		for (int i = n - 1; i >= 0; i--) {
			int num = pow(2, i);
			if (tmp[c] >= num) {
				str.append("#");
				tmp[c] -= num;
			}
			else {
				str.append(" ");
			}
		}
		answer.push_back(str);
	}
	return answer;
}
int main(void) {

	return 0;
}
