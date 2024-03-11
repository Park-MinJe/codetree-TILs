#include <iostream>
#include <queue>

using namespace std;

int n, m,
    minK = 101, maxK = 0;
int** map;
int dr[4] = {-1, 0, 1, 0},
    dc[4] = {0, 1, 0, -1};

class Coord{
public:
    int r, c;
    Coord(int ir, int ic): r(ir), c(ic){}
};

bool inRange(int r, int c){
    return 0<=r&&r<n && 0<=c&&c<m;
}

void search(){
    int resultCnt = -1,
        resultK;
    for(int k = minK; k <= maxK; ++k){
        int cnt = 0;
        bool** isVisited;
        isVisited = new bool*[n];
        for(int i = 0; i <n; ++i){
            isVisited[i] = new bool[m];
            for(int j = 0; j < m; ++j){
                if(map[i][j] <= k){
                    isVisited[i][j] = true;
                }
                else{
                    isVisited[i][j] = false;
                }
            }
        }

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(!isVisited[i][j]){
                    // debug
                    //printf("r: %d/c: %d\n", i, j);
                    queue<Coord> q;
                    q.push(Coord(i, j));
                    isVisited[i][j] = true;
                    while(!q.empty()){
                        Coord cur = q.front();
                        q.pop();

                        for(int i = 0; i < 4; ++i){
                            int nr = cur.r + dr[i],
                                nc = cur.c + dc[i];

                            if(inRange(nr, nc) && !isVisited[nr][nc]){
                                q.push(Coord(nr, nc));
                                isVisited[nr][nc] = true;
                            }
                        }
                    }
                    ++cnt;
                }
            }
        }
        //printf("%d %d\n", k, cnt);
        if(resultCnt < cnt){
            resultCnt = cnt;
            resultK = k;
        }
        
        for(int i = 0; i < n; ++i){
            delete[] isVisited[i];
        }
        delete[] isVisited;
    }
    printf("%d %d", resultK, resultCnt);
}

int main() {
    scanf("%d %d", &n, &m);
    map = new int*[n];
    for(int i = 0; i <n; ++i){
        map[i] = new int[m];
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            scanf(" %d", &map[i][j]);
            if(minK > map[i][j]){
                minK = map[i][j];
            }
            if(maxK < map[i][j]){
                maxK = map[i][j];
            }
        }
    }

    search();

    for(int i = 0; i < n; ++i){
        delete[] map[i];
    }
    delete[] map;

    return 0;
}