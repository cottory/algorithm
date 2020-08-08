import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class BOJ11399 {

	public static int N;
	public static int[] arr;
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(bufferedReader.readLine());
		arr = new int[N];
		
		String[] times = bufferedReader.readLine().split(" ");
		
		for (int i = 0; i < times.length; ++i)
		{
			arr[i] = Integer.parseInt(times[i]);			
		}
		
		Arrays.sort(arr);
		
		int ans = 0;
		int waitingTime = 0;
		for (int time : arr)
		{
			ans += (waitingTime + time);
			waitingTime += time;
		}
		
		System.out.println(ans);
		
	}
}
