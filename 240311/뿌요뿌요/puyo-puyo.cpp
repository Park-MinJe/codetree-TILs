#include <iostream>

using namespace std;

int n, blockSize = 0;
int** board;
bool** isVisited;
int dr[4] = {-1, 0, 1, 0},
    dc[4] = {0, 1, 0, -1};

bool inRange(int r, int c){
    return 0<=r&&r<n && 0<=c&&c<n;
}

void dfs(int r, int c, int num){
    for(int i = 0; i < 4; ++i){
        int nr = r + dr[i],
            nc = c + dc[i];
        
        if(inRange(nr, nc) && !isVisited[nr][nc] && num == board[nr][nc]){
            isVisited[nr][nc] = true;
            ++blockSize;
            dfs(nr, nc, num);
        }
    }
}

void search(){
    int blockCnt = 0,
        maxBlockSize = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(!isVisited[i][j]){
                blockSize = 1;
                isVisited[i][j] = true;
                dfs(i, j, board[i][j]);

                if(maxBlockSize < blockSize) maxBlockSize = blockSize;
                if(blockSize >= 4) ++blockCnt;
            }
        }
    }

    printf("%d %d", blockCnt, maxBlockSize);
}

int main() {
    scanf("%d", &n);
    board = new int*[n];
    isVisited = new bool*[n];
    for(int i = 0; i < n; ++i){
        board[i] = new int[n];
        isVisited[i] = new bool[n];
        for(int j = 0; j < n; ++j){
            isVisited[i][j] = false;
        }
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf(" %d", &board[i][j]);
        }
    }

    search();

    return 0;
}