import java.util.*;
import java.io.*;

public class BOJ5427 {

	public static int dy[] = {-1,1,0,0};
	public static int dx[] = {0,0,-1,1}; 
	public static int N,W,H,sy,sx;	//sangGeun
	public static final int FIRE = 0;
	public static final int SANGGEUN = 1;
	public static final int DIR_SIZE = 4;
	public static ArrayList<String> board;
	public static boolean trip[][];
	public static Queue<Tuple> q;
	
	static class Tuple {
		int y, x, type, time;
		Tuple(int y, int x, int type, int time) {
			this.y = y;
			this.x = x;
			this.type = type;
			this.time = time;
		}
	}
	
	public static boolean isSafe(int y, int x) {
		return (0 <= y && y < H && 0 <= x && x < W);
	}
	public static int bfs() {
		
		q.offer(new Tuple(sy,sx,SANGGEUN,0));
		
		while (true)
		{
			int loopSize = q.size();
			if (loopSize == 0) 
			{
				break;
			}
			
			for (int loop = 0; loop < loopSize; ++loop)
			{
				Tuple now = q.poll();
				
				if (now.type == SANGGEUN)
				{
					for (int dir = 0; dir < DIR_SIZE; ++dir)
					{
						int ny = now.y + dy[dir];
						int nx = now.x + dx[dir];
						if (!isSafe(ny,nx)) 
							return now.time + 1;
					}
				}
				
				for (int dir = 0; dir < DIR_SIZE; ++dir)
				{
					int ny = now.y + dy[dir];
					int nx = now.x + dx[dir];
					
					if (!isSafe(ny,nx)) continue;
					if (trip[ny][nx]) continue;
					if (board.get(ny).charAt(nx) == '#') continue;
					
					if (now.type == SANGGEUN)
					{
						//sangGeun
						if (board.get(ny).charAt(nx) == '*') continue;
					}
					
					trip[ny][nx] = true;
					q.offer(new Tuple(ny,nx,now.type,now.time + 1));
				}
			}
		}
		
		return -1;
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String line = br.readLine();
		N = Integer.parseInt(line);
		
		for (int test_case = 0; test_case < N; ++test_case)
		{
			String[] board_Size = br.readLine().split(" ");
			W = Integer.parseInt(board_Size[0]);
			H = Integer.parseInt(board_Size[1]);
			board = new ArrayList<>();
			q = new LinkedList<>();
			trip = new boolean[H][W];
			
			for (int i = 0; i < H; ++i)
			{
				line = br.readLine();
				board.add(line);
			}
			
			for (int i = 0; i < H; ++i)
			{
				for (int j = 0; j < W; ++j)
				{
					if (board.get(i).charAt(j) == '@')
					{
						sy = i;
						sx = j;
					}
					else if (board.get(i).charAt(j) == '*')
					{
						q.offer(new Tuple(i,j,FIRE,0));
					}
				}
			}
			
			int ans = bfs();
			if (ans == -1) 
			{
				System.out.println("IMPOSSIBLE");
			}
			else 
			{
				System.out.println(ans);
			}
		}
	}
}
