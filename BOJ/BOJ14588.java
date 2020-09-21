package ETC;

import java.io.*;
import java.util.*;

public class BOJ14588 {

	static class Line {
		int left,right;
		
		Line(int l, int r)
		{
			left = l;
			right = r;
		}
	}
	
	static final int INF = 987654321;
	static int N;
	static ArrayList<Line> lines = new ArrayList<>();
	static int[][] dist;
	
	public static boolean isAdjsent(Line arg1, Line arg2)
	{
		if (arg1.right < arg2.left || arg2.right < arg1.left)
			return false;
		else
			return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		dist = new int[N][N];
		for (int i = 0; i < N; ++i)
			Arrays.fill(dist[i], INF);
		
		for (int i = 0; i < N; ++i)
			dist[i][i] = 0;
		
		for (int loop = 0; loop < N; ++loop)
		{
			String[] lineInfo = br.readLine().split(" ");
			int l = Integer.parseInt(lineInfo[0]);
			int r = Integer.parseInt(lineInfo[1]);
			
			lines.add(new Line(l,r));
		}
		
		for (int i = 0; i < lines.size() - 1; ++i)
		{
			for (int j = i + 1; j < lines.size(); ++j)
			{
				if (isAdjsent(lines.get(i), lines.get(j)))
				{
					dist[i][j] = 1;
					dist[j][i] = 1;
				}
			}
		}
		
		//floyd
		for (int mid = 0; mid < N; ++mid)
		{
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if (i==j)
						continue;
					else if (dist[i][j] > dist[i][mid] + dist[mid][j])
					{
						dist[i][j] = dist[i][mid] + dist[mid][j];
						dist[j][i] = dist[i][j];
					}
				}
			}
		}
		
		int query = Integer.parseInt(br.readLine());
		
		for (int loop = 0; loop < query; ++loop)
		{
			String[] info = br.readLine().split(" ");
			int src = Integer.parseInt(info[0]);
			int dst = Integer.parseInt(info[1]);
			src--; dst--;
			
			int result = dist[src][dst];
			if (result == INF)
				System.out.println(-1);
			else
				System.out.println(result);
		}
		
	}
}
