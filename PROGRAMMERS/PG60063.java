import java.util.*;

class PG60063 {
    
	public static final int UP = 0;
	public static final int RIGHT = 1;
	public static final int DOWN = 2;
	public static final int LEFT = 3;
	
	public static final int[] DY = {-1,0,1,0};
	public static final int[] DX = {0,1,0,-1};
	public static final int[] RY = {-1,-1,1,1};	//rotate_y
	public static final int[] RX = {-1,1,-1,1};
	public static final int BLOCK = 1;
	public static final int VISITED = 1;
	public static final int DIR_SIZE = 4;
	public static int boardSize;
	public static int visited[][][];
	
	public class Pair {
		int y, x;
		
		Pair() {
			this.y = 0;
			this.x = 0;
		}
		Pair(int y, int x) {
			this.y = y;
			this.x = x;
		}
	}
	public class Token {
		Pair head, tail;
		int dir, time;
		Token(Pair head, int dir, int time) {
			this.head = new Pair();
			this.tail = new Pair();
			
			this.head.y = head.y;
			this.head.x = head.x;
			
			this.dir = dir;
			this.time = time;
			
			this.tail.y = head.y + DY[dir];
			this.tail.x = head.x + DX[dir];
		}
	}
	
	public boolean isAdj(Pair head, Pair tail) {
		
		int distY = Math.abs(head.y - tail.y);
		int distX = Math.abs(head.x - tail.x);
		
		if (distY == 0 && distX == 1) return true;
		else if (distX == 0 && distY == 1) return true;
		else return false;
	}
	
	public int getDirection(final Pair head, final Pair tail) {
		
		if (head.y - tail.y == 1) return UP;
		else if (tail.y - head.y == 1) return DOWN;
		else if (head.x - tail.x == 1) return LEFT;
		else return RIGHT;
	}
	
	public Pair getTailPosition(final Pair head_position, final int dir) {
		return new Pair(head_position.y + DY[dir], head_position.x + DX[dir]);
	}
	
	public boolean isSafe(int y, int x) {
		return (0 <= y && y < boardSize && 0 <= x && x < boardSize);
	}

	public int bfs(int[][] board) {
		int ret = 987654321;
		Queue<Token> q = new LinkedList<Token>();
		q.offer(new Token(new Pair(0,0),RIGHT,0));
		q.offer(new Token(new Pair(0,1),LEFT,0));
		visited[RIGHT][0][0] = VISITED;
		visited[LEFT][0][1] = VISITED;
		
		while (!q.isEmpty())
		{
			Token now = q.poll();
			
			if ((now.head.y == boardSize-1 && now.head.x == boardSize - 1) ||
					(now.tail.y == boardSize-1 && now.tail.x == boardSize - 1))
			{
				ret = Math.min(ret, now.time);
			}
			else 
			{
				//기존 방향 유지하고 4 방향 이동
				for (int dir = 0; dir < DIR_SIZE; ++dir)
				{
					Pair nxtHead, nxtTail;
					int ny = now.head.y + DY[dir];
					int nx = now.head.x + DX[dir];
					nxtHead = new Pair(ny,nx);
					nxtTail = getTailPosition(nxtHead,now.dir);
					
					if (!isSafe(nxtHead.y,nxtHead.x) || !isSafe(nxtTail.y,nxtTail.x)) continue;
					if (board[nxtHead.y][nxtHead.x] == BLOCK || board[nxtTail.y][nxtTail.x] == BLOCK) continue;
					if (visited[now.dir][nxtHead.y][nxtHead.x] == VISITED) continue;
					
					visited[now.dir][nxtHead.y][nxtHead.x] = VISITED;
					q.offer(new Token(nxtHead, now.dir, now.time + 1));
				}
				
				//HEAD 기준으로 TAIL 회전
				for (int dir = 0; dir < DIR_SIZE; ++dir)
				{
					Pair nxtHead;
					int ny = now.tail.y + DY[dir];
					int nx = now.tail.x + DX[dir];
					nxtHead = new Pair(ny,nx);

					if (!isSafe(ny,nx)) continue;
					if (board[ny][nx] == BLOCK) continue;
					if (nxtHead.y == now.head.y && nxtHead.x == now.head.x) continue;
					
					for (int i = 0; i < DIR_SIZE; ++i)
					{
						int cy = now.tail.y + RY[i];
						int cx = now.tail.x + RX[i];
						
						if (!isSafe(cy,cx)) continue;
						if (board[cy][cx] == BLOCK) continue;
						
						Pair candidate = new Pair(cy,cx);
						int adjCnt = 0;
						
						if (isAdj(candidate,now.head)) adjCnt += 1;
						if (isAdj(candidate,nxtHead)) adjCnt += 1;
						
						if (adjCnt < 2) continue;
						
						int nxtDir = getDirection(now.tail, nxtHead);
						if (visited[nxtDir][now.tail.y][now.tail.x] == VISITED) continue;
						
						visited[nxtDir][now.tail.y][now.tail.x] = VISITED;
						q.offer(new Token(now.tail, nxtDir, now.time + 1));
					}
				}
				
				//TAIL 기준으로 HEAD 회전
				for (int dir = 0; dir < DIR_SIZE; ++dir)
				{
					Pair nxtTail;
					int ny = now.head.y + DY[dir];
					int nx = now.head.x + DX[dir];
					nxtTail = new Pair(ny,nx);

					if (!isSafe(ny,nx)) continue;
					if (board[ny][nx] == BLOCK) continue;
					if (nxtTail.y == now.tail.y && nxtTail.x == now.tail.x) continue;
					
					for (int i = 0; i < DIR_SIZE; ++i)
					{
						int cy = now.head.y + RY[i];
						int cx = now.head.x + RX[i];
						
						if (!isSafe(cy,cx)) continue;
						if (board[cy][cx] == BLOCK) continue;
						
						Pair candidate = new Pair(cy,cx);
						int adjCnt = 0;
						
						if (isAdj(candidate,now.tail)) adjCnt += 1;
						if (isAdj(candidate,nxtTail)) adjCnt += 1;
						
						if (adjCnt < 2) continue;
						
						int nxtDir = getDirection(now.head, nxtTail);
						if (visited[nxtDir][now.head.y][now.head.x] == VISITED) continue;
						
						visited[nxtDir][now.head.y][now.head.x] = VISITED;
						q.offer(new Token(now.head, nxtDir, now.time + 1));
					}
				}
			}
		}
		
		return ret;
	}
	
	public int solution(int[][] board) {
        int answer = 0;
        boardSize = board.length;
        visited = new int[DIR_SIZE][boardSize][boardSize];
                
        answer = bfs(board);
        return answer;
    }
	
}
