#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, k, m, result = 0;
int** board;    // 0: 이동가능, 1: 돌
int dr[4] = {-1, 0, 1, 0},
    dc[4] = {0, 1, 0, -1};

class Coord{
public:
    int r, c;
    Coord(){}
    Coord(int ir, int ic): r(ir), c(ic) {}
};
vector<Coord> startPoints;
vector<Coord> stonePoints;
queue<vector<int>> setOfStonePointIdx;

void setInput(){
    scanf("%d %d %d", &n, &k, &m);
    board = new int*[n+1];
    for(int i = 1; i <= n; ++i){
        board[i] = new int[n+1];
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            scanf(" %d", &board[i][j]);
            if(board[i][j] == 1){
                stonePoints.push_back(Coord(i, j));
            }
        }
    }
    for(int i = 0; i < k; ++i){
        int tmpR, tmpC;
        scanf(" %d %d", &tmpR, &tmpC);
        startPoints.push_back(Coord(tmpR, tmpC));
    }
}

void backTracking(int len, int stoneCnt, int startIdx, vector<int>& stoneIdxSet){
    if(len == 0){
        //debug
        // for(int i = 0; i < m; ++i){
        //     printf("%d ", stoneIdxSet[i]);
        // }
        // printf("\n");
        // printf("size = %ld\n", stoneIdxSet.size());
        
        setOfStonePointIdx.push(stoneIdxSet);
        return;
    }
    
    int tmpNextLen = len-1;
    for(int i = startIdx; i < stoneCnt; ++i){
        stoneIdxSet[m-len] = i;
        backTracking(tmpNextLen, stoneCnt, i+1, stoneIdxSet);
    }
}
void setCombination(){
    int stoneLen = stonePoints.size();
    vector<int> tmpStoneIdx(m, -1);
    backTracking(m, stoneLen, 0, tmpStoneIdx);
}

bool inRange(int r, int c){
    return 1<=r&&r<=n && 1<=c&&c<=n;
}
bool isAccessible(int**& isVisited, int r, int c){
    return inRange(r, c) && !isVisited[r][c] && board[r][c] == 0;
}
void bfs(){
    int cnt = 0;
    int** isVisited = new int*[n+1];
    for(int i = 1; i <= n; ++i){
        isVisited[i] = new int[n+1];
        for(int j = 1; j <= n; ++j){
            isVisited[i][j] = false;
        }
    }

    queue<Coord> q;
    vector<Coord>::iterator it;
    for(it = startPoints.begin(); it != startPoints.end(); ++it){
        // printf(">>start point: (%d, %d)\n", (*it).r, (*it).c);
        if(isAccessible(isVisited, (*it).r, (*it).c)){
            q.push(Coord((*it).r, (*it).c));
            isVisited[(*it).r][(*it).c] = true;
            ++cnt;
        }
    }

    while(!q.empty()){
        Coord cur = q.front();
        q.pop();

        for(int i = 0; i < 4; ++i){
            int nr = cur.r + dr[i],
                nc = cur.c + dc[i];
            if(isAccessible(isVisited, nr, nc)){
                q.push(Coord(nr, nc));
                isVisited[nr][nc] = true;
                ++cnt;
            }
        }
    }
    // printf("cnt = %d\n", cnt);

    // if(result < cnt){
    //     result = cnt;
    // }
    result = cnt;
}
void search(){
    while(!setOfStonePointIdx.empty()){
        vector<int> stoneIdxSet = setOfStonePointIdx.front();
        // printf(">>Start search for %ld set", stoneIdxSet.size());
        setOfStonePointIdx.pop();
        // 옮긴 돌 좌표 0으로 표기
        //debug
        // printf("\n옮긴 돌 좌표\n");
        for(int i = 0; i < m; ++i){
            Coord tmp = stonePoints[stoneIdxSet[i]];
            board[tmp.r][tmp.c] = 0;
            // debug
            // printf("- %d: %d %d\n", stoneIdxSet[i], tmp.r, tmp.c);
        }
        //debug
        // printf("\n대상 격자\n");
        // for(int i = 1; i <= n; ++i){
        //     for(int j = 1; j <= n; ++j){
        //         printf("%d ", board[i][j]);
        //     }
        //     printf("\n");
        // }

        bfs();

        // 옮긴 돌 좌표 0으로 표기했던 것 1로 되돌리기
        for(int i = 0; i < m; ++i){
            Coord tmp = stonePoints[stoneIdxSet[i]];
            board[tmp.r][tmp.c] = 1;
        }
    }
}

int main() {
    setInput();
    setCombination();
    search();
    printf("%d", result);
    return 0;
}