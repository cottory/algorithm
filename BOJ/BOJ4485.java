package ETC;

import java.io.*;
import java.util.*;

public class BOJ4485 {

	public static class Edge implements Comparable<Edge> {
		int y,x,cost;
		Edge(int y, int x, int cost)
		{
			this.y = y;
			this.x = x;
			this.cost = cost;
		}
		
		@Override
		public int compareTo(Edge o) {
			if (this.cost < o.cost) return -1;
			else if (this.cost == o.cost) return 0;
			else return 1;
		}
	}

	static int N;
	static final int[] dy = {-1,1,0,0};
	static final int[] dx = {0,0,-1,1};
	static final int IMPOSSIBLE = 987654321;
	
	static boolean safe(int y, int x)
	{
		return (0 <= y && y < N && 0 <= x && x < N);
	}
	public static int djikstra(int[][] graph)
	{
		int[][] dist = new int[N][N];
		
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				dist[i][j] = IMPOSSIBLE;
			}
		}
			
		dist[0][0] = graph[0][0];
		PriorityQueue<Edge> pq = new PriorityQueue<>();
		pq.offer(new Edge(0,0,graph[0][0]));
		
		while (!pq.isEmpty())
		{
			Edge now = pq.poll();
			
			if (dist[now.y][now.x] < now.cost)
				continue;
			
			for (int dir = 0; dir < 4; ++dir)
			{
				int ny = now.y + dy[dir];
				int nx = now.x + dx[dir];
				
				if (safe(ny,nx))
				{
					if (dist[ny][nx] > now.cost + graph[ny][nx])
					{
						dist[ny][nx] = now.cost + graph[ny][nx];
						pq.offer(new Edge(ny,nx,dist[ny][nx]));
					}
				}
			}
		}
		
		return dist[N-1][N-1];
	}
	
	public static void main(String[] args) throws IOException {
	
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int test_case = 0;
		while (true)
		{
			test_case++;
			
			N = Integer.parseInt(br.readLine());
			
			if (N == 0)
				break;
			
			int[][] graph = new int[N][N];
			
			for (int i = 0; i < N; ++i)
			{
				String[] info = br.readLine().split(" ");
				for (int j = 0; j < info.length; ++j)
				{
					graph[i][j] = Integer.parseInt(info[j]);
				}
			}
			
			System.out.println("Problem " + test_case + ": "+ djikstra(graph));
			
		}
	}
}
