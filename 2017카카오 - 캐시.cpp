/*
  vector의 erase 함수가 중간의 원소를 지워주기 때문에 vector를 사용 
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<string> v;
vector<string>::iterator search(string str) {
	vector<string>::iterator iter;
	for (iter = v.begin(); iter != v.end(); iter++) {
		if (str.compare(*iter) == 0)
			return iter;
	}
	return v.end();
}
int solution(int cacheSize, vector<string> cities) {

	for (int i = 0; i < cities.size(); i++) {
		transform(cities[i].begin(), cities[i].end(), cities[i].begin(), ::tolower);
	}
	int answer = 0;
	vector<string>::iterator iter;
	for (int i = 0; i < cities.size(); i++) {
		iter = search(cities[i]);
		if (iter == v.end()) {//미스
			answer += 5;
			v.push_back(cities[i]);
			if (v.size() > cacheSize) {
				v.erase(v.begin());
			}
		}
		else { //히트
			answer++;
			v.erase(iter);
			v.push_back(cities[i]);
		}
	}
	return answer;
}
int main(void) {

	return 0;
}
