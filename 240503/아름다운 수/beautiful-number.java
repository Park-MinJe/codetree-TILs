import java.util.*;

public class Main {
    public static int answer;

    public static void findPretty(int curN, int trgtN){
        if(curN >= trgtN){
            ++answer;
            return;
        }

        for(int i = 1; i <= 4; ++i){
            if(curN+i <= trgtN){
                findPretty(curN+i, trgtN);
            }
        }
    }

    public static void main(String[] args) {
        answer = 0;

        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        findPretty(0, n);
        System.out.println(answer);
    }
}