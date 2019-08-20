/*
	2017 KAKAO - 뉴스 클러스터링
	1. "AB", "Ab", "ab" 대소문자 구별 없이 다 같은것으로 판단.
	2. set_union, set_intersection 공부
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
	for (int i = 0; i < str1.length() - 1; i++) {
		if ((('a' <= str1[i] && str1[i] <= 'z') || ('A' <= str1[i] && str1[i] <= 'Z')) &&
			(('a' <= str1[i + 1] && str1[i + 1] <= 'z') || ('A' <= str1[i + 1] && str1[i + 1] <= 'Z'))) {
			if ('a' <= str1[i]) str1[i] -= 32; //대소문자 구분 없으므로 소문자의 경우 대문자로 변경 후 저장.
			if ('a' <= str1[i + 1]) str1[i + 1] -= 32;
			A.push_back(str1.substr(i, 2));
		}
	}
	for (int i = 0; i < str2.length() - 1; i++) {
		if ((('a' <= str2[i] && str2[i] <= 'z') || ('A' <= str2[i] && str2[i] <= 'Z')) &&
			(('a' <= str2[i + 1] && str2[i + 1] <= 'z') || ('A' <= str2[i + 1] && str2[i + 1] <= 'Z'))) {
			if ('a' <= str2[i]) str2[i] -= 32;
			if ('a' <= str2[i + 1]) str2[i + 1] -= 32;
			B.push_back(str2.substr(i, 2));
		}
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	set_union(A.begin(), A.end(), B.begin(), B.end(), back_inserter(H)); //********************* 공부
	set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(G)); //********************* 공부
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
