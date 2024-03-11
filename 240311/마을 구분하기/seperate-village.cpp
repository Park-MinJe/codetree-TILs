#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n;
int** map;
bool** isVisitied;
vector<int> result;

int dr[4] = {-1, 0, 1, 0},
    dc[4] = {0, 1, 0, -1};

class Coord{
public:
    int r, c;
    Coord(int ir, int ic) : r(ir), c(ic) {}
};

bool inRange(int r, int c){
    return 0<=r&&r<n && 0<=c&&c<n;
}

void search(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(isVisitied[i][j] || map[i][j] == 0) continue;

            queue<Coord> q;
            q.push(Coord(i, j));

            int cnt = 0;
            while(!q.empty()){
                Coord cur = q.front();
                q.pop();
                for(int k = 0; k < 4; ++k){
                    int nr = cur.r + dr[k],
                        nc = cur.c + dc[k];
                    if(inRange(nr, nc) && !isVisitied[nr][nc] && map[nr][nc] == 1){
                        // printf("%d-%d-%d: %d %d\n", i, j , k, nr, nc);
                        q.push(Coord(nr, nc));
                        isVisitied[nr][nc] = true;
                        ++cnt;
                    }
                }
            }
            
            result.push_back(cnt);
            for(int k = result.size()-2; k >= 0; --k){
                if(result[k] > result[k+1]){
                    int tmp = result[k];
                    result[k] = result[k+1];
                    result[k+1] = tmp;
                }
                else{
                    break;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    map = new int*[n];
    isVisitied = new bool*[n];
    for(int i = 0; i < n; ++i){
        map[i] = new int[n];
        isVisitied[i] = new bool[n];
        for(int j = 0; j < n; ++j){
            isVisitied[i][j] = false;
        }
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf(" %d", &map[i][j]);
        }
    }
    search();

    printf("%d\n", result.size());
    vector<int>::iterator it;
    for(it = result.begin(); it != result.end(); ++it){
        printf("%d\n", *it);
    }
    return 0;
}