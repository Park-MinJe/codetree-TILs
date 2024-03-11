#include <iostream>

using namespace std;

int n, m,
    dir = 1;    // 0-N, 1-E, 2-S, 3-W
char** board;

int dR[4] = {-1, 0, 1, 0}, dC[4] = {0, 1, 0, -1};

bool inRange(int r, int c){
    return 0 <= r && r < n && 0 <= c && c < m;
}

int main() {
    scanf("%d %d", &n, &m);
    board = new char*[n];
    for(int i = 0; i < n; ++i){
        board[i] = new char[m];
        for(int j = 0; j < m; ++j){
            board[i][j] = '-';
        }
    }

    int curR = 0, curC = 0;
    board[curR][curC] = 'A';
    for(int i = 1; i < n*m; ++i){
        while(true){
            int nR = curR + dR[dir],
                nC = curC + dC[dir];
            if(inRange(nR, nC) && board[nR][nC] == '-'){
                curR = nR;
                curC = nC;
                board[curR][curC] = 'A' + (i%26);
                break;
            }
            else{
                dir = (dir + 1) % 4;
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}