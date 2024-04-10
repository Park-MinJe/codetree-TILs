#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <queue>
#include <vector>

// 입력 변수 최대값 + 1
#define MAX_L   41
#define MAX_N   31
#define MAX_Q   101
#define MAX_K   101

// map의 유형
#define BLANK   0
#define TRAP    1
#define WALL    2

using namespace std;

/***************************************************************************/
/* Class 정의                                                              */
/***************************************************************************/
class Knight{
public:
    int idx,            // 고유번호 1~N
        r, c,           // 위치
        h, w,           // 세로, 가로
        k,              // 체력
        totalDamage;    // 받은 피해
    bool isDead;        // 체력이 0이하->true, 양수->false

    Knight();           // 기본 생성자

    bool move(int opDir);   // 이동
    void damage();          // 밀림으로 인한 피해 계산 및 체력 갱신
};

class Op{
public:
    int i, d;   // 기사 번호, 방향
    Op();
};

/***************************************************************************/
/* 변수 정의                                                               */
/***************************************************************************/
int L, N, Q,                    // 체스판 크기, 기사 수, 명령 수
    dr[4] = {-1, 0, 1, 0},
    dc[4] = {0, 1, 0, -1},
    map[MAX_L][MAX_L],          // 체스판
    mapForKnightIdx[MAX_L][MAX_L],
                                // 지도 상 기사의 위치
    traps[MAX_L][MAX_L],        // [(r,c), (r+h,c+w)] 영역 함정 갯수. *사용 보류*
    ansTotalDamage = 0;
unordered_map<int, Knight*> mapKnightsInfo; // 기사 정보 Map. 포인터 초기화 필요
// unordered_map<int, bool>    mapKnightIsMoved;
                                // 기사가 해당 턴에 이미 방문된 경우
queue<Op*> qOpList;             // 명령어 목록 큐. 포인터 초기화 필요

/***************************************************************************/
/* 함수 정의                                                               */
/***************************************************************************/
void init();                    // 입력 처리 및 변수 초기화

bool inRange(int nr, int nc, int curH, int curW);
                                // 이동할 좌표가 map 내인가
bool isWall(int nr, int nc, int curH, int curW);
                                // 이동할 좌표가 벽인가
unordered_set<int> isOther(int nr, int nc, int curKIdx, int curH, int curW);
                                // 이동할 좌표가 포함된 영역에 curKIdx 이외의 기사가 있는가
                                // 있다면 해당 기사들의 idx 반환
                                // 없다면 기사의 번호가 될 수 없는 0 반환

void simulate();                // 시뮬레이션 수행
int calcTotalDamageAlive();     // 살아있는 기사들이 총 받은 피해의 합 출력

/***************************************************************************/
/* main 함수                                                               */
/***************************************************************************/
int main() {
    init();                         // 입력 처리 및 변수 초기화
    simulate();                     // 시뮬레이션 진행
    cout<<calcTotalDamageAlive();   // 결과 출력
    return 0;
}

/***************************************************************************/
/* 함수 구현                                                               */
/***************************************************************************/
void init(){                    // 입력 처리 및 변수 초기화
    //debug
    // cout<<"init 시작---\n";

    cin>>L>>N>>Q;

    // 칸의 유형
    for(int i = 1; i <= L; ++i){
        for(int j = 1; j <= L; ++j){
            cin>>map[i][j];     // 0->빈칸, 1->함정, 2->벽
        }
    }

    // 기사 정보
    for(int i = 1; i <= N; ++i){
        Knight* newKnight = new Knight();
        newKnight->idx = i;
        cin>>newKnight->r>>newKnight->c>>newKnight->h>>newKnight->w>>newKnight->k;

        // mapKnightIsMoved.insert(
        //     make_pair(i, false)
        // );

        mapKnightsInfo.insert(
            make_pair(i, newKnight)
        );

        // mapForKnightIdx에 기사 위치 갱신
        for(int rj = 0; rj < newKnight->h; ++rj){
            for(int cj = 0; cj < newKnight->w; ++cj){
                mapForKnightIdx[newKnight->r + rj][newKnight->c + cj] = i;
            }
        }
    }

    // 명령 정보
    for(int i = 1; i <= Q; ++i){
        Op* newOp = new Op();
        cin>>newOp->i>>newOp->d;

        qOpList.push(newOp);
    }

    //debug
    // cout<<"---init 종료\n";
    // for(int i = 1; i <= L; ++i){
    //     for(int j = 1; j <= L; ++j){
    //         cout<<mapForKnightIdx[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
}

bool inRange(int nr, int nc, int curH, int curW){   // 이동할 좌표가 map 내인가
    int upperR = nr + curH,
        upperC = nc + curW;
    for(int i = nr; i < upperR; ++i){
        for(int j = nc; j < upperC; ++j){
            if(!(1<=i&&i<=L && 1<=j&&j<=L)){
                return false;
            }
        }
    }
    return true;
}
bool isWall(int nr, int nc, int curH, int curW){    // 이동할 좌표가 포함된 영역에 벽이 있는가
    int upperR = nr+curH,
        upperC = nc+curW;
    for(int i = nr; i < upperR; ++i){
        for(int j = nc; j < upperC; ++j){

            if(map[i][j] == WALL){
                // debug
                // printf("map[%d][%d] == WALL\n", i, j);
                return true;
            }
        }
    }
    return false;
}
unordered_set<int> isOther(int nr, int nc, int curKIdx, int curH, int curW){
                                                    // 이동할 좌표가 포함된 영역에 다른 기사가 있는가
    unordered_set<int> rt;

    for(int i = nr; i < nr+curH; ++i){
        for(int j = nc; j < nc+curW; ++j){
            if(mapForKnightIdx[i][j] != 0 && mapForKnightIdx[i][j] != curKIdx
            && rt.find(mapForKnightIdx[i][j]) == rt.end()){
                // 이동하려는 영역에 기사가 이미 있고, 다른 기사인 경우
                rt.insert(mapForKnightIdx[i][j]);
            }
        }
    }

    return rt;
}

void simulate(){                                    // 시뮬레이션 수행
    //debug
    // cout<<"simulate 시작---\n";

    int i = 0;
    while(!qOpList.empty()){
        // debug
        // cout<<"\n"<<i<<"\n";

        // 방문 여부 초기화
        // unordered_map<int, bool>::iterator isVisitedIt;
        // for(isVisitedIt = mapKnightIsMoved.begin(); isVisitedIt != mapKnightIsMoved.end(); ++isVisitedIt){
        //     isVisitedIt->second = false;
        // }

        Op*& curOp = qOpList.front();               // 현재 수행할 명령어
        qOpList.pop();

        int curKnightIdx = curOp->i,
            curDir = curOp->d;

        if(mapKnightsInfo.find(curKnightIdx) != mapKnightsInfo.end()){
            // 기사가 있고 생존한 경우
            Knight*& curKnight = mapKnightsInfo[curKnightIdx];
            
            // 기사 이동 연산
            curKnight->move(curDir);
        }
        else{
            // 기사가 없거나 이미 사망한 경우
        }

        //debug
        // ++i;
    }

    //debug
    // cout<<"---simulate 종료\n";
}

int calcTotalDamageAlive(){     // 살아있는 기사들이 총 받은 피해의 합 출력
    int rt = 0;

    unordered_map<int, Knight*>::iterator aliveIt;
    for(aliveIt = mapKnightsInfo.begin(); aliveIt != mapKnightsInfo.end(); ++aliveIt){
        rt += aliveIt->second->totalDamage;
    }

    return rt;
}

/***************************************************************************/
/* Class 구현                                                              */
/***************************************************************************/
/*
 * int idx,            // 고유번호 1~N
       r, c,            // 위치
       h, w,            // 세로, 가로
       k,               // 체력
       totalDamage;     // 받은 피해
 * bool isDead;         // 체력이 0이하->true, 양수->false
 */
Knight::Knight(){               // 기본 생성자
    totalDamage = 0;
    isDead = false;
}

bool Knight::move(int opDir){            // 이동
    // debug
    // cout<<this->idx<<"이동 시작---\n";
    // mapKnightIsMoved[idx] = true;

    int nr = r + dr[opDir],
        nc = c + dc[opDir];     // 이동할 좌표 후보
    // debug
    // printf("기사%d %d 방향 이동 가능 여부 판단 시작::(%d, %d)->(%d, %d)\n", this->idx, opDir, this->r, this->c, nr, nc);
    
    if(!inRange(nr, nc, this->h, this->w) || isWall(nr, nc, this->h, this->w)){
        // debug
        // cout<<this->idx<<"가 지도 밖이거나 벽이 포함되어 종료\n";

        // 지도 밖이거나 벽이 포함된 경우
        return false;
    }
    if(this->isDead){
        // 죽은 기사
        return false;
    }

    unordered_set<int> possibleKnights = isOther(nr, nc, this->idx, this->h, this->w);
    unordered_set<int>::iterator possibleIt;
    for(possibleIt = possibleKnights.begin(); possibleIt != possibleKnights.end(); ++possibleIt){
        // debug
        // cout<<this->idx<<"이동하는 길에 다른 기사"<<*possibleIt<<" 존재\n";

        // 다른 기사 존재
        Knight*& nextK = mapKnightsInfo[
            *possibleIt
        ];
        if(!nextK->move(opDir)){
            // debug
            // cout<<this->idx<<"가 민 "<<nextK->idx<<"가 움직일 수 없음\n";

            // 연쇄 이동해야하는 기사가 이동할 수 없는 상황인 경우
            return false;
        }
        else{
            // debug
            // cout<<this->idx<<"가 민 "<<nextK->idx<<"가 움직일 수 있음\n";

            // 밀림
            nextK->damage();
        }
    }

    // 이동 가능
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            mapForKnightIdx[r+i][c+j] = 0;              // 원래 위치 초기화
        }
    }
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            mapForKnightIdx[nr+i][nc+j] = this->idx;    // 이동할 위치에 표시
        }
    }

    // debug
    // printf("- 기사%d 좌표 이동::(%d, %d) -> (%d, %d)\n", this->idx, r, c, nr, nc);
    // for(int i = 1; i <= L; ++i){
    //     for(int j = 1; j <= L; ++j){
    //         cout<<mapForKnightIdx[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }

    // 좌표 갱신
    r = nr; c = nc;

    // debug
    // cout<<"---"<<this->idx<<" 좌표 갱신 후 종료\n";
    return true;
}
void Knight::damage(){          // 밀림으로 인한 피해 계산 및 체력 갱신
    // 이번 턴에 받는 피해
    int curDamage = 0;
    for(int idr = 0; idr < h; ++idr){
        for(int idc = 0; idc < w; ++idc){
            if(map[r+idr][c+idc] == TRAP){
                // 함정이라면
                ++curDamage;
            }
        }
    }
    
    // 기사의 상태 갱신과 총 피해 계산
    if(k <= curDamage){
        this->isDead = true;
        // 총 피해에 추가
        this->totalDamage += k;
        //debug
        // cout<<this->idx<<"기사 피해 업데이트::"<<this->totalDamage<<"\n";

        // 사망 처리
        mapKnightsInfo.erase(this->idx);
        // mapKnightIsMoved.erase(this->idx);
        for(int i = r; i < r+h; ++i){
            for(int j = c; j < c+w; ++j){
                mapForKnightIdx[i][j] = 0;
            }
        }

        // debug
        // cout<<this->idx<<"기사 사망\n";
    }
    else{
        // 총 피해에 추가
        this->totalDamage += curDamage;
        //debug
        // cout<<this->idx<<"기사 피해 업데이트::"<<this->totalDamage<<"\n";
    }
}

/*
 * int i, d;   // 기사 번호, 방향
 */
Op::Op(){}