package FINAL;

import java.util.*;
import java.io.*;

public class BOJ16918 {
	
	public static class Pair {
		int y,x;
		Pair(int y, int x) {
			this.y = y;
			this.x = x;
		}
	}
	
	public static final int[] dy = {-1,1,0,0};
	public static final int[] dx = {0,0,-1,1};
	public static final int EMPTY = -1;
	public static final int BOMB = 3;
	public static int R,C,N;
	public static int[][] board;
	
	static boolean isSafe(int y, int  x)
	{
		return (0 <= y && y < R && 0 <= x && x < C);
	}
	
	static void printBoard()
	{
		for (int i = 0; i < board.length; ++i)
		{
			for (int j = 0; j < board[0].length; ++j)
			{
				if (board[i][j] == EMPTY)
				{
					System.out.print('.');
				}
				else
				{
					System.out.print('O');
				}
			}
			System.out.println();
		}
	}
	
	static void bbang()
	{
		ArrayList<Pair> candidate = new ArrayList<>();
		
		for (int i = 0; i < board.length; ++i)
		{
			for (int j = 0; j < board[0].length; ++j)
			{
				if (board[i][j] == 0)
				{
					candidate.add(new Pair(i,j));
					board[i][j] = EMPTY;
				}
			}
		}
		
		for (Pair p : candidate)
		{
			for (int dir = 0; dir < 4; ++dir)
			{
				int ny = p.y + dy[dir];
				int nx = p.x + dx[dir];
				
				if (isSafe(ny,nx))
				{
					board[ny][nx] = EMPTY;
				}
			}
		}
	}
	
	static void timePassed(int val)
	{
		for (int i = 0; i < board.length; ++i)
		{
			for (int j = 0; j < board[0].length; ++j)
			{
				if (board[i][j] != EMPTY)
				{
					board[i][j] = Math.max(0, board[i][j] - 1);
				}
			}
		}
	}
	
	static void setBomb()
	{
		for (int i = 0; i < board.length; ++i)
		{
			for (int j = 0; j < board[0].length; ++j)
			{
				if (board[i][j] == EMPTY)
				{
					board[i][j] = BOMB;
				}
			}
		}
		return;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String[] info = br.readLine().split(" ");
		
		R = Integer.parseInt(info[0]);
		C = Integer.parseInt(info[1]);
		N = Integer.parseInt(info[2]);
		board = new int[R][C];
		
		for (int loop = 0; loop < R; ++loop)
		{
			String line = br.readLine();
			
			for (int j = 0; j < C; ++j)
			{
				char val = line.charAt(j);
				if (val == '.')
				{
					board[loop][j] = EMPTY;
				}
				else
				{
					board[loop][j] = BOMB;
				}
			}
		}
		
		N--;
		timePassed(1);
		
		if (N <= 0)
		{
			printBoard();
		}
		else
		{
			//폭탄 설치
			while (true)
			{
				//폭탄 설치
				N--;
				timePassed(1);
				setBomb();
				
				if (N == 0)
					break;
				
				N--;
				timePassed(1);
				
				//3초 지난 폭탄 모두 폭발
				bbang();
				
				if (N == 0)
					break;
			}
			
			printBoard();
		}
	}
}
