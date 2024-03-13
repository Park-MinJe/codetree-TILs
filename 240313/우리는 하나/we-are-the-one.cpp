#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n,  // 격자의 크기
    k,  // 고를 도시의 수
    u, d,   // u<=두 도시간의 높이의 차<=d
    result = 0; // 방문가능한 도시 수의 최대값
int** board;
int dr[4] = {-1, 0, 1, 0},
    dc[4] = {0, 1, 0, -1};
vector<vector<int>>* diff;

class Coord{
public:
    int r, c;
    Coord(){}
    Coord(int ir, int ic): r(ir), c(ic) {}
    void setCoord(int ir, int ic){
        r = ir;
        c = ic;
    }
};
vector<Coord> lstPosiblePoints;
vector<vector<Coord>> lstStartPointSet;

void getInput(){
    scanf("%d %d %d %d", &n, &k, &u, &d);
    board = new int*[n];
    for(int i = 0; i < n; ++i){
        board[i] = new int[n];
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf(" %d", &board[i][j]);
        }
    }
}

void backTracking(int len, int minR, int minC, vector<Coord>& vResult, int**& isUsed){
    if(len == 0){
        // for(int i = 0; i < k; ++i){
        //     printf("(%d,%d) ", vResult[i].r, vResult[i].c);
        // }
        // printf("\n");
        lstStartPointSet.push_back(vResult);
        return;
    }

    for(int i = minC; i < n; ++i){
        if(!isUsed[minR][i]){
            vResult[k-len].setCoord(minR, i);
            isUsed[minR][i] = true;
            backTracking(len-1, minR, i+1, vResult, isUsed);
            isUsed[minR][i] = false;
        }
    }
    for(int i = minR+1; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(!isUsed[i][j]){
                vResult[k-len].setCoord(i, j);
                isUsed[i][j] = true;
                backTracking(len-1, i, j+1, vResult, isUsed);
                isUsed[i][j] = false;
            }
        }
    }
}
bool inRange(int r, int c){
    return 0<=r&&r<n && 0<=c&&c<n;
}
bool isAccesible(int cr, int cc, int nr, int nc, bool**& isVisited){
    int diff = abs(board[cr][cc] - board[nr][nc]);
    return inRange(nr, nc) && !isVisited[nr][nc] && (u<=diff&&diff<=d);
}
void bfs(vector<Coord>& startPointSet){
    int cnt = 0;

    bool** isVisited = new bool*[n];
    for(int i = 0; i < n; ++i){
        isVisited[i] = new bool[n];
        for(int j = 0; j < n; ++j){
            isVisited[i][j] = false;
        }
    }

    queue<Coord> q;
    vector<Coord>::iterator it;
    for(it = startPointSet.begin(); it != startPointSet.end(); ++it){
        //debug
        // printf("%d %d\n", (*it).r, (*it).c);
        
        q.push(*it);
        isVisited[(*it).r][(*it).c] = true;
        ++cnt;
    }

    while(!q.empty()){
        Coord cur = q.front();
        q.pop();

        for(int i = 0; i < 4; ++i){
            int nr = cur.r + dr[i],
                nc = cur.c + dc[i];
            if(isAccesible(cur.r, cur.c, nr, nc, isVisited)){
                q.push(Coord(nr, nc));
                isVisited[nr][nc] = true;
                ++cnt;
            }
        }
    }

    if(result < cnt){
        result = cnt;
    }
    //debug
    // printf("%d\n", result);
}
void simulate(){
    int** isUsed = new int*[n];
    for(int i = 0; i < n; ++i){
        isUsed[i] = new int[n];
        for(int j = 0; j < n; ++j){
            isUsed[i][j] = false;
        }
    }
    vector<Coord> tmpForStartPointSet;
    for(int i = 0; i < k; ++i){
        tmpForStartPointSet.push_back(Coord(-1, -1));
    }
    backTracking(k, 0, 0, tmpForStartPointSet, isUsed);

    vector<vector<Coord>>::iterator it;
    for(it = lstStartPointSet.begin(); it != lstStartPointSet.end(); ++it){
        bfs(*it);
    }
}

int main() {
    getInput();
    simulate();
    printf("%d", result);
    return 0;
}