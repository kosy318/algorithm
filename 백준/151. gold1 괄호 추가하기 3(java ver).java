package naverFinancial;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;

// https://goldenriver42.tistory.com/158
// https://velog.io/@timointhebush/%EB%B0%B1%EC%A4%80-16639%EB%B2%88-%EA%B4%84%ED%98%B8-%EC%B6%94%EA%B0%80%ED%95%98%EA%B8%B0-3-Python
public class Solution {
	
	static class Value{
		int minVal;
		int maxVal;
		
		public Value(int minVal, int maxVal) {
			this.minVal = minVal;
			this.maxVal = maxVal;
		}
	}
	
	static int N;
	static int[] nums;
	static char[] op;
	
	// Dp[i][j] : i~j구간 계산 값
	static int[][] maxDp = new int[20][20];
	static int[][] minDp = new int[20][20];
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		String formula = br.readLine();
		
		nums = new int[N/2 +1];
		op = new char[N/2];

		// 숫자와 op 분리
		for(int i=0; i<N; i++) {
			if(i%2 == 0) nums[i/2] = Integer.parseInt(Character.toString(formula.charAt(i)));
			else op[i/2] = formula.charAt(i);
		}
		
		// check
//		System.out.println(Arrays.toString(nums));
//		System.out.println(Arrays.toString(op));

		for(int interval=0; interval<nums.length; interval++) {
			for(int i=0; i<nums.length && i+interval<nums.length; i++) {
				// 범위 체크
//				System.out.println(i + " ~ " + (i+interval));
				if(interval == 0) {
					minDp[i][i+interval] = nums[i];
					maxDp[i][i+interval] = nums[i];
				}else if(interval == 1) {
					minDp[i][i+interval] = calculate(nums[i], nums[i+interval], op[i]);
					maxDp[i][i+interval] = calculate(nums[i], nums[i+interval], op[i]);
				}else {
					int[] result = calDp(i, i+interval); // i부터 j까지 계싼결과 min, max 구하기
					minDp[i][i+interval] = result[0];
					maxDp[i][i+interval] = result[1];
				}
			}
		}
		
		System.out.println(maxDp[0][nums.length-1]);
	}
	
	// i부터 j까지 계싼결과 min, max 구하기
	private static int[] calDp(int start, int end) {
		ArrayList<Integer> results = new ArrayList<>();
		
		for(int i=start; i<end; i++) {
			results.add(calculate(minDp[start][i], minDp[i+1][end], op[i]));
			results.add(calculate(minDp[start][i], maxDp[i+1][end], op[i]));
			results.add(calculate(maxDp[start][i], minDp[i+1][end], op[i]));
			results.add(calculate(maxDp[start][i], maxDp[i+1][end], op[i]));
		}
		
		Collections.sort(results);
		
		//check
//		System.out.println(results);
		
		return new int[]{results.get(0), results.get(results.size()-1)};
	}

	public static int calculate(int num1, int num2, char op) {
		int result = 0;
		switch(op) {
		case '+':
			result = num1+num2;
			break;
		case '-':
			result = num1-num2;
			break;
		case '*':
			result = num1*num2;
			break;
		}
		
		return result;
	}

}
