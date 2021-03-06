import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Main {

	/*Checkpoint 1
	public static void main(String[] args) {
		File file = new File("input.txt");
		try {
			Scanner in = new Scanner(file);
			ArrayList<Integer> nums = new ArrayList<Integer>();
			String input;
			int n;
			while (true) {
				input = in.nextLine();
				n = Integer.parseInt(input);
				nums.add(n);
				if (!in.hasNextLine()) {
					break;
				}
			}
			nums.add(0);
			Collections.sort(nums);
			nums.add(nums.get(nums.size()-1) + 3);

			int threeCounter = 0;
			int oneCounter = 0;

			int i = 0;
			for (; i < nums.size() - 1; ++i) {
				if (nums.get(i+1) - nums.get(i) > 3) {
					break;
				} else if (nums.get(i+1) - nums.get(i) == 3) {
					++threeCounter;
				} else if (nums.get(i+1) - nums.get(i) == 1) {
					++oneCounter;
				}
			}
			System.out.println(threeCounter*oneCounter);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}*/

	//Checkpoint 2
	public static long numSolution(ArrayList<Integer> arr) {
		ArrayList<Long> paths = new ArrayList<Long>();
		long begin = 1;
		paths.add(begin);

		int index = 1;
		for (int i = 1; index < arr.size(); ++i) {
			long total = 0;
			if (arr.get(index) == i) {
				if (i-3 >= 0)
					total += paths.get(i-3);
				if (i-2 >= 0)
					total += paths.get(i-2);
				total += paths.get(i-1);
				++index;
			}
			paths.add(total);
		}
		return paths.get(paths.size()-1);
	}

/*  Highly Inefficient due to repeated calculations
	public static long numSolution(ArrayList<Integer> arr, int index) {
		if (index >= arr.size() - 2)
			return 1;

		int odiff = arr.get(index+1) - arr.get(index);
		int tdiff = -1;
		int thdiff = -1;

		if (index + 2 < arr.size()-1)
			tdiff = arr.get(index + 2) - arr.get(index);
		if (index + 3 < arr.size()-1) {
			thdiff = arr.get(index + 3) - arr.get(index);
			if (thdiff == 3)
				return numSolution(arr, index + 1) + numSolution(arr, index + 2) + numSolution(arr, index + 3);
			else if (tdiff <= 3)
				return numSolution(arr, index + 1) + numSolution(arr, index + 2);
			return numSolution(arr, index+1);
		} else if (index + 2 < arr.size()-1) {
			if (tdiff <= 3)
				return numSolution(arr, index+2) + numSolution(arr, index+1);
			return numSolution(arr, index+1);
		}
		return numSolution(arr, index+1);
	}	
*/
	public static void main(String[] args) {
		File file = new File("input2.txt");
		try {
			Scanner in = new Scanner(file);
			ArrayList<Integer> nums = new ArrayList<Integer>();
			String input;
			int n;
			while (true) {
				input = in.nextLine();
				n = Integer.parseInt(input);
				nums.add(n);
				if (!in.hasNextLine()) {
					break;
				}
			}
			nums.add(0);
			Collections.sort(nums);
			nums.add(nums.get(nums.size()-1) + 3);

			long num = numSolution(nums);

			System.out.println(num);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}