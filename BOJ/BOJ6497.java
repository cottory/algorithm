package MST;

import java.io.*;
import java.util.*;

public class BOJ6497 {

	static class Tuple implements Comparable<Tuple> {
		int house1, house2, cost;

		public Tuple(int house1, int house2, int cost) {
			super();
			this.house1 = house1;
			this.house2 = house2;
			this.cost = cost;
		}
		
		@Override
		public int compareTo(Tuple o) {
			if (this.cost < o.cost) return -1;
			else if (this.cost == o.cost) return 0;
			else return 1;
		}
	}
	
	static int totalCnt, M,N;	//집의 수 M, 길의 수 N
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
		int result = 0;
		int edgeCount = 0;
		
		while (edgeCount < M-1)
		{
			while (!pq.isEmpty())
			{
				Tuple now = pq.poll();
				
				int c1 = find(now.house1);
				int c2 = find(now.house2);
				
				if (c1 != c2)
				{
					union(c1,c2);
					result += now.cost;
					edgeCount += 1;
				}
			}
		}
		
		return result;
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		while (true)
		{
			String[] nodeInfo = br.readLine().split(" ");
			M = Integer.parseInt(nodeInfo[0]);
			N = Integer.parseInt(nodeInfo[1]);
			
			if (M == 0 && N == 0)
			{
				break;
			}
			
			totalCnt = 0;
			pq.clear();
			parent = new int[M];
			for (int i = 0; i < M; ++i)
				parent[i] = i;
			
			for (int loop = 0; loop < N; ++loop)
			{
				String[] edgeInfo = br.readLine().split(" ");
				int h1 = Integer.parseInt(edgeInfo[0]);
				int h2 = Integer.parseInt(edgeInfo[1]);
				int cost = Integer.parseInt(edgeInfo[2]);
				
				pq.offer(new Tuple(h1,h2,cost));
				totalCnt += cost;
			}
			
			int answer = (totalCnt - kruskal());
			System.out.println(answer);
		}
		
	}
}
