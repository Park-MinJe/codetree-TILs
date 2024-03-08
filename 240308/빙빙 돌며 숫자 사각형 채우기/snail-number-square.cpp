#include <iostream>

using namespace std;

int n, m, 
    dx,     // 열
    dy,     // 행
    dir;
int** board;

int main() {
    scanf("%d %d", &n, &m);
    int rSize = n,
        cSize = m;
    board = new int*[n+1];
    for(int i = 1; i <= n; ++i){
        board[i] = new int[m+1];
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            board[i][j] = 0;
        }
    }

    dx = 1;
    dy = 1;
    dir = 0;    // 0:E, 1:S, 2:W, 3:N
    int num = 1;
    for(int i = 1; i <= m; ++i){
        board[dy][dx] = num;
        if(i != m) dx++;
        num++;
    }
    dy++;
    dir = (dir+1)%4;
    while(n != 0 && m != 0){
        //printf("%d %d\n", n, m);
        //printf("%d %d %d\n\n", dir, dy, dx);
        switch(dir){
        case 0: // E
            for(int i = 1; i < m; ++i){
                board[dy][dx] = num;
                if(i != m-1) dx++;
                num++;
            }
            dy++;
            --m;
            break;
        case 1: // S
            for(int i = 1; i < n; ++i){
                board[dy][dx] = num;
                if(i != n-1) dy++;
                num++;
            }
            dx--;
            --n;
            break;
        case 2: // W
            for(int i = 1; i < m; ++i){
                board[dy][dx] = num;
                if(i != m-1) dx--;
                num++;
            }
            dy--;
            --m;
            break;
        case 3: // N
            for(int i = 1; i < n; ++i){
                board[dy][dx] = num;
                if(i != n-1) dy--;
                num++;
            }
            dx++;
            --n;
            break;
        }
        dir = (dir+1)%4;
    }

    for(int i = 1; i <= rSize; ++i){
        for(int j = 1; j <= cSize; ++j){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}