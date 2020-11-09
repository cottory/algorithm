package FINAL;

import java.io.*;
import java.util.*;

public class BOJ1956 {

	static final int IMP = 987654321;
	static int V, E, ans;
	static int[][] dist;
	
	public static void floyd() {
		
		for (int mid = 0; mid < V; ++mid) 
		{
			for (int i = 0; i < V; ++i)
			{
				for (int j = 0; j < V; ++j)
				{
					if (dist[i][mid] != IMP && dist[mid][j] != IMP)
					{
						dist[i][j] = Math.min(dist[i][j], dist[i][mid] + dist[mid][j]);
					}
				}
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String[] graphInfo = br.readLine().split(" ");
		
		V = Integer.parseInt(graphInfo[0]);
		E = Integer.parseInt(graphInfo[1]);
		
		dist = new int[V][V];
		
		for (int i = 0; i < V; ++i)
		{
			Arrays.fill(dist[i], IMP);
		}
		
		for (int loop = 0; loop < E; ++loop)
		{
			String[] edgeInfo = br.readLine().split(" ");
			int src = Integer.parseInt(edgeInfo[0]);
			int dst = Integer.parseInt(edgeInfo[1]);
			int weight = Integer.parseInt(edgeInfo[2]);
			src--;
			dst--;
			dist[src][dst] = weight;
		}
		
		floyd();
		
		ans = IMP;
		for (int node = 0; node < V; ++node)
		{
			ans = Math.min(ans, dist[node][node]);
		}
		
		if (ans == IMP)
		{
			System.out.println(-1);
		}
		else
		{
			System.out.println(ans);
		}
		
	}
}
