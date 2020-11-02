package FINAL;

import java.util.*;
import java.io.*;

public class BOJ10159 {

	static final int NOTHING = 0;
	static final int HEAVY = 1;
	static final int LIGHT = 2;
	static int N,M;
	static int[][] graph;
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		M = Integer.parseInt(br.readLine());
		graph = new int[N][N];
		
		for (int i = 0; i < M; ++i)
		{
			String[] info = br.readLine().split(" ");
			int src = Integer.parseInt(info[0]);
			int dst = Integer.parseInt(info[1]);
			src--; dst--;
			graph[src][dst] = HEAVY;
			graph[dst][src] = LIGHT;
		}
		
		for (int mid = 0; mid < N; ++mid)
		{
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if (graph[i][mid] == HEAVY && graph[mid][j] == HEAVY)
					{
						graph[i][j] = HEAVY;
					}
					else if (graph[i][mid] == LIGHT && graph[mid][j] == LIGHT)
					{
						graph[i][j] = LIGHT;
					}
				}
			}
		}
		
		for (int i = 0; i < N; ++i)
		{
			int nothingCnt = 0;
			for (int j = 0; j < N; ++j)
			{
				if (i != j && graph[i][j] == NOTHING)
				{
					nothingCnt += 1;
				}
			}
			System.out.println(nothingCnt);
		}
		
	}
}
