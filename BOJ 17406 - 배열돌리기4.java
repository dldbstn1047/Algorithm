package ForSolution;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main_17406_배열돌리기4_이윤수 {
	public static int n, m, k, MIN = 987654321;
	public static int[][] a = new int[51][51];
	public static int[] visit = new int[7];
	public static int[] dy = { 1, 0, -1, 0 };
	public static int[] dx = { 0, 1, 0, -1 };

	public static int[] R = new int[7];
	public static int[] C = new int[7];
	public static int[] S = new int[7];

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		n = Integer.parseInt(input[0]);
		m = Integer.parseInt(input[1]);
		k = Integer.parseInt(input[2]);
		for (int i = 1; i <= n; i++) {
			input = br.readLine().split(" ");
			for (int j = 1; j <= input.length; j++) {
				a[i][j] = Integer.parseInt(input[j - 1]);
			}
		}
		for (int i = 1; i <= k; i++) {
			input = br.readLine().split(" ");
			R[i] = Integer.parseInt(input[0]);
			C[i] = Integer.parseInt(input[1]);
			S[i] = Integer.parseInt(input[2]);
		}

		dfs(0);
		System.out.println(MIN);
	}

	public static void turn(int index) {
		int row = R[index];
		int col = C[index];
		int y;
		int x;
		int s = S[index];
		int tmp;
		for (int i = 1; i <= s; i++) {
			y = row - i;
			x = col - i;
			tmp = a[row - i][col - i];
			for (int d = 0; d < 4; d++) {
				for (int j = 1; j <= i * 2; j++) {
					a[y][x] = a[y + dy[d]][x + dx[d]];
					y += dy[d];
					x += dx[d];

				}
			}
			a[row -i][col - i + 1] = tmp;
		}
	}

	public static void dfs(int index) {



		if (index == k) {
			for (int row = 1; row <= n; row++) {
				int cnt = 0;
				for (int col = 1; col <= m; col++) {
					cnt += a[row][col];
				}
				MIN = Math.min(cnt, MIN);
			}
			return;
		}

		int[][] tmp = new int[51][51];

		for (int l = 1; l <= k; l++) {
			if (visit[l] == 1)
				continue;

			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					tmp[i][j] = a[i][j];
				}
			}
			turn(l);
			visit[l] = 1;
			dfs(index + 1);
			visit[l] = 0;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					a[i][j] = tmp[i][j];
				}
			}

		}
	}


}
