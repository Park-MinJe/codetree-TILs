#include <iostream>

using namespace std;

int n, m,
    curR, curC,
    dir = 2;    // 0-N, 1-E, 2-S, 3-W
int** board;

int main() {
    scanf("%d %d", &n, &m);
    int rSize = n,
        cSize = m;

    board = new int*[n];
    for(int i = 0; i<n; ++i){
        board[i] = new int[n];
    }

    curR = 0;
    curC = 0;
    int num = 1, iter = 0;
    board[curR][curC] = num;
    ++curR;
    ++num;
    while(n > 0 && m > 0){
        switch(dir){
        case 0: // N
            for(int i = 1; i<n; ++i){
                board[curR][curC] = num;
                ++num;
                if(i != n-1) --curR;
            }
            --curC;
            dir = (dir+3)%4;
            --n;
            break;
        case 1: // E
            for(int i = 1; i<m; ++i){
                board[curR][curC] = num;
                ++num;
                if(i != m-1) ++curC;
            }
            --curR;
            dir = (dir+3)%4;
            --m;
            break;
        case 2: // S
            for(int i = 1; i<n; ++i){
                board[curR][curC] = num;
                ++num;
                if(i != n-1) ++curR;
            }
            ++curC;
            dir = (dir+3)%4;
            if(iter != 0) --n;
            break;
        case 3: // W
            for(int i = 1; i<m; ++i){
                board[curR][curC] = num;
                ++num;
                if(i != m-1) --curC;
            }
            ++curR;
            dir = (dir+3)%4;
            --m;
            break;
        }
        ++iter;
    }

    for(int i = 0; i < rSize; ++i){
        for(int j = 0; j < cSize; ++j){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}