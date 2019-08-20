/*
	2017 KAKAO - 뉴스 클러스터링
	tranform 공부
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>

using namespace std;
vector<string> A, B, G, H;
int main(void) {
	return 0;
}
int solution(string str1, string str2) {
	transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
	transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

	for (int i = 0; i < str1.length() - 1; i++) {
		if (('a' <= str1[i] && str1[i] <= 'z') && ('a' <= str1[i + 1] && str1[i + 1] <= 'z')) {
			A.push_back(str1.substr(i, 2));
		}
	}
	for (int i = 0; i < str2.length() - 1; i++) {
		if (('a' <= str2[i] && str2[i] <= 'z')  && ('a' <= str2[i + 1] && str2[i + 1] <= 'z')) {
			B.push_back(str2.substr(i, 2));
		}
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	set_union(A.begin(), A.end(), B.begin(), B.end(), back_inserter(H));
	set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(G));
	/* 출력
	for (int i = 0; i < A.size(); i++) {
		cout << A[i] << " ";
	}
	cout << '\n';
	for (int i = 0; i < B.size(); i++) {
		cout << B[i] << " ";
	}
	cout << '\n';
	for (int i = 0; i < G.size(); i++) {
		cout << G[i] << " ";
	}
	cout << '\n';
	for (int i = 0; i < H.size(); i++) {
		cout << H[i] << " ";
	}
	cout << '\n';
	*/
	if (H.size() == 0) {
		return 65536;
	}

	return 65536.0 * G.size() / H.size();
}
