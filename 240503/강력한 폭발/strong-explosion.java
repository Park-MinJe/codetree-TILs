import java.util.*;
import java.lang.Math;

public class Main {
    public static Scanner sc;

    public static int n;
    public static ArrayList<int[]> bombs;
    public static int maxCnt;
    public static int[][] dr = {
        {-2, -1, 1, 2},
        {-1, 0, 1, 0},
        {-1, -1, 1, 1}
    };
    public static int[][] dc = {
        {0, 0, 0, 0},
        {0, 1, 0, -1},
        {-1, 1, 1, -1}
    };

    public static boolean inRange(int nr, int nc){
        return 0<=nr&&nr<n && 0<=nc&&nc<n;
    }

    public static void backtracking(int curBomb, int cntBombs, int[][] map){
        if(curBomb >= cntBombs){
            int tmpCnt = 0;
            for(int i = 0; i < n; ++i){
                for(int j = 0; j < n; ++j){
                    if(map[i][j] != 0) ++tmpCnt;
                }
            }

            maxCnt = Math.max(maxCnt, tmpCnt);
            return;
        }

        int[] curBombCoord = bombs.get(curBomb);
        for(int i = 0; i < 3; ++i){
            int[][] curMap = new int[n][n];
            for(int j = 0; j < n; ++j){
                for(int k = 0; k < n; ++k){
                    curMap[j][k] = map[j][k];
                }
            }
            for(int j = 0; j < 4; ++j){
                int nr = curBombCoord[0] + dr[i][j];
                int nc = curBombCoord[1] + dc[i][j];

                if(inRange(nr, nc)){
                    curMap[nr][nc] = -1;
                }
            }
            backtracking(curBomb+1, cntBombs, curMap);
        }
    }
    
    public static void main(String[] args) {
        sc = new Scanner(System.in);
        n = sc.nextInt();
        int[][] map = new int[n][n];
        bombs = new ArrayList<>();
        maxCnt = 0;

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                map[i][j] = sc.nextInt();

                int[] tmpCoord = new int[2];
                tmpCoord[0] = i;
                tmpCoord[1] = j;

                if(map[i][j] != 0)
                    bombs.add(tmpCoord);
            }
        }

        backtracking(0, bombs.size(), map);
        
        System.out.println(maxCnt);
    }
}