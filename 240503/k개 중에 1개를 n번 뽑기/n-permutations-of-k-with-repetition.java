import java.util.*;

public class Main {
    public static void backtracking(int curN, int trgtN, int maxK, String str){
        if(curN >= trgtN){
            System.out.println(str);
            return;
        }

        for(int i = 1; i <= maxK; ++i){
            backtracking(curN+1, trgtN, maxK, str+Integer.toString(i)+" ");
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int K = sc.nextInt();
        int N = sc.nextInt();

        backtracking(0, N, K, "");
    }
}