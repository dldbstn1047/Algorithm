import java.awt.Point;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Solution_1247_SW문제해결응용3일차_최적경로_이윤수 {
	static int T, n;
	static Point[] a ;
	static int[] visit;
	static int MIN = 200000000;
	static int distance(Point a, Point b) {
		return Math.abs(a.x - b.x) + Math.abs(a.y - b.y);
	}
	static void dfs(int index, int cnt, int sum) {
		if(sum >= MIN) return;
		if(cnt == n) {
			MIN = Math.min(MIN, sum + distance(a[index], a[2]));
			return;
		}

		for(int i = 3; i <= n + 2; i++) {
			if(visit[i] != 0) continue;
			visit[i] = cnt + 1;
			dfs(i, cnt + 1, sum + distance(a[index], a[i]));
			visit[i] = 0;
		}
	}
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine().trim());
		for(int t = 1; t <= T ; t++) {
			a = new Point[15];
			for(int i =0; i < 15; i++) {
				a[i] = new Point();
			}
			visit = new int[15];
			MIN = 20000000;
			n = Integer.parseInt(br.readLine().trim());
			String[] input;
			input = br.readLine().trim().split(" ");
			for(int i = 0; i < input.length; i+=2) {
				a[i/2 + 1].x = Integer.parseInt(input[i]);
				a[i/2 + 1].y = Integer.parseInt(input[i + 1]);
			}
			for(int i = 3;i <= n + 2; i++) {
				visit[i] = 1;
				dfs(i, 1, distance(a[1], a[i]));
				visit[i] = 0;
			}
			System.out.printf("#%d %d\n", t, MIN);
		}
	}
}
