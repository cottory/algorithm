package ETC;

import java.io.*;
import java.util.*;

public class BOJ2493 {

	static class Pair {
		int h, idx;
		Pair(int h , int idx)
		{
			this.h = h;
			this.idx = idx;
		}
	}
	
	static int N;
	static LinkedList<Pair> ls,rs;	//leftStack, rightStack;
	static int[] result;
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		
		ls = new LinkedList<>();
		rs = new LinkedList<>();
		result = new int[N];
		
		String[] topInfo = br.readLine().split(" ");
		
		for (int i = 0; i < topInfo.length; ++i)
		{
			ls.addLast((new Pair(Integer.parseInt(topInfo[i]), i)));
		}
		
		//LS 6 9 5 7 4
		
		//RS
		
		while (!ls.isEmpty())
		{
			Pair leftTop = ls.pollLast();
			
			while (!rs.isEmpty())
			{
				Pair rightTop = rs.peekFirst();
				
				if (leftTop.h >= rightTop.h)
				{
					rs.pollFirst();
					result[rightTop.idx] = leftTop.idx + 1; 
				}
				else
				{
					//leftTop < rightTop
					break;
				}
			}
						
			//leftTop -> rightTop 이동
			rs.addFirst(leftTop);
		}
		
		while (!rs.isEmpty())
		{
			Pair top = rs.pollFirst();
			result[top.idx] = 0;
		}
	
	
		ArrayList<Integer> list = new ArrayList<>();
		
		for (int i = 0; i < N; ++i)
			list.add(result[i]);

		list.stream().forEach( height -> {
			System.out.print(height + " ");
		});
	}
}
