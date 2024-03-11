#include <iostream>
#include <queue>

using namespace std;

int n, m;
int** map;

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

    while(!q.empty()){
        Coord now = q.front();
        q.pop();

        int nrDown = now.getRow()+1, ncDown = now.getCol(),
            nrRight = now.getRow(), ncRight = now.getCol()+1;
        // 다음 도착지가 목표 지점인 경우
        if(isDest(nrDown, ncDown) || isDest(nrRight, ncRight)){
            return true;
        }
        if(inRange(nrDown, ncDown) && map[nrDown][ncDown] == 1){
            q.push(Coord(nrDown, ncDown));
        }
        if(inRange(nrRight, ncRight) && map[nrRight][ncRight] == 1){
            q.push(Coord(nrRight, ncRight));
        }
    }
    return false;
}

int main() {
    scanf("%d %d", &n, &m);
    map = new int*[n];
    for(int i = 0; i < n; ++i){
        map[i] = new int[m];
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