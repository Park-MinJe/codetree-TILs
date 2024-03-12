#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, k, result = 0;
int** board;
bool** isVisited;
int dr[4] = {-1, 0, 1, 0},
    dc[4] = {0, 1, 0, -1};

class Coord{
public:
    int r, c;
    Coord(){}
    Coord(int ir, int ic): r(ir), c(ic) {}
    void setCoord(int ir, int ic) {
        r = ir;
        c = ic;
    }
};

vector<Coord> startPoints;

bool inRange(int r, int c){
    return 1<=r&&r<=n && 1<=c&&c<=n;
}

bool isAccessible(int r, int c){
    return inRange(r, c) && !isVisited[r][c] && board[r][c] == 0;
}

void search(){
    queue<Coord> q;
    for(int i = 0; i < k; ++i){
        q.push(startPoints[i]);
        isVisited[startPoints[i].r][startPoints[i].c] = true;
        ++result;
    }

    while(!q.empty()){
        Coord cur = q.front();
        q.pop();

        for(int j = 0; j < 4; ++j){
            int nr = cur.r + dr[j],
                nc = cur.c + dc[j];

            if(isAccessible(nr, nc)){
                q.push(Coord(nr, nc));
                isVisited[nr][nc] = true;
                ++result;
            }
        }
    }
    printf("%d", result);
}

int main() {
    scanf("%d %d", &n, &k);
    board = new int*[n+1];
    isVisited = new bool*[n+1];
    for(int i = 1; i <= n; ++i){
        board[i] = new int[n+1];
        isVisited[i] = new bool[n+1];
    }
    // 격자 정보 입력
    for(int i = 1; i <=n; ++i){
        for(int j = 1; j <= n; ++j){
            scanf(" %d", &board[i][j]);
            isVisited[i][j] = false;
        }
    }
    for(int i = 0; i < k; ++i){
        int tmpR, tmpC;
        scanf("%d %d", &tmpR, &tmpC);
        startPoints.push_back(Coord(tmpR, tmpC));
    }
    search();
    return 0;
}