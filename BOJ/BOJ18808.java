package ETC;

import java.io.*;
import java.util.*;

public class BOJ18808 {

	static class Sticker {
		int h,w;
		int[][][] sticker = new int[4][][];
		
		Sticker(int h, int w, int[][] sticker)
		{
			this.h = h;
			this.w = w;
			for (int i = 0; i < 4; ++i)
			{
				if (i % 2 == 0)
				{
					this.sticker[i] = new int[h][w];
				}
				else
				{
					this.sticker[i] = new int[w][h];
				}
			}
			
			this.sticker[0] = sticker;
			
			rotate(this.sticker[0],this.sticker[1]);			
			rotate(this.sticker[1],this.sticker[2]);				
			rotate(this.sticker[2],this.sticker[3]);
		}
		
		public void rotate(int[][] before, int[][] after)
		{
			int h = before.length;
			int w = before[0].length;
			
			for (int i = 0; i < h; ++i)
			{
				for (int j = 0; j < w; ++j)
				{
					after[j][(h-1)-i] = before[i][j];
				}
			}
		}
	}
	
	static final int NOT_USED = 0;
	static final int USED = 1;
	static int N,M,K;
	static int[][] paper;
	static ArrayList<Sticker> stickers = new ArrayList<>();
	
	public static boolean isSafe(int y, int x)
	{
		return (0 <= y && y < N && 0 <= x && x < M);
	}
	
	public static void setSticker(int[][] sticker, int sy, int sx)
	{
		int h = sticker.length;
		int w = sticker[0].length;
		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < w; ++x)
			{
				if (sticker[y][x] == USED)
				{
					paper[sy+y][sx+x] = USED;
				}
			}
		}
	}
	
	public static boolean isPossible2Stick(int[][] sticker, int sy, int sx)
	{
		int h = sticker.length;
		int w = sticker[0].length;
		
		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < w; ++x)
			{
				if (!isSafe(y+sy,x+sx))
				{
					return false;
				}
				else if (sticker[y][x] == USED && paper[y+sy][x+sx] == USED)
				{
					return false;
				}
			}
		}
		
		return true;
	}
	
	public static void StickingSticker()
	{
		//
		for (Sticker s : stickers)
		{
			for (int loop = 0; loop < 4; ++loop)
			{
				boolean isSticked = false;
				int[][] nowSticker = s.sticker[loop];
				
				int idx = 0;
				while (idx < N*M)
				{
					int y = idx / M;
					int x = idx % M;
					if (isPossible2Stick(nowSticker,y,x))
					{
						isSticked = true;
						setSticker(nowSticker,y,x);
						break;
					}
					
					idx++;
				}
				
				if (isSticked)
				{
					break;
				}
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String[] info = br.readLine().split(" ");
		
		N = Integer.parseInt(info[0]);
		M = Integer.parseInt(info[1]);
		K = Integer.parseInt(info[2]);
		
		paper = new int[N][M];
		
		for (int loop = 0; loop < K; ++loop)
		{
			String[] stickerInfo = br.readLine().split(" ");
			int h = Integer.parseInt(stickerInfo[0]);
			int w = Integer.parseInt(stickerInfo[1]);
			int[][] newSticker = new int[h][w];
			
			for (int i = 0; i < h; ++i)
			{
				String[] width = br.readLine().split(" ");
				for (int j = 0; j < w; ++j)
				{
					int num = Integer.parseInt(width[j]);
					newSticker[i][j] = num;
				}
			}
			
			Sticker sticker = new Sticker(h, w, newSticker);
			stickers.add(sticker);
		}
		
		//종이에 붙이기
		StickingSticker();
		
		int answer = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (paper[i][j] == USED)
				{
					answer += 1;
				}
			}
		}
		
		System.out.println(answer);
	}

}
