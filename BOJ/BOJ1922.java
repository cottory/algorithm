package MST;

import java.io.*;
import java.util.*;

public class BOJ1922 {
	
	static class Tuple implements Comparable<Tuple> {
		
		int src,dst,cost;

		public Tuple(int src, int dst, int cost) {
			super();
			this.src = src;
			this.dst = dst;
			this.cost = cost;
		}
		
		@Override
		public int compareTo(Tuple arg0) {
			if (this.cost < arg0.cost) return -1;
			else if (this.cost == arg0.cost) return 0;
			else return 1;
		}
	}
	
	static int N,M;
	static int[] parent;
	static PriorityQueue<Tuple> pq = new PriorityQueue<>();

	static int find(int node) {
		if (parent[node] == node) return node;
		else return parent[node] = find(parent[node]);
	}
	
	static void union(int c1, int c2) {
		parent[c2] = c1;
		return;
	}
	
	static int kruskal() {
		int totalCost = 0;
		int edgeCount = 0;
		
		while (edgeCount < N-1)
		{
			while (!pq.isEmpty())
			{
				Tuple now = pq.poll();
				
				int c1 = find(now.src);
				int c2 = find(now.dst);
				
				if (c1 != c2) 
				{
					union(c1,c2);
					totalCost += now.cost;
					edgeCount += 1;
				}
			}
		}
		
		return totalCost;
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		M = Integer.parseInt(br.readLine());
		
		for (int i = 0; i < M; ++i)
		{
			String[] edge = br.readLine().split(" ");
			int src,dst,cost;
			
			src = Integer.parseInt(edge[0]);
			dst = Integer.parseInt(edge[1]);
			cost = Integer.parseInt(edge[2]);
			src--; dst--;
			
			pq.add(new Tuple(src,dst,cost));
		}
		
		parent = new int[N];
		for (int i = 0; i < N; ++i)
		{
			parent[i] = i;
		}
		
		System.out.println(kruskal());
		
	}
}
