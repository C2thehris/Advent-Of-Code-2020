import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Code {

    public static void main(String[] args) {
        int x = -10;
        int y = 1;
        int shipx = 0;
        int shipy = 0;
        try (Scanner in = new Scanner(new File("input.txt"))) {
            String input;
            while (true) {
                input = in.nextLine();
                char c = input.charAt(0);
                int val = Integer.parseInt(input.substring(1));
                switch (c) {
                    case 'N': { y += val; break; }
                    case 'S': { y -= val; break; }
                    case 'E': { x -= val; break; }
                    case 'W': { x += val; break; }
                    case 'L': { 
                        val %= 360; 
                        switch (val) {
                            case 0: { break; }
                            case 90: {
                                int temp = x;
                                x = y;
                                y = -1 * temp;
                                break;
                            }
                            case 180: {
                                x *= -1;
                                y *= -1;
                                break;
                            }
                            case 270: {
                                int temp = x;
                                x = -1*y;
                                y = temp;
                                break;

                            }
                            default:
                        }
                        break;
                    }
                    case 'R': { 
                        val %= 360;
                        switch (val) {
                            case 0: { break; }
                            case 90: {
                                int temp = x;
                                x = -1*y;
                                y = temp;
                                break;
                            }
                            case 180: {
                                x *= -1;
                                y *= -1;
                                break;
                            }
                            case 270: {
                                int temp = x;
                                x = y;
                                y = -1 * temp;
                                break;
                            }
                            default:
                        }
                        break;
                    }
                    case 'F': {
                        shipx += val *x;
                        shipy += val *y;
                        break;
                    }
                    default:
                }
                if (!in.hasNextLine()) break;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        System.out.println(Math.abs(shipx) + Math.abs(shipy));
    }
}