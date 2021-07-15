import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;
import java.io.File;

class Code {

    static int checkRules(HashMap<Integer, String> map, String str, int nRule, int index) {
        String rule = map.get(nRule);
        int quot = rule.indexOf('\"');
        int current = index;
        int end = 0;
        if (quot != -1) {
            while (index < str.length()) {
                if (str.charAt(index) == map.get(nRule).charAt(quot + 1)) return index + 1;
                ++index;
            }
            return -1;
        } else {
            int bar = rule.indexOf('|');
            int first = 0;
            for (first = -1; end != -1
                && (bar == -1 || end < bar-1); first = end) {
                end = rule.indexOf(' ', first+1);
                String p;
                if (end != -1) {
                    p = rule.substring(first+1, end);
                } else {
                    p = rule.substring(first+1);
                }
                int next = Integer.parseInt(p);    
                index = checkRules(map, str, next, index);
                if (index == -1) break;
            }
            if (bar == -1) return index;
            int temp = index;
            index = current;
            for (first = bar+1; end != -1; first = end) {
                end = rule.indexOf(' ', first+1);
                String p;
                if (end != -1) {
                    p = rule.substring(first+1, end);
                } else {
                    p = rule.substring(first+1);
                }
                int next = Integer.parseInt(p);    
                index = checkRules(map, str, next, index);
                if (index == -1) {break;}
            }
            if (temp == -1 && index == -1) return -1;
            else if (temp == -1) return index;
            else if (index == -1) return temp;
            return Math.min(temp, index);
        }
    }

    public static void main(String[] args) {
        int total = 0;
        String input;
        boolean checkMode = false;
        HashMap<Integer, String> map = new HashMap<>();
        try (Scanner scn = new Scanner(new File("input2.txt"))) {
            while (scn.hasNextLine()) {
                input = scn.nextLine();
                if (input.length() == 0) {
                    checkMode = true;
                    continue;
                }

                if (checkMode) {
                    if (checkRules(map, input, 0, 0) == input.length()) {
                    ++total;
                    }
                } else {
                    int colon = input.indexOf(':');
                    int index = Integer.parseInt(input.substring(0, colon));
                    String rule = input.substring(colon+2);
                    map.put(index, rule);
                }
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        System.out.println(total);
    }

}