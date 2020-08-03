import java.util.*;

class PG1829 {

	public class Pair {
		int y, x;

		Pair(int y, int x) {
			this.y = y;
			this.x = x;
		}
	}

	public static int N, M;
	public static int dy[] = { -1, 1, 0, 0 };
	public static int dx[] = { 0, 0, -1, 1 };
	public static int visited[][];

	public boolean isSafe(int y, int x) {
		return (0 <= y && y < M && 0 <= x && x < N);
	}

	public int bfs(int[][] picture, int y, int x) {

		Queue<Pair> q = new LinkedList();
		q.offer(new Pair(y, x));
		int block_type = picture[y][x];
		int ret = 1;

		while (!q.isEmpty()) {
			Pair now = q.poll();

			for (int dir = 0; dir < 4; ++dir) {
				int ny = now.y + dy[dir];
				int nx = now.x + dx[dir];

				if (!isSafe(ny, nx))
					continue;
				if (visited[ny][nx] == 1)
					continue;
				if (picture[ny][nx] == block_type) {
					visited[ny][nx] = 1;
					q.offer(new Pair(ny, nx));
					ret += 1;
				}
			}
		}

		return ret;
	}

	public int[] solution(int m, int n, int[][] picture) {
		int numberOfArea = 0;
		int maxSizeOfOneArea = 0;

		M = m;
		N = n;
		visited = new int[m][];
		for (int i = 0; i < m; ++i)
			visited[i] = new int[n];

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (picture[i][j] != 0 && visited[i][j] == 0) {
					numberOfArea += 1;
					visited[i][j] = 1;
					maxSizeOfOneArea = Math.max(maxSizeOfOneArea, bfs(picture, i, j));
				}
			}
		}

		int[] answer = new int[2];
		answer[0] = numberOfArea;
		answer[1] = maxSizeOfOneArea;
		return answer;
	}
}