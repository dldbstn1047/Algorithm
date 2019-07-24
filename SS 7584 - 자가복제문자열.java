/**
 * SS 7584 - 자가복제 문자열 (*****)
 * 문제 : 1, 2, 4, 8, 16 ... 2^n 자리는 항상 0 이며, 이 0을 기준으로 죄우대칭 + 비트반전 으로 반복된다.
 * k <= 10^18 이므로 굉장히 크다. long 사용
 * 1. 들어온  k보다 작은 가장 큰 2^n을 구한다.
 * 2. 구한 2^n을 기준축으로 하여 왼쪽으로 대칭이동한다. (반복)
 * 3. 대칭 이동을 할수 없게 k가 2^n 값이면 탈출
 * 4. 첫 숫자인 1로 오면 탈줄
 * 5. 대칭이동한 횟수를 센다
 * 6. 대칭이동 횟수가 짝수면 0 홀수면 1이다.
 *
 *
 * (다른 방법)
 * 1.001001100011011... 문자열을 짝수번쨰와 홀수번째를 나누어본다.
 * 2.홀수번쨰가 0 1 0 1 0 1... 이 반복된다.
 * 3.짝수번째만 빼서 그 문자열에서 또 짝수 홀수를 나눈다.
 * 4.또 홀수번째가 0 1 0 1 0 1.. 반복된다.
 * 5.k가 홀수라면 0 1 0 1... 반복되는 값이고
 * 6.k가 짝수 라면  k를 2로 나눈다 - 0 1 0 1.. 반복되는 홀수번째 수를 신경 쓰지않는 방법 즉 홀수를 뺴고만든 문자열에서 k/2번쨰를 구하는거
 * 7.이렇게 k가 홀수가 나올때 까지 나누고 k가 홀수가 나오면 0 1 0 1.. 으로 찾는다.
 */
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Solution_7584_자가복제문자열_이윤수 {
	static long[] two = new long[65];
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int ans = 0;
		int T = Integer.parseInt(br.readLine());
		for(int t =1; t <=T ; t++) {
			long num = Long.parseLong(br.readLine());
			int max;
			long gap;
			int cnt  = 0;
			while(true) {
				max = (int)((Math.log(num)/Math.log(2))); //********** 로그의 나누기는 밑을 바꾸는 과정 (밑 2 만들기)
				gap = num - (long)(1L << max); // num보다 작지만 가장큰 2^n 과의 gap(거리) 구하기
				cnt++;
				num -= (gap*2); // gap만큼 빼서 2^n으로 가고 또 gap만큼뺴서 대칭이동
				if(gap == 0 || num == 1) {
					if(gap == 0) cnt--; //gap이 0인 경우는 num숫자가 2^n 이므로 이동을 한게 아니니 cnt를 하나 줄인다.
					break;
				}
			}
			System.out.printf("#%d %d\n", t, cnt%2==0?0:1); //cnt 가 짝수면 0, 홀수면 1
		}
	}
}
