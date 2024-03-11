#include <iostream>

using namespace std;

int n, m,
    curR, curC,
    dir = 2;    // 0-N, 1-E, 2-S, 3-W
int** board;

int mvR[4] = {-1, 0, 1, 0}, mvC[4] = {0, 1, 0, -1},
    mvRLast[4] = {0, -1, 0, 1}, mvCLast[4] = {-1, 0, 1, 0};

bool inRange(int nr, int nc){
    return nr >= 0 && nr < n && nc >= 0 && nc < m;
}

int main() {
    scanf("%d %d", &n, &m);
    int rSize = n,
        cSize = m;

    board = new int*[n];
    for(int i = 0; i<n; ++i){
        board[i] = new int[n];
        for(int j = 0; j<n; ++j){
            board[i][j] = -1;
        }
    }

    curR = 0;
    curC = 0;
    board[curR][curC] = 1;
    for(int i = 2; i <= n*m; ++i){
        while(true){
            int nr = curR + mvR[dir];
            int nc = curC + mvC[dir];
            //printf("%d %d\n", nr, nc);

            if(inRange(nr, nc) && board[nr][nc] == -1){
                curR = nr;
                curC = nc;
                board[curR][curC] = i;
                break;
            }
            else{
                dir = (dir+3)%4;
            }
        }
    }

    for(int i = 0; i < rSize; ++i){
        for(int j = 0; j < cSize; ++j){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    delete[] board;

    return 0;
}