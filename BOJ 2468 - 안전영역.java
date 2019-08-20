package ForSolution;

import java.awt.Point;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class Main_2468_안전영역_이윤수 {
	private static int[] dy = {0, 0, -1, 1};
	private static int[] dx = {-1, 1, 0, 0};
	static int n, cnt, high_max = -1, MAX = -1;
	static int[][] a = new int[101][101];
	static int[][] visit;

	static void bfs(int row, int col, int h) {
		if(a[row][col] <= h) return;
		cnt++;
		Queue<Point> q = new LinkedList<Point>();
		Point out = new Point();
		Point in = new Point();
		q.add(new Point(col, row));
		if(visit[row][col] != 0) return;
		visit[row][col] = cnt;
		while(!q.isEmpty()) {
			out = q.poll();
			for(int d = 0; d < 4 ;d++) {
				in = (Point) out.clone();
				in.y += dy[d];
				in.x += dx[d];
				if(0 < in.y && in.y <= n && 0 < in.x && in.x <=n && visit[in.y][in.x] == 0 && a[in.y][in.x] > h ) {
					visit[in.y][in.x] = cnt;
					q.add(in);
				}
			}
		}
	}

	public static void main(String[] args) throws Exception {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.parseInt(br.readLine());
		for (int i = 1; i <= n; i++) {
			String[] line = br.readLine().trim().split(" ");
			for (int j = 1; j <= line.length; j++) {
				a[i][j] = Integer.parseInt(line[j-1]);
				high_max = Math.max(a[i][j], high_max);
			}
		}
		for (int h = 1; h <= high_max; h++) {
			visit = new int[101][101];
			cnt = 0;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					if(visit[i][j] != 0) continue;
					if(a[i][j] <= h) continue;
					bfs(i, j, h);
				}
			}
			MAX = Math.max(cnt, MAX);
		}
		if(MAX == 0) MAX = 1;
		System.out.println(MAX);
	}
}
