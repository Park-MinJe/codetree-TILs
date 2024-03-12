#include <iostream>
#include <queue>

using namespace std;

int n, m;
int** map;
bool** isVisited;
int dr[4] = {-1, 0, 1, 0},
    dc[4] = {0, 1, 0, -1};

class Coord{
public:
    int r, c;
    Coord(int ir, int ic): r(ir), c(ic) {}
};

bool inRange(int r, int c){
    return 0<=r&&r<n && 0<=c&&c<m;
}

bool isAccessable(int r, int c){
    return inRange(r, c) && !isVisited[r][c] && map[r][c] == 1;
}

int search(){
    queue<Coord> q;
    q.push(Coord(0, 0));
    isVisited[0][0] = true;
    while(!q.empty()){
        Coord cur = q.front();
        q.pop();
        
        for(int i = 0; i < 4; ++i){
            int nr = cur.r + dr[i],
                nc = cur.c + dc[i];
            if(isAccessable(nr, nc)){
                if(nr == n-1 && nc == m-1){
                    return 1;
                }
                q.push(Coord(nr, nc));
                isVisited[nr][nc] = true;
            }
        }
    }

    return 0;
}

int main() {
    scanf("%d %d", &n, &m);
    map = new int*[n];
    isVisited = new bool*[n];
    for(int i = 0; i < n; ++i){
        map[i] = new int[m];
        isVisited[i] = new bool[m];
    }
    // map, isVisited 초기화
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            scanf(" %d", &map[i][j]);
            isVisited[i][j] = false;
        }
    }
    printf("%d", search());
    return 0;
}