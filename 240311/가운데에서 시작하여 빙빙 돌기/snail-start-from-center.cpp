#include <iostream>
#define MAX_N 100

using namespace std;

int n,
    curR, curC, 
    dir = 3;    // 0-N,1-E,2-S,3-W
int board[MAX_N][MAX_N];

int dR[4] = {-1, 0, 1, 0},
    dC[4] = {0, 1, 0, -1};

bool inRange(int r, int c){
    return 0<=r&&r<n && 0<=c&&c<n;
}

int main() {
    scanf("%d", &n);
    curR = n-1;
    curC = n-1;

    board[curR][curC] = n*n;
    for(int i = n*n-1; i > 0; --i){
        while(true){
            int nR = curR + dR[dir],
                nC = curC + dC[dir];
            if(inRange(nR, nC) && board[nR][nC] == 0){
                curR = nR;
                curC = nC;
                board[curR][curC] = i;
                break;
            }
            else{
                dir = (dir+1)%4;
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}