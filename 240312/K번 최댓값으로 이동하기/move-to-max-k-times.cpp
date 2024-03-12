#include <iostream>
#include <queue>

using namespace std;

int n, k, startR, startC;
int** board;
int dr[4] = {-1, 0, 1, 0},
    dc[4] = {0, 1, 0, -1};
//bool** isVisited;

class Coord{
public:
    int r, c;
    Coord(){}
    Coord(int ir, int ic): r(ir), c(ic) {}
};

bool inRange(int r, int c){
    return 1<=r&&r<=n && 1<=c&&c<=n;
}
bool isAccessible(int sr, int sc, int nr, int nc, bool** isVisited){
    return inRange(nr, nc) && !isVisited[nr][nc] && board[nr][nc]<board[sr][sc];
}

void search(){
    int curStartR = startR,
        curStartC = startC,
        nextStartR = n,
        nextStartC = n,
        maxN = 0;
    for(int i = 0; i < k; ++i){
        maxN = 0;

        bool** isVisited = new bool*[n+1];
        for(int j = 1; j <= n; ++j){
            isVisited[j] = new bool[n+1];
            for(int l = 1; l <=n; ++l){
                isVisited[j][l] = false;
            }
        }

        queue<Coord> q;
        q.push(Coord(curStartR, curStartC));
        isVisited[curStartR][curStartC] = true;

        while(!q.empty()){
            Coord cur = q.front();
            q.pop();

            for(int j = 0; j < 4; ++j){
                int nr = cur.r + dr[j],
                    nc = cur.c + dc[j];

                if(isAccessible(curStartR, curStartC, nr, nc, isVisited)){
                    //debug
                    // printf("%d: %d %d\n", i, nr, nc);
                    q.push(Coord(nr, nc));
                    isVisited[nr][nc] = true;

                    if(maxN < board[nr][nc]){
                        maxN = board[nr][nc];
                        nextStartR = nr;
                        nextStartC = nc;
                    }
                    else if(maxN == board[nr][nc]){
                        if(nextStartR > nr){
                            nextStartR = nr;
                            nextStartC = nc;
                        }
                        else if(nextStartR == nr){
                            if(nextStartC > nc){
                                nextStartR = nr;
                                nextStartC = nc;
                            }
                        }
                    }
                    //debug
                    // printf("%d: nextR-%d nextC-%d\n", i, nextStartR, nextStartC);
                }
            }
        }
        //debug
        // printf("%d: startR-%d startC-%d\n", i, curStartR, curStartC);
        // printf("%d: nextR-%d nextC-%d\n", i, nextStartR, nextStartC);
        curStartR = nextStartR;
        curStartC = nextStartC;
    }
    printf("%d %d", nextStartR, nextStartC);
}

void handleInput(){
    scanf("%d %d", &n, &k);
    board = new int*[n+1];
    //isVisited = new bool*[n+1];
    for(int i = 1; i <= n; ++i){
        board[i] = new int[n+1];
        //isVisited[i] = new bool[n+1];
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            scanf(" %d", &board[i][j]);
            //isVisited[i][j] = false;
        }
    }
    scanf(" %d %d", &startR, &startC);
}

int main() {
    handleInput();
    search();
    return 0;
}