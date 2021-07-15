import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Code {

    public static long chineseRemainder(ArrayList<Long> n, ArrayList<Long> a) {
 
        long prod = n.stream().reduce((long) 1, (i, j) -> i * j);
 
        long p, sm = 0;
        for (int i = 0; i < n.size(); i++) {
            p = prod / n.get(i);
            sm += a.get(i) * mulInv(p, n.get(i)) * p;
        }
        return sm % prod;
    }
 
    private static long mulInv(Long a, Long b) {
        long b0 = b;
        long x0 = 0;
        long x1 = 1;
 
        if (b == 1)
            return 1;
 
        while (a > 1) {
            long q = a / b;
            long amb = a % b;
            a = b;
            b = amb;
            long xqx = x1 - q * x0;
            x1 = x0;
            x0 = xqx;
        }
 
        if (x1 < 0)
            x1 += b0;
 
        return x1;
    }

    public static void main(String[] args) {
        ArrayList<Long> nbus = new ArrayList<>();
        ArrayList<Long> offsets = new ArrayList<>();
        String buses;
        try (Scanner in = new Scanner(new File("input.txt"))) {
            in.nextLine();
            int begin = -1;
            int end = 0;
            buses = in.nextLine();
            Long current = (long) 0;
            while (true) {
                end = buses.indexOf(',', begin+1);
                if(buses.charAt(begin+1) == 'x') {
                    ++current;
                    begin = end;
                    continue;
                }
                offsets.add(current);
                ++current;
                if (end == -1) {
                    nbus.add(Long.parseLong(buses.substring(begin+1)));
                    break;
                }
                nbus.add(Long.parseLong(buses.substring(begin+1, end)));
                begin = end;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        
        System.out.println(chineseRemainder(nbus, offsets));
    }

    /* PART 1
    public static void main(String[] args) {
        ArrayList<Integer> nbus = new ArrayList<>();
        int earliest = 0;
        try (Scanner in = new Scanner(new File("input.txt"))) {
            earliest = Integer.parseInt(in.nextLine());
            String buses = in.nextLine();
            int begin = -1;
            int end = 0;
            while (true) {
                end = buses.indexOf(',', begin+1);
                if(buses.charAt(begin+1) == 'x') {
                    begin = end;
                    continue;
                }
                if (end == -1) {
                    nbus.add(Integer.parseInt(buses.substring(begin+1)));
                    break;
                }
                nbus.add(Integer.parseInt(buses.substring(begin+1, end)));
                begin = end;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        int nBus = -1;
        int wait = -1;
        for (int i : nbus) {
            int bwait = i - (earliest % i);
            if (bwait < wait || wait == -1) {
                wait = bwait;
                nBus = i;
            }
        }
        System.out.println(wait*nBus);
    }
    */
}