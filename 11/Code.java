import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Code {

	static int count(ArrayList<String> arr) {
		int count = 0;
		for (String str : arr) {
			char[] c = str.toCharArray();
			for (char ch : c) {
				if (ch == '#')
					++count;
			}
		}
		return count;
	}

	/* PART 1
	static int countAdj(ArrayList<String> arr, int y, int x) {
		int count = 0;
		boolean up = y > 0;
		boolean down = y < arr.size() - 1;
		boolean left = x > 0;
		boolean right = x < arr.get(0).length() - 1;
		String str;

		if (up) {
			str = arr.get(y - 1);
			if (str.charAt(x) == '#') ++count;
			if (left) count += (str.charAt(x - 1) == '#') ? 1 : 0;
			if (right) count += (str.charAt(x + 1) == '#') ? 1 : 0;
		}
		if (down) {
			str = arr.get(y + 1);
			if (str.charAt(x) == '#') ++count;
			if (left) count += (str.charAt(x - 1) == '#') ? 1 : 0;
			if (right) count += (str.charAt(x + 1) == '#') ? 1 : 0;
		}
		if (left) {
			str = arr.get(y);
			count += (str.charAt(x - 1) == '#') ? 1 : 0;
		}
		if (right) {
			str = arr.get(y);
			count += (str.charAt(x + 1) == '#') ? 1 : 0;
		}
		return count;
	}
	*/

	static int countAdj(ArrayList<String> arr, int y, int x) {
		int count = 0;

		int currx = x;
		int curry = y;
		while (currx > 0) {
			--currx;
			char ch = arr.get(y).charAt(currx);
			if (ch == '#') ++count;
			if (ch != '.') break;
		}
		while (curry > 0) {
			--curry;
			char ch = arr.get(curry).charAt(x);
			if (ch == '#') ++count;
			if (ch != '.') break;
		}

		currx = x;
		curry = y;
		while (currx < arr.get(0).length()-1) {
			++currx;
			char ch = arr.get(y).charAt(currx);
			if (ch == '#') ++count;
			if (ch != '.') break;
		}
		while (curry < arr.size() - 1) {
			++curry;
			char ch = arr.get(curry).charAt(x);
			if (ch == '#') ++count;
			if (ch != '.') break;
		}

		currx = x;
		curry = y;
		while (currx > 0 && curry > 0) {
			--currx;
			--curry;
			char ch = arr.get(curry).charAt(currx);
			if (ch == '#') ++count;
			if (ch != '.') break;
		}

		currx = x;
		curry = y;
		while (currx > 0 && curry < arr.size() - 1) {
			--currx;
			++curry;
			char ch = arr.get(curry).charAt(currx);
			if (ch == '#') ++count;
			if (ch != '.') break;
		}
		currx = x;
		curry = y;
		while (currx < arr.get(0).length() - 1 && curry < arr.size() - 1) {
			++currx;
			++curry;
			char ch = arr.get(curry).charAt(currx);
			if (ch == '#') ++count;
			if (ch != '.') break;
		}

		currx = x;
		curry = y;
		while (currx < arr.get(0).length() - 1 && curry > 0) {
			++currx;
			--curry;
			char ch = arr.get(curry).charAt(currx);
			if (ch == '#') ++count;
			if (ch != '.') break;
		}

		return count;
	}

	public static void main(String[] args) {
		ArrayList<String> arr = new ArrayList<>();
		try (Scanner in = new Scanner(new File("input.txt"))) {
			while (true) {
				arr.add(in.nextLine());
				if (!in.hasNextLine()) {
					break;
				}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		int current = 0;
		int last = 1;
		while (current != last) {
			last = current;
			ArrayList<String> temp = new ArrayList<>();
			for (int i = 0; i < arr.size(); ++i) {
				StringBuilder str = new StringBuilder();
				for (int j = 0; j < arr.get(0).length(); ++j) {
					if (arr.get(i).charAt(j) == '.') {str.append('.'); continue;}
					int count = countAdj(arr, i, j);
					if (count == 0) str.append('#');
					else str.append(arr.get(i).charAt(j));
				}
				temp.add(str.toString());
			}
			arr.clear();
			arr = temp;
			temp = new ArrayList<>();
			for (int i = 0; i < arr.size(); ++i) {
				StringBuilder str = new StringBuilder();
				for (int j = 0; j < arr.get(0).length(); ++j) {
					if (arr.get(i).charAt(j) == '.') {str.append('.'); continue;}
					int count = countAdj(arr, i, j);
					if (count >= 5 && arr.get(i).charAt(j) == '#') str.append('L');
					else str.append(arr.get(i).charAt(j));
				}
				temp.add(str.toString());
			}
			arr = temp;
			current = count(arr);
		}
		System.out.println(current);
	}

}