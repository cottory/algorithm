package ETC;

import java.util.*;
import java.io.*;

public class BOJ18223 {

	static class Pair implements Comparable<Pair> {
		int node, weight;
		
		Pair(int node, int weight)
		{
			this.node = node;
			this.weight = weight;
		}
		
		@Override
		public int compareTo(Pair o) {
			if (this.weight < o.weight) return -1;
			else if (this.weight == o.weight) return 0;
			else return 1;
		}
	}
	
	static final int INF = 987654321;
	
	static int V,E,P;
	static ArrayList<Pair>[] graph;
	static ArrayList<Integer>[] before;
	
	public static boolean bfs(int node)
	{		
		Queue<Integer> q = new LinkedList<>();
		boolean[] visited = new boolean[V];
		
		visited[node] = true;
		q.offer(new Integer(node));
		
		while (!q.isEmpty())
		{
			Integer now = q.poll();
			
			for (Integer nxt : before[now])
			{
				if (visited[nxt] == false)
				{
					visited[nxt] = true;
					q.offer(nxt);
				}
			}
		}
		
		if (visited[P-1])
			return true;
		else 
			return false;
	}
	
	public static void djikstra()
	{
		int[] dist = new int[V];
		Arrays.fill(dist, INF);
		
		PriorityQueue<Pair> pq = new PriorityQueue<>();
		
		dist[0] = 0;
		pq.offer(new Pair(0,0));
		
		while (!pq.isEmpty())
		{
			Pair now = pq.poll();
			
			if (now.weight > dist[now.node]) 
				continue;
			
			for (Pair nxt : graph[now.node])
			{
				int nxtNode = nxt.node;
				int nxtWeight = nxt.weight;
				
				if (dist[nxtNode] > now.weight + nxtWeight)
				{
					dist[nxtNode] = now.weight + nxtWeight;
					before[nxtNode].clear();
					before[nxtNode].add(now.node);
					pq.offer(new Pair(nxtNode,dist[nxtNode]));
				}
				else if (dist[nxtNode] == now.weight + nxtWeight)
				{
					before[nxtNode].add(now.node);
				}
			}
		}
		
		return;
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String[] info = br.readLine().split(" ");
		
		V = Integer.parseInt(info[0]);
		E = Integer.parseInt(info[1]);
		P = Integer.parseInt(info[2]);
		
		graph = new ArrayList[V];
		for (int i = 0; i < V; ++i)
		{
			graph[i] = new ArrayList<>();
		}
		
		before = new ArrayList[V];
		for (int i = 0; i < V; ++i)
		{
			before[i] = new ArrayList<>();
		}
		
		for (int i = 0; i < E; ++i)
		{
			String[] edge = br.readLine().split(" ");
			int src, dst, weight;
			src = Integer.parseInt(edge[0]);
			dst = Integer.parseInt(edge[1]);
			weight = Integer.parseInt(edge[2]);
			src--;
			dst--;
			graph[src].add(new Pair(dst,weight));
			graph[dst].add(new Pair(src,weight));
		}
		
		//djikstra
		djikstra();
		
		//bfs
		boolean isVisited = bfs(V-1);
		if (isVisited)
		{
			System.out.println("SAVE HIM");
		}
		else
		{
			System.out.println("GOOD BYE");
		}
	}
}
