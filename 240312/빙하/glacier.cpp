#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, t = 0, lastSize;
int** map;  // 1-빙하, 0-물
int** isVisited;    // -1:방문x / 0:녹일 대상 / 1:방문 완료
int dr[4] = {-1, 0, 1, 0},
    dc[4] = {0, 1, 0, -1};

class Coord{
public:
    int r, c;
    Coord(int ir, int ic): r(ir), c(ic) {}
};

void getInput(){
    scanf("%d %d", &n, &m);
    map = new int*[n];
    isVisited = new int*[n];
    for(int i = 0; i < n; ++i){
        map[i] = new int[m];
        isVisited[i] = new int[m];
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            scanf(" %d", &map[i][j]);
            isVisited[i][j] = -1;
        }
    }
}

bool inRange(int r, int c){
    return 0<=r&&r<n && 0<=c&&c<m;
}
void setFirstQueue(queue<Coord>& q){
    for(int i = 0; i < n; ++i){
        q.push(Coord(i, 0));
        q.push(Coord(i, m-1));

        isVisited[i][0] = 1;
        isVisited[i][m-1] = 1;
    }
    for(int i = 0; i < m; ++i){
        q.push(Coord(0, i));
        q.push(Coord(n-1, i));

        isVisited[0][i] = 1;
        isVisited[n-1][i] = 1;
    }
}
void bfs(queue<Coord>& q, vector<Coord>& toMelt){
    while(!q.empty()){
        Coord cur = q.front();
        q.pop();

        for(int i = 0; i < 4; ++i){
            int nr = cur.r + dr[i],
                nc = cur.c + dc[i];
            if(inRange(nr, nc)){
                if(isVisited[nr][nc] != 1 && map[nr][nc] == 0){
                    q.push(Coord(nr, nc));
                    isVisited[nr][nc] = true;
                }
                else if(isVisited[nr][nc] == -1 && map[nr][nc] == 1){
                    toMelt.push_back(Coord(nr, nc));
                    isVisited[nr][nc] = 0;
                }
            }
        }
    }
}
void simulate(){
    queue<Coord> q;
    setFirstQueue(q);

    while(true){
        vector<Coord> toMelt;
        bfs(q, toMelt);
        if(toMelt.empty()){
            break;
        }
        else{
            lastSize = toMelt.size();
            ++t;
            
            vector<Coord>::iterator it;
            for(it = toMelt.begin(); it != toMelt.end(); ++it){
                map[(*it).r][(*it).c] = 0;
                q.push(*it);
            }
        }
    }
}

int main() {
    getInput();
    simulate();
    printf("%d %d", t, lastSize);
    return 0;
}