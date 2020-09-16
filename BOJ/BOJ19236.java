package SAMSUNG;

import java.io.*;
import java.util.*;

public class BOJ19236 {

	static final int MAP_SIZE = 4;
	static final int EMPTY = -11111111;
	static final int SHARK = 99999;
	static final int DIR_SIZE = 8;
	static final int dy[] = {-1,-1,0,1,1,1,0,-1};
	static final int dx[] = {0,-1,-1,-1,0,1,1,1};
	static int answer = -1;
	
	public static class Fish {
		int num, dir;
		
		Fish (int num, int dir)
		{
			this.num = num;
			this.dir = dir;
		}
	}
	
	public static boolean isFish(Fish[][] map, int y, int x)
	{
		int number = map[y][x].num;
		if (1 <= number && number <= 16) return true;
		else return false;
	}
	
	public static Fish[][] copy(Fish[][] src, Fish[][] dst) {
		for (int i = 0; i < MAP_SIZE; ++i)
		{
			for (int j = 0; j < MAP_SIZE; ++j)
			{
				dst[i][j] = new Fish(src[i][j].num, src[i][j].dir);
			}
		}
		return dst;
	}
	
	public static boolean safe(int y, int x)
	{
		return (0 <= y && y < MAP_SIZE && 0 <= x && x < MAP_SIZE);
	}
	
	public static void fishMove(Fish[][] map) 
	{			
		for (int num = 1; num <= 16; ++num)
		{
			boolean isChanged = false;
			
			for (int i = 0; i < MAP_SIZE; ++i)
			{
				for (int j = 0; j < MAP_SIZE; ++j)
				{
					if (map[i][j].num == num && (isChanged == false))
					{
						//8방향 탐색
						int nowDir = map[i][j].dir;
						for (int loop = 0; loop < DIR_SIZE; ++loop)
						{
							int ny = i + dy[(nowDir + loop) % DIR_SIZE];
							int nx = j + dx[(nowDir + loop) % DIR_SIZE];
							
							if (safe(ny,nx) == false)
								continue;
							if (map[ny][nx].num == SHARK)
								continue;
							
							isChanged = true;
							if (map[ny][nx].num == EMPTY)
							{
								map[ny][nx] = new Fish(num,((nowDir + loop) % DIR_SIZE));
								map[i][j] = new Fish(EMPTY,EMPTY);
							}
							else if (isFish(map,ny,nx) == true)
							{
								Fish tmp = new Fish(map[ny][nx].num, map[ny][nx].dir);
								map[ny][nx] = new Fish(num,((nowDir + loop) % DIR_SIZE));
								map[i][j] = tmp;
							}
							
							break;
						}
					}
				}
			}
		}
	}
	
	public static int dfs(Fish[][] mapState, int sum)
	{
		//물고기 이동
		Fish[][] nowState = new Fish[MAP_SIZE][MAP_SIZE];
		nowState = copy(mapState,nowState);

		fishMove(nowState);
		
		//상어 이동
		for (int i = 0; i < MAP_SIZE; ++i)
		{
			for (int j = 0; j < MAP_SIZE; ++j)
			{
				if (nowState[i][j].num == SHARK)
				{
					int ny = i;
					int nx = j;
					int dir = nowState[i][j].dir;
					
					for (int loop = 0; loop < 3; ++loop)
					{
						ny += dy[dir];
						nx += dx[dir];
						
						if (safe(ny,nx) == true && isFish(nowState,ny,nx))
						{
							Fish[][] nxtState = new Fish[MAP_SIZE][MAP_SIZE];
							nxtState = copy(nowState,nxtState);
							
							int addNumber = nxtState[ny][nx].num;
							nxtState[ny][nx].num = SHARK;
							nxtState[i][j] = new Fish(EMPTY,EMPTY);
							
							dfs(nxtState, sum + addNumber);
						}
					}
				}
			}
		}
		
		answer = Math.max(answer, sum);
		
		return 0;
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Fish[][] init = new Fish[MAP_SIZE][MAP_SIZE];
		
		int idx = 0;
		for (int loop = 0; loop < MAP_SIZE; ++loop)
		{
			String[] info = br.readLine().split(" ");
			
			for (int i = 0; i < info.length; i += 2)
			{
				int num = Integer.parseInt(info[i]);
				int dir = Integer.parseInt(info[i+1]);
				dir--;
				
				int y = idx / MAP_SIZE;
				int x = idx % MAP_SIZE;
				
				init[y][x] = new Fish(num,dir);
				
				idx += 1;
			}
		}
		
		int startNumber = init[0][0].num;
		init[0][0].num = SHARK;
		dfs(init,startNumber);
		
		System.out.println(answer);
	}
}
