/*
	2017 KAKAO - 뉴스 클러스터링
	set_union, set_intersection 사용 안하고 -
	**** str1과 str2로 만들어진 문자들이 각각 몇개 있는지 알아내고 교집합은 둘중 작은애로 합집합은 둘중 큰애로
	26*26 배열을 만들어서 ('앞자리문자' * 26 + '뒷자리문자')로 사용
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>

using namespace std;
int main(void) {
	return 0;
}
int solution(string str1, string str2) {
	vector<int> multiset1(26 * 26, 0);
	vector<int> multiset2(26 * 26, 0);

	transform(str1.begin(), str1.end(), str1.begin(), ::tolower); //소문자로 변경
	transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

	for (int i = 0; i < str1.length() - 1; i++) {
		if (('a' <= str1[i] && str1[i] <= 'z') && ('a' <= str1[i + 1] && str1[i + 1] <= 'z')) {
			multiset1[(str1[i] - 'a') * 26 + (str1[i + 1] - 'a')]++;
		}
	}
	for (int i = 0; i < str2.length() - 1; i++) {
		if (('a' <= str2[i] && str2[i] <= 'z') && ('a' <= str2[i + 1] && str2[i + 1] <= 'z')) {
			multiset2[(str2[i] - 'a') * 26 + (str2[i + 1] - 'a')]++;
		}
	}
	//sort(A.begin(), A.end());
	//sort(B.begin(), B.end());

	//set_union(A.begin(), A.end(), B.begin(), B.end(), back_inserter(H));
	//set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(G));
	int G = 0, H = 0;
	for (int i = 0; i < 26 * 26; i++) {
		G += min(multiset1[i], multiset2[i]);
	}
	for (int i = 0; i < 26 * 26; i++) {
		H += max(multiset1[i], multiset2[i]);
	}
	if (H == 0) return 65536;

	return 65536.0 * G / H;
}
