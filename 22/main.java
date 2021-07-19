import java.io.File;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;

class main {

    static int score(LinkedList<Integer> list) {
        int score = 0;
        ListIterator<Integer> it = list.listIterator(0);
        for (int val = list.size(); val >= 1; --val) {
            score += it.next() * val;
        }
        return score;
    }

    /*
    static int combat(LinkedList<Integer> player1, LinkedList<Integer> player2) { //PART 1 Non-recursive Combat
        while (!player1.isEmpty() && !player2.isEmpty()) {
            if (player1.peekFirst() < player2.peekFirst()) {
                player2.add(player2.pop());
                player2.add(player1.pop());
            } else {
                player1.add(player1.pop());
                player1.add(player2.pop());
            }
        }

        if (player1.isEmpty()) {
            return 2;
        } else {
            return 1;
        }
    }
    */

    static int combat(LinkedList<Integer> player1, LinkedList<Integer> player2) { //PART 2 Recursive Combat
        HashMap<LinkedList<Integer>,LinkedList<Integer>> roundHistory = new HashMap<>();

        while (!player1.isEmpty() && !player2.isEmpty()) {
            if (roundHistory.get(player1) == player2) return 1;
            roundHistory.put(player1, player2);
            if (player1.peekFirst() <= player1.size() - 1 && player2.peekFirst() <= player2.size() - 1) {
                LinkedList<Integer> sub1 = new LinkedList<>();
                LinkedList<Integer> sub2 = new LinkedList<>();
    
                ListIterator<Integer> it1 = player1.listIterator(1);
                ListIterator<Integer> it2 = player2.listIterator(1);
                for (int i = 0; i < player1.peekFirst(); ++i) {
                    sub1.add(it1.next());
                }

                for (int i = 0; i < player2.peekFirst(); ++i) {
                    sub2.add(it2.next());
                }
                int subWin = combat(sub1, sub2);
                
                if (subWin == 1) {
                    player1.add(player1.pop());
                    player1.add(player2.pop());
                } else {
                    player2.add(player2.pop());
                    player2.add(player1.pop());
                }
            } else {
                if (player1.peekFirst() < player2.peekFirst()) {
                    player2.add(player2.pop());
                    player2.add(player1.pop());
                } else {
                    player1.add(player1.pop());
                    player1.add(player2.pop());
                }
            }
        }

        if (player1.isEmpty()) {
            return 2;
        } else {
            return 1;
        }
    }



    public static void main(String[] args) {
        String input;
        LinkedList<Integer> player1 = new LinkedList<>();
        LinkedList<Integer> player2 = new LinkedList<>();

        try (Scanner scn = new Scanner(new File(args[0]))) {
            boolean isPlayer1 = true;
            scn.nextLine();
            while (scn.hasNextLine()) {
                input = scn.nextLine();
                if (input.isBlank());
                else if (input.charAt(0) == 'P') {
                    isPlayer1 = false;
                } else {
                    if (isPlayer1) {
                        player1.add(Integer.parseInt(input));
                    } else {
                        player2.add(Integer.parseInt(input));
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }

        int winner = combat(player1, player2);
        int score;
        if (winner == 1) score = score(player1);
        else score = score(player2);
        System.out.println("Player " + winner + " Wins! Their score was: " + score);
    }

}