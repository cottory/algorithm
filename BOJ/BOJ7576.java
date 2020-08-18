import java.io.*;
import java.util.*;

public class BOJ7576 {
	
	public static int N,M;
	public static int tomatoSize;
	public static int board[][];
	public static int trip[][];
	public static Queue<Pair> q;
	
	public static int dy[] = {-1,1,0,0};
	public static int dx[] = {0,0,-1,1};
	
	static public class Pair {
		int y,x;
		Pair(int y, int x) {
			this.y = y;
			this.x = x;
		}
	}
	
	public static boolean isSafe(int y, int x) {
		return (0 <= y && y < N && 0 <= x && x < M);
	}
	public static int bfs() {
		
		int day = 0;
		
		while (true)
		{
			int loopSize = q.size();
			
			if (loopSize == 0) {
				break;
			}
			
			for (int loop = 0; loop < loopSize; ++loop)
			{
				Pair now = q.poll();
				
				for (int dir = 0; dir < 4; ++dir)
				{
					int ny = now.y + dy[dir];
					int nx = now.x + dx[dir];
					
					if (!isSafe(ny,nx)) continue;
					if (board[ny][nx] == -1) continue;
					if (trip[ny][nx] == 1) continue;
					
					trip[ny][nx] = 1;
					tomatoSize -= 1;
					board[ny][nx] = 1;
					q.offer(new Pair(ny,nx));
				}
			}
			
			day += 1;
		}
		
		return tomatoSize == 0 ? (day-1) : -1;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String[] line = br.readLine().split(" ");
		
		M = Integer.parseInt(line[0]);
		N = Integer.parseInt(line[1]);
			
		board = new int[N][M];
		trip = new int[N][M];
		
		for (int i = 0; i < N; ++i) 
		{
			line = br.readLine().split(" ");
			for (int j = 0; j < M; ++j) 
			{
				board[i][j] = Integer.parseInt(line[j]);
			}
		}
		
		q = new LinkedList<>();
		
		for (int i = 0; i < N; ++i) 
		{
			for (int j = 0; j < M; ++j)
			{
				if (board[i][j] == 1)
				{
					q.offer(new Pair(i,j));
					trip[i][j] = 1;
				}
				else if (board[i][j] == 0)
				{
					tomatoSize += 1;
				}
			}
		}
		
		System.out.println(bfs());
	}
}
