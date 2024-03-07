#include <iostream>

using namespace std;

int n;
int** board;

bool checkCnt(int dy, int dx){
    int cnt = 0,
        preDy = dy-1,
        nextDy = dy+1,
        preDx = dx-1,
        nextDx = dx+1;
    // N
    if(preDy>=0 && preDy<n){
        if(board[preDy][dx] == 1) ++cnt;
    }
    // S
    if(nextDy>=0 && nextDy<n){
        if(board[nextDy][dx] == 1) ++cnt;
    }
    // W
    if(preDx>=0 && preDx<n){
        if(board[dy][preDx] == 1) ++cnt;
    }
    // E
    if(nextDx>=0 && nextDx<n){
        if(board[dy][nextDx] == 1) ++cnt;
    }

    if(cnt >= 3) return true;
    else return false;
}

int main() {
    scanf("%d", &n);
    
    board = new int*[n];
    for(int i = 0; i<n; ++i){
        board[i] = new int[n];
    }
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            scanf("%d", &board[i][j]);
        }
    }

    int result = 0;
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            if(checkCnt(j, i)){
                ++result;
            }
        }
    }
    printf("%d", result);
    
    return 0;
}