import java.util.*;
import java.lang.*;

public class Main {
    static Scanner sc;
    static int n;
    static List<Integer> arr;
    static int min = Integer.MAX_VALUE;

    public static void main(String[] args) {
        sc = new Scanner(System.in);
        n = sc.nextInt();
        arr = new ArrayList<Integer>(n);
        for(int i = 0; i < n; ++i){
            arr.add(sc.nextInt());
        }
        
        // 회의 장소가 i번재 집인 경우
        for(int i = 0; i < n; ++i){
            int tmpSum = 0;
            for(int j = 0; j < n; ++j){
                if(i == j) continue;
                tmpSum += Math.abs(i-j) * arr.get(j);
            }
            min = Math.min(min, tmpSum);
        }

        // 결과 출력
        System.out.print(min);
    }
}