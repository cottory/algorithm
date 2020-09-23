package ETC;

import java.io.*;
import java.util.*;

public class BOJ6198 {

	static int N;
	static LinkedList<Integer> stack = new LinkedList<>();
	static int[] arr;
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		arr = new int[N];
		
		for (int i = 0; i < N; ++i)
		{
			int num = Integer.parseInt(br.readLine());
			arr[i] = num;
		}
		
		long answer = 0;
		for (int i = 0; i < N; ++i)
		{
			int now = arr[i];
			
			while (!stack.isEmpty())
			{
				int tail = stack.peekLast();
				if (tail <= now)
				{
					stack.pollLast();
				}
				else 
				{
					break;
				}
			}
			
			answer += stack.size();
			stack.addLast(now);
		}
		
		System.out.println(answer);
		
	}
}
