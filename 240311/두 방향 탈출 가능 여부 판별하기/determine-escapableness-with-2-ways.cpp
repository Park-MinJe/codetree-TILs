#include <iostream>
#include <queue>

using namespace std;

int n, m;
int** map;
bool** isVisited;

class Coord{
private:
    int r, c;
public:
    Coord(int ir, int ic) : r(ir), c(ic){}
    int getRow(){
        return r;
    }
    int getCol(){
        return c;
    }
};

bool inRange(int r, int c){
    return 0<=r&&r<n && 0<=c&&c<m;
}
bool isDest(int r, int c){
    return r == n-1 && c == m-1;
}

bool dfs(){
    queue<Coord> q;
    q.push(Coord(0, 0));
    isVisited[0][0] = true;

    while(!q.empty()){
        Coord now = q.front();
        q.pop();

        int nrDown = now.getRow()+1, ncDown = now.getCol(),
            nrRight = now.getRow(), ncRight = now.getCol()+1;
        // 다음 도착지가 목표 지점인 경우
        if(isDest(nrDown, ncDown) || isDest(nrRight, ncRight)){
            return true;
        }
        if(inRange(nrDown, ncDown) && map[nrDown][ncDown] == 1 && !isVisited[nrDown][ncDown]){
            q.push(Coord(nrDown, ncDown));
            isVisited[nrDown][ncDown] = true;
        }
        if(inRange(nrRight, ncRight) && map[nrRight][ncRight] == 1 && !isVisited[nrRight][ncRight]){
            q.push(Coord(nrRight, ncRight));
            isVisited[nrRight][ncRight] = true;
        }
    }
    return false;
}

int main() {
    scanf("%d %d", &n, &m);
    map = new int*[n];
    isVisited = new bool*[n];
    for(int i = 0; i < n; ++i){
        map[i] = new int[m];
        isVisited[i] = new bool[m];
        for(int j = 0; j<m; ++j){
            isVisited[i][j] = false;
        }
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            scanf(" %d", &map[i][j]);
        }
    }

    if(dfs()) printf("%d", 1);
    else printf("%d", 0);

    for(int i = 0; i < n; ++i){
        delete[] map[i];
    }
    delete[] map;

    return 0;
}