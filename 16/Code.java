import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.Map.Entry;
import java.io.File;
import java.io.FileNotFoundException;

class Bounds {

    Bounds(int lowerMin, int lowerMax, int upperMin, int upperMax) {
        this.lowerMin = lowerMin;
        this.lowerMax = lowerMax;
        this.upperMax = upperMax;
        this.upperMin = upperMin;
    }

    boolean valid(int x) {
        return (x <= lowerMax && x >= lowerMin) || (x <= upperMax && x >= upperMin);
    }

    public int lowerMax;
    public int lowerMin;
    public int upperMax;
    public int upperMin;
}

public class Code {

    static void remove(TreeMap<String, ArrayList<Integer>> map, int val, Entry<String, ArrayList<Integer>> skip) {
        for (Map.Entry<String, ArrayList<Integer>> entry : map.entrySet()) {
            if (entry == skip) continue;
            ArrayList<Integer> arr = entry.getValue();
            int index = arr.indexOf(val);
            if (index == -1) continue;
            arr.remove(index);
            entry.setValue(arr);
        }
    }

    static void reduce(TreeMap<String, ArrayList<Integer>> map) {
        ArrayList<Integer> removed = new ArrayList<>();
        Iterator<Map.Entry<String, ArrayList<Integer>>> it = map.entrySet().iterator();
        while (it.hasNext()) {
            Entry<String, ArrayList<Integer>> entry = it.next();
            if (entry.getValue().size() == 1) {
                int val = entry.getValue().get(0);
                if(removed.indexOf(val) != -1) continue;
                removed.add(val);
                remove(map, val, entry);
                it = map.entrySet().iterator();
            }
        }
        
    }

    public static void main(String[] args) {
        TreeMap<String, Bounds> bounds = new TreeMap<>();
        TreeMap<String, ArrayList<Integer>> cols = new TreeMap<>();
        ArrayList<Integer> myTicket = new ArrayList<Integer>();
        try (Scanner in = new Scanner(new File("input.txt"))) {
            String input;
            String category;
            int begin = 0;
            int end = 0;
            int lowerMin = 0;
            int lowerMax = 0;
            int upperMin = 0;
            int upperMax = 0;
            while (true) {
                input = in.nextLine();
                if (input.isEmpty())
                    break;
                begin = input.indexOf(':') + 2;
                category = input.substring(0, begin - 2);
                end = input.indexOf('-', begin);
                lowerMin = Integer.parseInt(input.substring(begin, end));

                begin = end + 1;
                end = input.indexOf(' ', begin);
                lowerMax = Integer.parseInt(input.substring(begin, end));

                begin = input.indexOf(' ', end + 1);
                end = input.indexOf('-', begin);
                upperMin = Integer.parseInt(input.substring(begin + 1, end));

                upperMax = Integer.parseInt(input.substring(end + 1));

                Bounds b = new Bounds(lowerMin, lowerMax, upperMin, upperMax);

                ArrayList<Integer> list = new ArrayList<>();

                for (int i = 1; i < 21; ++i) {
                    list.add(i);
                }
                bounds.put(category, b);
                cols.put(category, list);
            }

            for (int i = 0; i < 2; ++i) {
                input = in.nextLine();
            }

            begin = -1;
            end = 0;
            while (end != -1) {
                if (begin == -1) begin = 0;
                else begin = end + 1;
                end = input.indexOf(',', begin);
                String val;
                if (end != -1)
                    val = input.substring(begin, end);
                else
                    val = input.substring(begin);
                int n = Integer.parseInt(val);
                myTicket.add(n);
            }

            for (int i = 0; i < 2; ++i) {
                input = in.nextLine();
            }

            while (true) {
                input = in.nextLine();
                begin = -1;
                end = 0;
                int i = 1;
                while (end != -1) {
                    if (begin == -1) begin = 0;
                    else begin = end + 1;
                    end = input.indexOf(',', begin);
    
                    String val;
                    if (end != -1)
                        val = input.substring(begin, end);
                    else
                        val = input.substring(begin);
                    int n = Integer.parseInt(val);

                    for (String str : bounds.keySet()) {
                        if (!bounds.get(str).valid(n)) {
                            ArrayList<Integer> arr = cols.get(str);
                            int index = arr.indexOf(i);
                            if (index == -1) continue;
                            arr.remove(arr.indexOf(i)); 
                            cols.put(str, arr);
                        }
                    }
                    ++i;
                }  
                /*
                 * boolean valid = false; for (Bounds b : arr) { valid = b.valid(n); if (valid)
                 * break; } if (!valid) { ; break; }
                 */
                if (!in.hasNextLine())
                    break;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        reduce(cols);
        Long answer = (long) 1;
        answer *= myTicket.get(cols.get("departure location").get(0)-1);
        answer *= myTicket.get(cols.get("departure station").get(0)-1);
        answer *= myTicket.get(cols.get("departure platform").get(0)-1);
        answer *= myTicket.get(cols.get("departure track").get(0)-1);
        answer *= myTicket.get(cols.get("departure date").get(0)-1);
        answer *= myTicket.get(cols.get("departure time").get(0)-1);
        
        System.out.println(answer);
    }
}