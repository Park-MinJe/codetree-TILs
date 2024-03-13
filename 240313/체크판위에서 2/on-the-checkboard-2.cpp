#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int r, c;
char** board;

class Coord{
public:
    int r, c;
    Coord(){}
    Coord(int ir, int ic): r(ir), c(ic){}
};

void init(){
    scanf("%d %d", &r, &c);
    board = new char*[r];
    for(int i = 0;i < r; ++i){
        board[i] = new char[c];
        for(int j = 0; j < c; ++j){
            scanf(" %c", &board[i][j]);
        }
    }
}

bool isMovable(char currentColor, int nr, int nc){
    return board[nr][nc] != currentColor;
}
void bfs(){
    int cnt = 0;
    queue<Coord> q;
    q.push(Coord(0, 0));
    for(int i = 0; i < 3; ++i){
        vector<Coord> tmpNextPoint;
        while(!q.empty()){
            Coord cur = q.front();
            q.pop();

            if(i != 2){
                for(int j = cur.r+1; j < r; ++j){
                    for(int k = cur.c+1; k < c; ++k){
                        if(isMovable(board[cur.r][cur.c], j, k) && ((j < r-1) || (k < c-1))){
                            // printf("%d: %d %d\n", i, j, k);
                            tmpNextPoint.push_back(Coord(j, k));
                        }
                    }
                }
            }
            else{
                if((cur.r < r-1) && (cur.c < c-1) && isMovable(board[cur.r][cur.c], r-1, c-1)){
                    ++cnt;
                }
            }
        }

        vector<Coord>::iterator it;
        for(it = tmpNextPoint.begin(); it != tmpNextPoint.end(); ++it){
            q.push(*it);
        }
    }

    printf("%d", cnt);
}

int main() {
    init();
    bfs();
    return 0;
}