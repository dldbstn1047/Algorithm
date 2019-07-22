/**
SS 1210 - Ladder1
사다리 타고 내려가는 문제인데 도착점에서 올라가듯이 풀면 끝
*/
import java.util.Scanner;

public class Ladder1 {
	static int[][] a;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		for(int t = 1; t <= 10; t++) {
			int number = sc.nextInt();
			a = new int[101][101];
			int col = 0;;
			for(int i =1; i <= 100; i++) {
				for(int j= 1;j <=100;j++) {
					a[i][j] = sc.nextInt();
					if(a[i][j] == 2) col = j;
				}
			}

			for(int row = 100; row >0;row--) {
				if(col != 1 && a[row][col - 1] == 1) { //왼쪽
					while(true) {
						if(col == 1) {break;}
						if(a[row][col -1 ] == 0) {break;}
						col--;
					}
					continue;
				}
				if(col != 100 && a[row][col+1] == 1) {
					while(true) {
						if(col == 100) {break;}
						if(a[row][col+1] == 0) {break;}
						col++;
					}
					continue;
				}
			}
			System.out.printf("#%d %d\n", t, col -1 );
		}
	}
}
