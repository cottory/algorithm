
import java.io.*;
import java.util.*;

public class BOJ3055 {

	public static class Tuple {
		int type, y, x, time;
		Tuple(int type, int y, int x, int time) {
			this.type = type;
			this.y = y;
			this.x = x;
			this.time = time;
		}
	}
	
	public static final int IMPOSSIBLE = 987654321;
	public static final int GOSUM = 0;
	public static final int WATER = 1;
	public static final char ROCK = 'X';
	public static int R,C,by,bx,gy,gx;	//비버 굴 좌표, 고슴도치 좌표
	public static String[] board;
	public static boolean trip[][];
	public static int dy[] = {-1,1,0,0};
	public static int dx[] = {0,0,-1,1};
	
	public static boolean isSafe(int y, int x) {
		return (0 <= y && y < R && 0 <= x && x < C);
	}
	
	public static int bfs() {
		
		int ret = IMPOSSIBLE;
		
		Queue<Tuple> q = new LinkedList<>();
		
		for (int i = 0; i < R; ++i) 
		{
			for (int j = 0; j < C; ++j)
			{
				if (board[i].charAt(j) == '*') 
				{
					q.offer(new Tuple(WATER,i,j,0));
					trip[i][j] = true;
				}
			}
		}
		
		q.offer(new Tuple(GOSUM, gy,gx, 0));
		trip[gy][gx] = true;
		
		while (true)
		{
			int loop = q.size();
			if (loop == 0)
			{
				break;
			}
			
			while (loop > 0)
			{
				Tuple now = q.poll();
				
				if (now.y == by && now.x == bx && now.type == GOSUM)
				{
					ret = Math.min(ret, now.time);
				}
				else
				{
					for (int dir = 0; dir < 4; ++dir)
					{
						int ny = now.y + dy[dir];
						int nx = now.x + dx[dir];
						
						if (!isSafe(ny,nx)) continue;
						if (trip[ny][nx]) continue;
						if (board[ny].charAt(nx) == ROCK) continue;
						
						if (now.type == WATER) 
						{
							if (board[ny].charAt(nx) == 'D') continue;
							
						}
						else if (now.type == GOSUM)
						{
							if (board[ny].charAt(nx) == '*') continue;
						}
						
						trip[ny][nx] = true;
						q.offer(new Tuple(now.type, ny, nx, now.time + 1));
					}
				}
				
				loop--;
			}	
		}
		
		return ret;
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String[] line = br.readLine().split(" ");
		R = Integer.parseInt(line[0]);
		C = Integer.parseInt(line[1]);
		board = new String[R];
		trip = new boolean[R][C];
		
		for (int i = 0; i < R; ++i)
		{
			board[i] = br.readLine();
		}
		
		for (int i = 0; i < R; ++i)
		{
			for (int j = 0; j < C; ++j)
			{
				if (board[i].charAt(j) == 'D')
				{
					by = i;
					bx = j;
				}
				else if (board[i].charAt(j) == 'S')
				{
					gy = i;
					gx = j;
				}
			}
		}
		
		int answer = bfs();
		if (answer == IMPOSSIBLE) {
			System.out.println("KAKTUS");
		}
		else {
			System.out.println(answer);
		}
		
		
	}
}
