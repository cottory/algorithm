import java.io.*;
import java.util.*;

public class Main {

	static final int INF = 987654321;
	static int N,ans;
	static int[][] graph;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String info = br.readLine();
		
		N = Integer.parseInt(info);
		ans = INF;
		graph = new int[N][N];
		
		for (int loop = 0; loop < N-1; ++loop)
		{
			String[] edges = br.readLine().split(" ");
			int src = Integer.parseInt(edges[0]);
			int dst = Integer.parseInt(edges[1]);
			src--; dst--;
			graph[src][dst] = 1;
		}
		
		for (int mid = 0; mid < N; ++mid)
		{
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if (graph[i][mid] == 1 && graph[mid][j] == 1)
					{
						graph[i][j] = 1;
					}
				}
			}
		}
		
		for (int dst = 0; dst < N; ++dst)
		{
			int cnt = 0;
			
			for (int src = 0; src < N; ++src)
			{
				if (graph[src][dst] == 1)
				{
					cnt += 1;
				}
			}
			
			if (cnt == N-1)
			{
				ans = Math.min(ans, dst);
			}
		}
		
		if (INF == ans)
		{
			System.out.println(-1);
		}
		else 
		{
			System.out.println(ans+1);
		}
		
	}
}