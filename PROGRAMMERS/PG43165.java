import java.util.LinkedList;
import java.util.Queue;

class PG43165 {

	public static int N;

	public class Pair {
		int sum, cnt;

		Pair(int sum, int cnt) {
			this.sum = sum;
			this.cnt = cnt;
		}
	}

	public int bfs(int[] numbers, int target) {

		int ret = 0;
		Queue<Pair> q = new LinkedList();
		q.offer(new Pair(0, 0));

		for (int i = 0; i < N; ++i) {
			int num = numbers[i];

			int qSize = q.size();

			while (qSize != 0) {
				Pair now = q.poll();
				q.offer(new Pair(now.sum + num, now.cnt + 1));
				q.offer(new Pair(now.sum - num, now.cnt + 1));
				qSize--;
			}
		}

		while (!q.isEmpty()) {
			Pair now = q.poll();
			if (now.sum == target) {
				ret += 1;
			}
		}

		return ret;
	}

	public int solution(int[] numbers, int target) {
		int answer = 0;
		N = numbers.length;

		answer = bfs(numbers, target);

		return answer;
	}
}