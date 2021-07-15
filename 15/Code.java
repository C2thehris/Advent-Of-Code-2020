import java.util.ArrayList;
import java.util.TreeMap;

public class Code {

    public static void main(String[] args) {
        int i = 1;
        String input = "16,11,15,0,1,7";

        TreeMap<Integer, ArrayList<Integer> > map = new TreeMap<>();

        int end = 0;
        int begin = -1;
        while (end != -1) {
            if (begin != -1) begin = end+1;
            else begin = 0;
            end = input.indexOf(',', begin);
            String key;
            if (end == -1) key = input.substring(begin);
            else key = input.substring(begin, end);
            ArrayList<Integer> arr = new ArrayList<>();
            arr.add(-1);
            arr.add(i);
            map.put(Integer.parseInt(key), arr);
            ++i;
        }
        
        int current = Integer.parseInt(input.substring(begin));

        while (i < 30000001) {
            ArrayList<Integer> last = map.get(current);
            current = 0;
            if (last.get(0) != -1) {
                current = last.get(1) - last.get(0);
            }

            ArrayList<Integer> lAge = map.get(current);
            if (lAge != null) {
                lAge.remove(lAge.get(0));
                lAge.add(i);
            } else {
                lAge = new ArrayList<>();
                lAge.add(-1);
                lAge.add(i);
            }
            map.put(current, lAge);
            ++i;
        }
        System.out.println(current);
    }


}