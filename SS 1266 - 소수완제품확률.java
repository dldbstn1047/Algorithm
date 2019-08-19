import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Solution_1266_SW문제해결응용9일차_소수완제품확률_이윤수 {
	static int T;
	static int a, b;
	static double sum_a = 0.0, sum_b = 0.0;
	static void dfs(int index, int cnt) {
		if(index > 18) {
			if(cnt == 2 || cnt == 3 || cnt == 5 || cnt == 7 || cnt == 11 || cnt == 13 || cnt == 17) return;
			double ret_a = Math.pow(a/100.0, cnt);
			ret_a *= Math.pow(1.0 - a/100.0, 18-cnt);
			sum_a += ret_a;

			double ret_b = Math.pow(b/100.0, cnt);
			ret_b *= Math.pow(1.0 - b/100.0, 18-cnt);
			sum_b += ret_b;
			return;
		}

		dfs(index + 1, cnt + 1);
		dfs(index + 1, cnt);
	}

	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		for(int t = 1; t <= T; t++) {
			sum_a = 0.0;
			sum_b = 0.0;
			String[] input = br.readLine().split(" ");
			a = Integer.parseInt(input[0]);
			b = Integer.parseInt(input[1]);

			dfs(1, 0);
			dfs(1, 0);
			System.out.printf("#%d %f\n", t, (1.0 - (sum_a * sum_b)));
		}
	}
}
