import java.util.Stack;

class PG12909 {
	boolean solution(String s) {
		boolean answer = true;

		Stack<Character> stack = new Stack();

		for (int i = 0; i < s.length(); ++i) {
			if (stack.isEmpty() && s.charAt(i) == ')') {
				answer = false;
				break;
			} else if (s.charAt(i) == '(') {
				stack.add('(');
			} else {
				stack.pop();
			}
		}

		if (!stack.isEmpty()) {
			answer = false;
		}

		return answer;
	}
}