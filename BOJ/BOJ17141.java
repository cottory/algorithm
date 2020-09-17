package ETC;

import java.io.*;
import java.util.*;

public class BOJ17141 {

	public static class Pair {
		int y,x;
		Pair(int y, int x)
		{
			this.y = y;
			this.x =x;
		}
	}
	
	static final int EMPTY = 0;
	static final int WALL = 1;
	static final int VIRUS_POSTION = 2;
	static final int IMPOSSIBLE = 987654321;
	static final int[] dy = {-1,1,0,0};
	static final int[] dx = {0,0,-1,1};
	
	static int[][] map;
	static int N,M, vSize,answer,emptyCnt;
	static boolean isUsed[];
	static ArrayList<Pair> virusList = new ArrayList<>();
	static LinkedList<Integer> pick = new LinkedList<>();
	
	public static int[][] copy(int[][] src, int[][] dst)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				dst[i][j] = src[i][j];
			}
		}
		
		return dst;
	}
	
	public static boolean isSafe(int y, int x)
	{
		return (0 <= y && y < N && 0 <= x && x < N);
	}
	
	public static int solve()
	{
		int[][] newMap = new int[N][N];
		copy(map,newMap);
		
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (newMap[i][j] == VIRUS_POSTION)
					newMap[i][j] = EMPTY;
			}
		}
		
		//newMap에 대해 pick 정보를 가지고, emptyCnt 갯수 채우기
		
		//bfs
		boolean[][] visited = new boolean[N][N];
		Queue<Pair> q = new LinkedList<>();
		for (Integer idx : pick)
		{
			Pair p = virusList.get(idx);
			q.add(new Pair(p.y,p.x));
			visited[p.y][p.x]= true; 
		}
		
		int cnt = 0;
		int time = 0;
		
		while (q.size() != 0)
		{
			int loopSize = q.size();
			
			if (cnt == emptyCnt)
				break;
			
			for (int loop = 0; loop < loopSize; ++loop)
			{
				Pair now = q.poll();
				
				for (int dir = 0; dir < 4; ++dir)
				{
					int ny = now.y + dy[dir];
					int nx = now.x + dx[dir];
					
					if (isSafe(ny,nx) && !visited[ny][nx] && newMap[ny][nx] == EMPTY)
					{
						visited[ny][nx] = true;
						q.offer(new Pair(ny,nx));
						cnt += 1;
					}
				}
			}
			
			time += 1;
		}
		
		if (cnt == emptyCnt) 
			return time;
		else
			return IMPOSSIBLE;
	}
	
	public static void combination(int idx, int pickCnt)
	{
		if (pickCnt == M)
		{
			//solve
			answer = Math.min(answer, solve());
			return;
		}
		
		if (idx == vSize)
			return;
		
		if (!isUsed[idx])
		{
			isUsed[idx] = true;
			pick.addLast(idx);
			combination(idx+1,pickCnt+1);
			pick.removeLast();
			isUsed[idx] = false;
		}
		
		combination(idx+1,pickCnt);
		return;
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	
		String[] info = br.readLine().split(" ");
		N = Integer.parseInt(info[0]);
		M = Integer.parseInt(info[1]);
		
		map = new int[N][N];
		
		for (int i = 0; i < N; ++i)
		{
			info = br.readLine().split(" ");
			
			for (int j = 0; j < info.length; ++j)
			{
				map[i][j] = Integer.parseInt(info[j]);
				
				if (map[i][j] == VIRUS_POSTION)
				{
					virusList.add(new Pair(i,j));
					emptyCnt += 1;
				}
				else if (map[i][j] == EMPTY)
				{
					emptyCnt += 1;
				}
			}
		}
		
		emptyCnt -= M;
		
		vSize = virusList.size();
		isUsed = new boolean[vSize];
		
		answer = IMPOSSIBLE;
		combination(0,0);
		if (answer == IMPOSSIBLE)
			System.out.println(-1);
		else
			System.out.println(answer);
		
	}
}
