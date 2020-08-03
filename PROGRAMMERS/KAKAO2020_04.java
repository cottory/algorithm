import java.util.*;

class KAKAO2020_04 {
    
	public static final int UP = 0;
	public static final int RIGHT = 1;
	public static final int DOWN = 2;
	public static final int LEFT = 3;
	public static final int DIR_SIZE = 4;
	
	public static int N;
	public static final int IMPOSSIBLE = 987654321;
	public static int visited[][][];
	
	public static int dy[] = {-1,0,1,0};
	public static int dx[] = {0,1,0,-1};
	
	public class Token {
		int y,x,dir,cost;
		Token (int y, int x, int dir, int cost) 
		{
			this.y = y;
			this.x = x ;
			this.dir = dir;
			this.cost = cost;
		}
	}
	
	public boolean isSafe(int y, int x) {
		return (0 <= y && y < N && 0 <= x && x < N);
	}
	
	public int bfs(int[][] board) {
	
		int ret = IMPOSSIBLE;
		Queue<Token> q = new LinkedList();
		
		if (board[0][1] == 0) {
			q.offer(new Token(0,1,RIGHT,100));
		}
		if (board[1][0] == 0) {
			q.offer(new Token(1,0,DOWN,100));
		}
				
		while (!q.isEmpty())
		{
			Token now = q.poll();
			
			if (now.y == 1 && now.x == 1 && now.dir == RIGHT) {
				System.out.println("Hello");
			}
			
			if (now.y == N-1 && now.x == N-1)
			{
				ret = Math.min(ret, now.cost);
			}
			else
			{
				for (int dir = 0; dir < DIR_SIZE; ++dir)
				{
					int ny = now.y + dy[dir];
					int nx = now.x + dx[dir];
					
					if (!isSafe(ny,nx)) continue;
					if (board[ny][nx] == 1) continue;
					if ((dir + 2) % DIR_SIZE == now.dir) continue;
					
					if (dir == now.dir)
					{
						int nxtCost = now.cost + 100;
						if (visited[dir][ny][nx] > nxtCost)
						{
							visited[dir][ny][nx] = nxtCost;
							q.offer(new Token(ny,nx,dir,nxtCost));
						}
					}
					else 
					{
						int nxtCost = now.cost + 600;
						
						if (visited[dir][ny][nx] > nxtCost)
						{
							visited[dir][ny][nx] = nxtCost;
							q.offer(new Token(ny,nx,dir,nxtCost));
						}
					}
				}
			}
		}
		
		return ret;
	}
	
	public int solution(int[][] board) {
        int answer = 0;
        N = board.length;
        visited = new int[DIR_SIZE][N][N];
        
        for (int i = 0; i < DIR_SIZE; ++i) 
        {
        	for (int j = 0; j < N; ++j) 
        	{
        		for (int k = 0; k < N; ++k) {
        			visited[i][j][k] = IMPOSSIBLE;
        		}
        	}
        }
        
        answer = bfs(board);
        return answer;
    }
}