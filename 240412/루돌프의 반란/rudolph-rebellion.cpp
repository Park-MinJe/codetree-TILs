#include <iostream>
//#include <unordered_map>
#include <map>
#include <climits>

#define MAX_N 51
#define MAX_P 31

using namespace std;

class Obj {  // 산타나 루돌프의 좌표
public:
    int r, c;
    Obj() {}
    Obj(int ir, int ic) : r(ir), c(ic) {}

    long long getDist(int nr, int nc);
};
class Santa : public Obj {
public:
    int idx,
        score,
        dirIdx,
        isSturned;
    bool isDead;
    Santa() {}
    Santa(int iIdx, int ir, int ic) : Obj(ir, ic), idx(iIdx) {
        score = 0;
        isSturned = 0;
        isDead = false;
    }

    void serialReaction(int by, int roodolphDirIdx);
    void collapse();
    void move();
};
class Roodolph : public Obj {
public:
    int dirIdx;
    Roodolph() {}
    Roodolph(int ir, int ic) : Obj(ir, ic) {}

    void setDir();
    void move();
    void collapse();
};

int N, M, P, C, D,
    tmpIdx, tmpR, tmpC,
    roodolphDr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 },    // 루돌프 R방향 이동 (북, 북동, 동, 동남, 남, 남서, 서, 서북)
    roodolphDc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 },    // 루돌프 C방향 이동 (북, 북동, 동, 동남, 남, 남서, 서, 서북)
    santaDr[4] = { -1, 0, 1, 0 },                     // 산타 R방향 이동 (북, 동, 남, 서)
    santaDc[4] = { 0, 1, 0, -1 },                     // 산타 C방향 이동 (북, 동, 남, 서)

    minDistSantaNum = 0,                            // 가장 가까운 산타까지의 번호 (초기 값: 0)

    //lstSantaNum[MAX_P],                             // 산타 번호 목록
    mapSantaNum[MAX_N][MAX_N];                      // 산타 번호 맵

long long minDist = MAX_N * MAX_N + MAX_N * MAX_N;      // 가장 가까운 산타까지의 거리
// unordered_map<int, long long> lstDistToSanta;       // 루돌프에서 산타까지 거리. 죽으면 삭제
map<int, long long> lstDistToSanta;       // 루돌프에서 산타까지 거리. 죽으면 삭제

Roodolph* roodolph;                                 // 루돌프 포인터
// unordered_map<int, Santa*> santaMap;                // <산타 번호, 산타 포인터>
map<int, Santa*> santaMap;                // <산타 번호, 산타 포인터>

// 해당 좌표가 map 안의 좌표인가
bool inRange(int nr, int nc);

// 산타가 움직일 수 있는 칸인가
bool isMovable(int nr, int nc);

void updateDist(int santaNum, int santaR, int santaC);

void getInput();

void simulate();

void printScore();

int main() {
    getInput();
    simulate();
    printScore();
    return 0;
}

/***** functions *****/
// 해당 좌표가 map 안의 좌표인가
bool inRange(int nr, int nc) {
    return 1 <= nr && nr <= N && 1 <= nc && nc <= N;
}

// 산타가 움직일 수 있는 칸인가
bool isMovable(int nr, int nc) {
    return inRange(nr, nc) && mapSantaNum[nr][nc] == 0;
}

void updateDist(int santaNum, int santaR, int santaC) {
    lstDistToSanta[santaNum] = roodolph->getDist(santaR, santaC);

    if (minDistSantaNum == 0                     // 처음인 경우
        || minDist > lstDistToSanta[santaNum]       // 최소 거리보다 짧은 경우
        || (minDist == lstDistToSanta[santaNum]     // 최소 거리와 같은 경우
            && (
                santaMap[minDistSantaNum]->r < santaMap[santaNum]->r
                || (santaMap[minDistSantaNum]->r == santaMap[santaNum]->r
                    && santaMap[minDistSantaNum]->c < santaMap[santaNum]->c
                    )
                )
            )
        )
    {
        minDist = lstDistToSanta[santaNum];
        minDistSantaNum = santaNum;
    }
}

void getInput() {
    // N, M, P, C, D
    cin >> N >> M >> P >> C >> D;

    // 루돌프 초기 위치(r, c)
    cin >> tmpR >> tmpC;
    roodolph = new Roodolph(tmpR, tmpC);

    // 산타 초기 위치
    for (int i = 0; i < P; ++i) {
        cin >> tmpIdx >> tmpR >> tmpC;

        //lstSantaNum[i] = tmpIdx;
        mapSantaNum[tmpR][tmpC] = tmpIdx;
        santaMap.insert(
            make_pair(
                tmpIdx,
                new Santa(tmpIdx, tmpR, tmpC)
            )
        );

        // 산타와 루돌프 간 거리 갱신
        updateDist(tmpIdx, tmpR, tmpC);
    }
}

void simulate() {
    // M개의 턴
    for (int i = 0; i < M; ++i) {     // 종료 조건 1: M번 종료
        // debug
        // cout << "i = " << i << "\n";

        // 루돌프 이동
        roodolph->move();
        // debug
        // cout << "루돌프::(" << roodolph->r << ", " << roodolph->c << ")\n";
        roodolph->collapse();
        minDistSantaNum = 0;
        //for (int j = 0; j < P; ++j) {
        //    if (santaMap.find(lstSantaNum[j]) != santaMap.end()) {
        //        if (!santaMap[lstSantaNum[j]]->isDead) {
        //            updateDist(lstSantaNum[j], santaMap[lstSantaNum[j]]->r, santaMap[lstSantaNum[j]]->c);

        //            // debug
        //            cout << "산타" << lstSantaNum[j] << "와 거리 = " << lstDistToSanta[lstSantaNum[j]] << "\n";
        //        }
        //    }
        //}
        
        map<int, Santa*>::iterator it;
        for (it = santaMap.begin(); it != santaMap.end(); ++it) {
            if (!(it->second->isDead)) {
                updateDist(it->first, it->second->r, it->second->c);

                // debug
                // cout << "산타" << it->first << "와 거리  = " << lstDistToSanta[it->first] << "\n";
            }
        }

        // debug
        // cout << "루돌프 이동 후::";
        // printScore();
        // cout << "\n";

        // 산타들 이동
        //for (int j = 0; j < P; ++j) {
        for(it = santaMap.begin(); it != santaMap.end(); ++it){
            //Santa*& curSanta = santaMap[lstSantaNum[j]];
            Santa*& curSanta = it->second;
            if (!curSanta->isDead) {
                // debug
                // cout<<"산타"<<curSanta->idx<<"::"<<curSanta->isSturned<<"\n";
                // cout<<"BEFOR::산타"<<curSanta->idx<<"::("<<curSanta->r<<", "<<curSanta->c<<")\n";

                if (curSanta->isSturned == 0)
                    curSanta->move();

                // debug
                // else {
                //     cout << "산타" << curSanta->idx << "기절 상태 남은 턴 수 = " << curSanta->isSturned << "\n";
                // }
                // cout << "AFTER::산타" << curSanta->idx << "::(" << curSanta->r << ", " << curSanta->c << ")\n";
            }
        }
        // debug
        // cout << "산타 이동 후::";
        // printScore();
        // cout << "\n";

        // 종료 조건 판별
        if (lstDistToSanta.empty()) { // 종료 조건 2: 모든 산타 탈락
            break;
        }

        // 다음 턴 준비
        // updateDist
        minDistSantaNum = 0;
        for (it = santaMap.begin(); it != santaMap.end(); ++it) {
        //for (int j = 0; j < P; ++j) {
            Santa*& curSanta = it->second;
            //debug
            // cout<<"산타"<<curSanta->idx<<" isDead = "<<curSanta->isDead<<"\n";
            //if (lstDistToSanta.find(lstSantaNum[j]) != lstDistToSanta.end()) {
                //debug
                // cout<<"산타"<<curSanta->idx<<" isDead = "<<curSanta->isDead<<"\n";

            if (!curSanta->isDead) {
                updateDist(it->first, curSanta->r, curSanta->c);
                // debug
                // cout<<"Dist to "<<minDistSantaNum<<" = "<<minDist<<"\n";
                // cout<<"FINAL::산타"<<curSanta->idx<<"::("<<curSanta->r<<", "<<curSanta->c<<")\n";

                ++(curSanta->score);     // 생존 산타 점수 증가

                // 기절 상태 -1
                if (curSanta->isSturned > 0)
                    --(curSanta->isSturned);
            }
            //}
        }

        // debug
        // cout << "턴 종료 후::";
        // printScore();
        // cout << "\n\n";
    }
}

void printScore() {
    int tmpCntAlive = 0;

    map<int, Santa*>::iterator it;
    for (it = santaMap.begin(); it != santaMap.end(); ++it) {
    //for (int i = 0; i < P; ++i) {
        //cout << santaMap[lstSantaNum[i]]->score << " ";
        cout << it->second->score << " ";

        // debug
        // if (!(it->second->isDead)) {
        //     ++tmpCntAlive;
        // }
    }

    // debug
    // cout << "\n생존 산타 수 = " << tmpCntAlive << "\n";
}

/***** class Obj *****/
long long Obj::getDist(int nr, int nc) {
    return (nr - r) * (nr - r) + (nc - c) * (nc - c);
}

/***** class Santa *****/
void Santa::serialReaction(int by, int dirIdx) { // by::0->루돌프 / 1->산타
    // debug
    // cout << "by " << by << ", dirIdx = " << dirIdx << "\n";

    int originSantaNum = mapSantaNum[r][c];
    Santa*& originSanta = santaMap[originSantaNum]; // 충돌할 기존 산타

    int prevR = originSanta->r,         // 충돌할 기존 산타의 이동 전 좌표
        prevC = originSanta->c;
    if (by == 0) {
        originSanta->r += roodolphDr[dirIdx];   // 이동 후 좌표
        originSanta->c += roodolphDc[dirIdx];
    }
    else if (by == 1) {
        originSanta->r -= santaDr[dirIdx];   // 이동 후 좌표
        originSanta->c -= santaDc[dirIdx];
    }

    mapSantaNum[prevR][prevC] = 0;      // 이동 전 좌표 초기화

    if (!inRange(originSanta->r, originSanta->c)) {   // 이동 후 좌표가 맵 밖인 경우
        lstDistToSanta.erase(originSanta->idx);
        originSanta->isDead = true;
        // debug
        // cout<<"Line 241::Santa"<<idx<<" 퇴출\n";
    }
    else {
        if (mapSantaNum[originSanta->r][originSanta->c] > 0) {    // 이동할 좌표에 다른 산타 존재
            // 연쇄 반응
            originSanta->serialReaction(by, dirIdx);
        }

        mapSantaNum[originSanta->r][originSanta->c] = originSanta->idx;
    }
}

void Santa::collapse() {
    if (r == roodolph->r && c == roodolph->c) {   // 루돌프와 추돌
        score += D;
        int prevR = r,
            prevC = c;
        r -= santaDr[dirIdx] * D;
        c -= santaDc[dirIdx] * D;
        isSturned += 2;
        //debug
        // cout<<"Line 262::산타"<<idx<<" 기절 +1 -> "<<isSturned<<"\n";

        mapSantaNum[prevR][prevC] = 0;  // 이동 전 좌표 초기화

        if (!inRange(r, c)) {   // 지도 밖으로 나가는 경우
            lstDistToSanta.erase(idx);
            this->isDead = true;
            // debug
            // cout<<"Line 270::Santa"<<idx<<" 퇴출\n";
        }
        else {
            if (mapSantaNum[r][c] > 0) {    // 이동할 좌표에 다른 산타 존재
                // 연쇄 반응
                this->serialReaction(1, dirIdx);            // 이동할 좌표에서의 연쇄 반응
            }

            mapSantaNum[r][c] = idx;     // 연쇄 반응 후 이동할 좌표 갱신
        }
    }
}

void Santa::move() {
    int trgtR, trgtC, nr, nc;
    bool isMoved = false;
    long long
        newDist = LLONG_MAX,
        nextDist;

    if (lstDistToSanta.find(idx) != lstDistToSanta.end())
        newDist = lstDistToSanta[idx];

    for (int i = 0; i < 4; ++i) {
        nr = r + santaDr[i];
        nc = c + santaDc[i];

        if (isMovable(nr, nc)) {      // 이동할 수 있는 칸
            //debug
            // cout<< "산타"<<idx<<" 이동::("<<nr<<", "<<nc<<")\n";
            nextDist = roodolph->getDist(nr, nc);

            // debug
            // printf("(%d,%d)->(%d,%d) 이동 시 갱신되는 루돌프와의 거리 : %lld -> %lld\n", r, c, nr, nc, newDist, nextDist);

            if (newDist > nextDist) {      // 루돌프와 거리가 가까워지는 방향
                //debug
                // cout<< "산타"<<idx<<" 이동으로 인한 최소 거리 갱신: " <<lstDistToSanta[idx]<<" "<<newDist<<"\n";
                trgtR = nr;
                trgtC = nc;
                newDist = nextDist;
                dirIdx = i;

                isMoved = true;
            }
        }
    }

    if (isMoved) {
        mapSantaNum[r][c] = 0;              // 기존 위치 정보 삭제

        // 이동
        r = trgtR;
        c = trgtC;
        mapSantaNum[r][c] = idx;
        lstDistToSanta[idx] = newDist;

        this->collapse();
    }
}

/***** class Roodolph *****/
void Roodolph::setDir() {
    long long newMinDist = minDist;

    for (int i = 0; i < 8; ++i) {
        int nr = r + roodolphDr[i],
            nc = c + roodolphDc[i];
        if (inRange(nr, nc)) {
            long long newDist = santaMap[minDistSantaNum]->getDist(nr, nc);
            // debug
            // cout<<"("<<nr<<", "<<nc<<")::"<<newMinDist <<" "<< newDist<<"\n";

            if (newMinDist > newDist) {
                newMinDist = newDist;
                dirIdx = i;
            }
        }
    }
}

void Roodolph::move() {
    this->setDir();
    // debug 루돌프 방향
    // cout<<roodolph->dirIdx<<"\n";

    r += roodolphDr[dirIdx];
    c += roodolphDc[dirIdx];
    // debug 루돌프 이동
    // cout<<r<<" "<<c<<"\n";
}

void Roodolph::collapse() {    // 산타와 충돌
    Santa*& curTrgt = santaMap[minDistSantaNum];    // 충돌할 산타

    if (curTrgt->r == r && curTrgt->c == c) { // 충돌한 경우
        int prevR = curTrgt->r,     // 이동 전 R
            prevC = curTrgt->c;     // 이동 전 C

        curTrgt->score += C;
        curTrgt->r += roodolphDr[dirIdx] * C;
        curTrgt->c += roodolphDc[dirIdx] * C;
        if (curTrgt->isSturned != 0) {
            ++(curTrgt->isSturned);
        }
        else {
            curTrgt->isSturned += 2;
        }
        
        //debug
        // cout<<"Line 355::산타"<<curTrgt->idx<<" 기절 +1 -> "<<curTrgt->isSturned<<"\n";

        mapSantaNum[prevR][prevC] = 0;  // 이동 전 좌표 초기화

        if (!inRange(curTrgt->r, curTrgt->c)) {   // 지도 밖으로 나가는 경우
            lstDistToSanta.erase(minDistSantaNum);
            curTrgt->isDead = true;
            // debug
            // cout<<"Line 363::산타"<<curTrgt->idx<<" 퇴출\n";
            // cout<<"From "<<prevR<<" "<<prevC<<"\n";
            // cout<<"To "<<curTrgt->r<<" "<<curTrgt->c<<"\n";
            // cout<<"By dir = "<<dirIdx<<"\n";
            // cout<<"(dr, dc) = "<< roodolphDr[dirIdx]*C<<", "<<roodolphDc[dirIdx]*C<<"\n";
        }
        else {
            if (mapSantaNum[curTrgt->r][curTrgt->c] > 0) {    // 이동할 좌표에 다른 산타 존재
                // 연쇄 반응
                curTrgt->serialReaction(0, dirIdx);            // 이동할 좌표에서의 연쇄 반응
            }

            mapSantaNum[curTrgt->r][curTrgt->c] = curTrgt->idx;     // 연홰 반응 후 이동할 좌표 갱신
        }
    }
}