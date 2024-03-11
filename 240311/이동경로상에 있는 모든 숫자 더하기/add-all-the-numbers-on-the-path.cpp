#include <iostream>
#include <string>

using namespace std;

int n, t,
    curR, curC,
    dir = 0;    // 0-N, 1-E, 2-S, 3-W
string cmds;
int** board;
int dR[4] = {-1, 0, 1, 0}, dC[4] = {0, 1, 0, -1};

bool inRange(int r, int c){
    return 0<=r && r<n && 0<=c && c<n;
}

int calcSum(){
    int sum = board[curR][curC];
    for(int i = 0; i < cmds.size(); ++i){
        //printf("%d: %d\n", i, sum);
        switch(cmds[i]){
        case 'L':
            dir = (dir + 3) % 4;
            break;
        case 'R':
            dir = (dir + 1) % 4;
            break;
        case 'F':
            int nR = curR + dR[dir],
                nC = curC + dC[dir];
            if(inRange(nR, nC)){
                curR = nR;
                curC = nC;
                sum += board[curR][curC];
            }
            break;
        }
    }
    return sum;
}

int main() {
    scanf("%d %d", &n, &t);
    cin >> cmds;

    curR = n/2;
    curC = n/2;

    board = new int*[n];
    for(int i = 0; i < n; ++i){
        board[i] = new int[n];
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf(" %d", &board[i][j]);
        }
    }

    printf("%d", calcSum());

    delete[] board;
    return 0;
}