import java.io.*;
import java.util.*;

public class BOJ5014 {

	static int F,S,G,U,D,MAX_FLOOR = 1000000;
	static int visited[];
	static int dir[] = {0,0};
	
	public static class Pair {
		int floor, time;
		Pair(int floor, int time)
		{
			this.floor = floor;
			this.time = time;
		}
	}
	
	public static int bfs(int st, int en) {
		
		int ret = -1;
		Queue<Pair> q = new LinkedList<>();
		q.offer(new Pair(st,0));
		visited[st] = 1;
		
		while (!q.isEmpty())
		{
			Pair now = q.poll(); 
			
			if (now.floor == en) 
			{
				ret = now.time;
				break;
			}
			
			for (int loop = 0; loop < dir.length; ++loop)
			{
				int nxt = now.floor + dir[loop];
				
				if (nxt < 1 || nxt > F) continue;
				if (visited[nxt] == 1) continue;
				
				visited[nxt] = 1;
				q.offer(new Pair(nxt,now.time + 1));
			}
			
		}
		
		return ret;
	}
	public static void main(String[] args) throws IOException
	{
		BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
		
		String[] argument = bufferedReader.readLine().split(" ");
		
		F = Integer.parseInt(argument[0]);
		S = Integer.parseInt(argument[1]);
		G = Integer.parseInt(argument[2]);
		U = Integer.parseInt(argument[3]);
		D = Integer.parseInt(argument[4]);  
		
		int ans;
		visited = new int[MAX_FLOOR + 5];
		dir[0] = U;
		dir[1] = -D;
		ans = bfs(S,G);
		if (ans == -1) {
			System.out.println("use the stairs");
		}
		else {
			System.out.println(ans);
		}
	}
}
