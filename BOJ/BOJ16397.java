import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class BOJ16397 {
	
	public static final int MAX_VAULE = 99999;
	public static Integer N,T,G;
	public static int visited[];
	
	public class Pair {
		String number;
		int time;
		Pair(String number, int time) {
			this.number = number;
			this.time = time;
		}
	}
	
	public String plusOperation(String number) {

		Integer nxtNumber = Integer.parseInt(number);
		nxtNumber += 1;
		if (nxtNumber > MAX_VAULE) return null;
		else return nxtNumber.toString();
	}

	public String multipleOperation(String number) {
		Integer nxtNumber = Integer.parseInt(number);
		nxtNumber *= 2;
		
		if (nxtNumber > MAX_VAULE) return null;
		else {
			String str = nxtNumber.toString();
			int len = str.length();
			
			int minusValue = 1;
			for (int i = 0; i < len-1; ++i) {
				minusValue *= 10;
			}
			
			nxtNumber -= minusValue;
			return nxtNumber.toString();
		}
	}
	
	public int bfs() {
		
		Queue<Pair> q = new LinkedList();
		q.offer(new Pair(N.toString(),0));
		String answer = G.toString();
		visited[N] = 1;
		
		while (!q.isEmpty())
		{
			Pair now = q.poll();
			
			if (now.number.compareTo(answer) == 0) {
				return now.time;
			}
			else if (now.time >= T) {
				continue;
			}
			
			String result = plusOperation(now.number);
			if (result != null) {
				int nxtNumber = Integer.parseInt(result);
				if (visited[nxtNumber] == 0) {
					visited[nxtNumber] = 1;
					q.offer(new Pair(result,now.time+1));
				}
			}
			
			if (Integer.parseInt(now.number) == 0) 
				continue;
			
			result = multipleOperation(now.number);
			if (result != null) {
				int nxtNumber = Integer.parseInt(result);
				if (visited[nxtNumber] == 0) {
					visited[nxtNumber] = 1;
					q.offer(new Pair(result,now.time+1));
				}
			}
		}
		
		return -1;
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line = br.readLine().split(" ");
		
		N = Integer.parseInt(line[0]);
		T = Integer.parseInt(line[1]);
		G = Integer.parseInt(line[2]);
		visited = new int[MAX_VAULE + 1];
		
		BOJ16397 main = new BOJ16397();
		int answer = main.bfs();
		
		if (answer == -1) {
			System.out.println("ANG");
		}
		else {
			System.out.println(answer);
		}
		
		return;
	}
}
