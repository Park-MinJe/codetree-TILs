import java.util.*;
import java.lang.*;

class Segment{
    public int x1;
    public int x2;

    Segment(){}
    Segment(int pX1, int pX2){this.x1 = pX1; this.x2 = pX2;}
}

public class Main {
    public static Scanner sc;
    public static int n;
    public static ArrayList<Segment> segs;
    public static int answer;

    public static boolean overlapped(Segment s1, Segment s2){
        int ax1 = s1.x1;
        int ax2 = s1.x2;

        int bx1 = s2.x1;
        int bx2 = s2.x2;

        return (ax1 <= bx1 && bx1 <= ax2) || (ax1 <= bx2 && bx2 <= ax2) ||
               (bx1 <= ax1 && ax1 <= bx2) || (bx1 <= ax2 && ax2 <= bx2);
    }

    public static void backtracking(int curSegIdx, int curCnt){
        if(curSegIdx >= n-1){
            answer = Math.max(answer, curCnt);
            return;
        }

        Segment curSeg = segs.get(curSegIdx);
        for(int i = curSegIdx+1; i < n; ++i){
            Segment nSeg = segs.get(i);

            if(!overlapped(curSeg, nSeg)){
                // 겹치지 않는 경우
                backtracking(i, curCnt+1);
            }
            else backtracking(n, curCnt);
        }
    }

    public static void main(String[] args) {
        sc = new Scanner(System.in);
        n = sc.nextInt();
        segs = new ArrayList<>();
        for(int i = 0; i < n; ++i){
            Segment newSeg = new Segment();
            newSeg.x1 = sc.nextInt();
            newSeg.x2 = sc.nextInt();
            segs.add(newSeg);
        }
        answer = 0;

        for(int i = 0; i < n; ++i){
            backtracking(i, 1);
        }

        System.out.println(answer);
    }
}