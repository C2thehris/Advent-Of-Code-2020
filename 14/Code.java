import java.io.FileNotFoundException;
import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;

public class Code {

    static void floatings(ArrayList<Long> arr, String address, StringBuilder current) {
        for (int i = current.length(); i < address.length(); ++i) {
            if (address.charAt(i) != 'X') current.append(address.charAt(i));
            else {
                StringBuilder copy = new StringBuilder(current.toString());
                current.append('0');
                copy.append('1');
                floatings(arr, address, copy);
            }
        }
        arr.add(Long.parseLong(current.toString(), 2));
    }

    static String applyMask(String mask, long val) {
        StringBuilder binary = new StringBuilder(Long.toBinaryString(val));

        binary.reverse();

        for (int i = binary.length(); i < 36; ++i) {
            binary.append('0');
        }

        binary.reverse();

        StringBuilder masked = new StringBuilder();
        for (int i = 0; i < binary.length(); ++i) {
            if (mask.charAt(i) == '0') masked.append(binary.charAt(i));
            else masked.append(mask.charAt(i));
        }

        return masked.toString();
    }

    //PART 2
    public static void main(String[] args) {

        HashMap<Long, Long> map = new HashMap<>();
        String mask = "";
        String input;

        try (Scanner in = new Scanner(new File("input.txt"))) {

            while (true) {
                input = in.nextLine();
                if (input.indexOf("mask", 0) != -1) {
                    mask = input.substring(7);
                } else {
                    long val = 0;
                    int end = input.indexOf(']', 3);
                    String address = input.substring(4, end);
                    
                    val = Integer.parseInt(input.substring(end + 4));

                    address = applyMask(mask, Long.parseLong(address));

                    ArrayList<Long> arr = new ArrayList<>();

                    floatings(arr, address, new StringBuilder());

                    for (long i : arr) {
                        map.put(i, val);
                    }
                }
                if (!in.hasNextLine()) break;
            }
            
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        long sum = 0;

        for (long i : map.values()) {
            sum += i;
        }
        System.out.println(sum);
    }

    /* PART 1
    public static void main(String[] args) {

        HashMap<Integer, Long> map = new HashMap<>();
        String mask = "";
        String input;

        try (Scanner in = new Scanner(new File("input.txt"))) {

            while (true) {
                input = in.nextLine();
                if (input.indexOf("mask", 0) != -1) {
                    mask = input.substring(7);
                } else {
                    long val = 0;
                    int end = input.indexOf(']', 3);
                    String address = input.substring(4, end);

                    val = Integer.parseInt(input.substring(end + 4));

                    val = applyMask(mask, val);

                    map.put(Integer.parseInt(address), val);

                }
                if (!in.hasNextLine()) break;
            }
            
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        long sum = 0;

        for (long i : map.values()) {
            sum += i;
        }
        System.out.println(sum);
    }
    */

} 