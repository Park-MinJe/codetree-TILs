#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <climits>
#include <deque>
#include <unordered_map>
#include <queue>

#define MAX_NM 10
#define MAX_K 1000
#define MAX_POWER 5000

using namespace std;

/**********class 정의**********/
class Tower {
public:
    int r, c,
        power,
        usedTurn;
    Tower();
};

/**********변수 정의**********/
int N, M, K,
map[MAX_NM + 1][MAX_NM + 1],
mapTowerIdx[MAX_NM + 1][MAX_NM + 1],
ansMaxPower = 0,
cntWorkingTower = 0,
handicap,
curAttackPower,                 // 공격 시, handicap이 적용된 공격자의 공격력
curAttackPowerHalf,
lazerDr[4] = { 0, 1, 0, -1 },   // 우하좌상
lazerDc[4] = { 1, 0, -1, 0 },
bombDr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 },  // 폭탄의 영향 범위
bombDc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
//vector<Tower*> lstWorkingTower;
unordered_map<int, Tower*> lstWorkingTower;
Tower* curAttacker;
Tower* curTarget;
bool isVisited[MAX_NM + 1][MAX_NM + 1];
bool isRelated[MAX_NM + 1][MAX_NM + 1];     // 공격과 관련되었는지
pair<int, int> mapShortCut[MAX_NM + 1][MAX_NM + 1];

/**********함수 정의**********/
void init();
void simulate();
void printMaxPower();

bool compareTowerPower(Tower*& t1, Tower*& t2);     // 공격자 선정 우선 순위를 위한 정렬에 사용
bool compareTowerPowerWithVector(pair<int, Tower*>& p1, pair<int, Tower*>& p2);

bool inRange(int r, int c);
int searchRoute(int minLen, int curLen, int curR, int curC);    // 공격 대상까지 최단 거리 계산
bool searchRouteBfs();
void lazer();        // 레이저로 인한 피해 계산
void bombExplose();                 // 폭탄이 터지는 경우

int main() {
    init();
    simulate();
    printMaxPower();
    return 0;
}

/**********함수 구현**********/
void init() {
    cin >> N >> M >> K;
    handicap = N + M;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> map[i][j];

            if (map[i][j] > 0) {
                // 부서지지 않은 포탑 위치
                mapTowerIdx[i][j] = cntWorkingTower;

                // 부서지지 않은 포탑 개수 세기
                ++cntWorkingTower;

                // lstWorkingTower에 추가
                Tower* newTower = new Tower();
                newTower->r = i;
                newTower->c = j;
                newTower->power = map[i][j];
                newTower->usedTurn = 0;

                //lstWorkingTower.push_back(newTower);
                lstWorkingTower.insert(
                    make_pair(
                        mapTowerIdx[i][j], newTower
                    )
                );
            }
        }
    }
}
void simulate() {
    for (int i = 0; i < K; ++i) {
        // debug
        // cout << "\n" << (i + 1) << "번째 턴\n";

        // 1. 공격자 선정
        vector<pair<int, Tower*>> vecToSort(lstWorkingTower.begin(), lstWorkingTower.end());
        //sort(vecToSort.begin(), vecToSort.end(), compareTowerPower);
        sort(vecToSort.begin(), vecToSort.end(), compareTowerPowerWithVector);
        // debug
        // vector<pair<int, Tower*>>::iterator itDebug;
        // for (itDebug = vecToSort.begin(); itDebug != vecToSort.end(); ++itDebug) {
        //     cout << "Tower" << itDebug->first << "::(" << itDebug->second->r << ", " << itDebug->second->c << "), power = " << itDebug->second->power << "\n";
        // }

        //curAttacker = lstWorkingTower[0];
        curAttacker = vecToSort[0].second;
        curAttacker->usedTurn = i + 1;
        isRelated[curAttacker->r][curAttacker->c] = true;   // 공격과 연관됨. 포탑 정비 대상 제외

        curAttackPower = curAttacker->power + handicap;
        curAttackPowerHalf = curAttackPower / 2;
        curAttacker->power = curAttackPower;
        // debug
        //cout << i << "턴 공격자::(" << curAttacker->r << ", " << curAttacker->c << ")\n";

        // 2. 공격자의 공격
        //curTarget = lstWorkingTower[cntWorkingTower - 1];
        curTarget = vecToSort[cntWorkingTower - 1].second;
        isRelated[curTarget->r][curTarget->c] = true;       // 공격과 연관됨. 포탑 정비 대상 제외
        //cout << i << "턴 공격 대상::(" << curTarget->r << ", " << curTarget->c << ")\n";

        // 2-1. 레이저 공격
        // 최단 경로 탐색
        //isVisited[curAttacker->r][curAttacker->c] = true;
        //int tmpMinLen = searchRoute(INT_MAX, 0, curAttacker->r, curAttacker->c);
        bool hasRoute = searchRouteBfs();
        // debug
        //cout << "tmpMinLen = " << tmpMinLen << "\n";

        //if (tmpMinLen != INT_MAX) {
        if (hasRoute) {
            // 경로를 찾은 경우
            lazer();
        }
        // 2-2. 포탄 공격
        else {
            // 경로를 못찾은 경우
            bombExplose();
        }

        // 3. 포탑 부서짐
        // 공격 과정에서 처리

        // 4. 포탑 정비
        unordered_map<int, Tower*>::iterator it;
        for (it = lstWorkingTower.begin(); it != lstWorkingTower.end(); ++it) {
            if (!isRelated[(*it).second->r][(*it).second->c]) {
                ++((*it).second->power);
                map[(*it).second->r][(*it).second->c] = (*it).second->power;
            }
        }

        // 종료 조건
        if (cntWorkingTower == 1) {
            break;
        }

        // 다음 턴 준비
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                isVisited[i][j] = false;
                isRelated[i][j] = false;
                mapShortCut[i][j] = make_pair(0, 0);
            }
        }
    }
}
void printMaxPower() {
    vector<pair<int, Tower*>> vecToSort(lstWorkingTower.begin(), lstWorkingTower.end());
    sort(vecToSort.begin(), vecToSort.end(), compareTowerPowerWithVector);
    cout << vecToSort[cntWorkingTower - 1].second->power;
}

bool compareTowerPower(Tower*& t1, Tower*& t2) {  // 공격자 선정 우선 순위를 위한 정렬에 사용
    // 1. 가장 약한 포탑 -> power가 가장 작은 포탑
    bool weaker = t1->power < t2->power,
        samePower = t1->power == t2->power;

    // 2. 가장 최근에 공격한 포탑 -> usedTurn이 가장 큰 포탑
    bool lastTurnBigger = t1->usedTurn > t2->usedTurn,
        lastTurnSame = t1->usedTurn == t2->usedTurn;

    // 3. 행과 열의 합이 가장 큰 포탑 -> (r + c)가 가장 큰 포탑
    bool rlSumBigger = (t1->r + t1->c) > (t2->r + t2->c),
        rlSumSame = (t1->r + t1->c) == (t2->r + t2->c);

    // 4. 열 값이 가장 큰 포탑 -> r가 가장 큰 포탑
    bool rSize = t1->r > t2->r;

    return weaker
        || (samePower && lastTurnBigger)
        || (samePower && lastTurnSame && rlSumBigger)
        || (samePower && lastTurnSame && rlSumSame && rSize);
}
bool compareTowerPowerWithVector(pair<int, Tower*>& p1, pair<int, Tower*>& p2) {
    Tower*& t1 = p1.second;
    Tower*& t2 = p2.second;

    return compareTowerPower(t1, t2);
}

bool inRange(int r, int c) {
    return 1 <= r && r <= N && 1 <= c && c <= M;
}
int searchRoute(int minLen, int curLen, int curR, int curC) {
    if (curR == curTarget->r && curC == curTarget->c) {
        // debug
        /*cout << "(" << curR << ", " << curC << ")::curRoute.size() = " << curRoute.size() << "\n";
        cout << "curLen = " << curLen << "\n";*/
        return curLen;
    }

    //int minLen = INT_MAX;
    for (int i = 0; i < 4; ++i) {
        int nr = curR + lazerDr[i],
            nc = curC + lazerDc[i];
        if (!inRange(nr, nc)) {
            // 경계 밖인 경우
            if (nr < 1) nr = N;
            else if (nr > N) nr = 1;

            if (nc < 1) nc = M;
            else if (nc > M) nc = 1;
        }

        if (!isVisited[nr][nc] && map[nr][nc] > 0) {
            isVisited[nr][nc] = true;
            // debug
            // cout << "(" << curR << ", " << curC << ")->(" << nr << ", " << nc << ")\n";

            /*curRoute.push_back(
                make_pair(nr, nc)
            );*/
            int newLen = searchRoute(minLen, curLen + 1, nr, nc);
            //curRoute.pop_back();
            if (newLen < minLen) {

                // debug
                /*cout << "(" << curR << ", " << curC << ")::curLen = " << curLen << "\n";
                cout << "(" << curR << ", " << curC << ")::curRoute.size() = " << curRoute.size() << "\n";*/
                /*for (int j = 0; j < curRoute.size() - curLen; ++j) {
                    curRoute.pop_back();
                }*/
                mapShortCut[nr][nc] = make_pair(curR, curC);
                // cout << "mapShortCut[" << nr << "][" << nc << "] = (" << mapShortCut[nr][nc].first << ", " << mapShortCut[nr][nc].second << ")\n";

                // debug
                // cout << "(" << curR << ", " << curC << ")::minLen::" << minLen << "->" << newLen << "\n\n";

                minLen = newLen;
            }
            isVisited[nr][nc] = false;

            if (nr == curTarget->r && nc == curTarget->c) {
                break;
            }
        }
    }

    // debug
    //cout << "(" << curR << ", " << curC << ")::curRoute.size() = " << curRoute.size() << "\n";
    return minLen;
}
bool searchRouteBfs() {
    queue<Tower*> q;
    q.push(curAttacker);
    isVisited[curAttacker->r][curAttacker->c] = true;

    while (!q.empty()) {
        Tower* cur = q.front();
        q.pop();
        // debug
        // cout << "cur::(" << cur->r << ", " << cur->c << ")\n";

        for (int i = 0; i < 4; ++i) {
            int nr = cur->r + lazerDr[i],
                nc = cur->c + lazerDc[i];
            // debug
            // cout << "\t(" << cur->r << ", " << cur->c << ")->(" << nr << ", " << nc << ")\n";
            if (!inRange(nr, nc)) {
                // 경계 밖인 경우
                if (nr < 1) nr = N;
                else if (nr > N) nr = 1;

                if (nc < 1)nc = M;
                else if (nc > M)nc = 1;
            }

            if (!isVisited[nr][nc] && map[nr][nc] > 0) {
                q.push(lstWorkingTower[
                    mapTowerIdx[nr][nc]
                ]);
                isVisited[nr][nc] = true;
                mapShortCut[nr][nc] = make_pair(
                    cur->r, cur->c
                );
                // debug
                // cout << "\t\tmapShortCut[" << nr << "][" << nc << "] = (" << mapShortCut[nr][nc].first << ", " << mapShortCut[nr][nc].second << ")\n";

                if (nr == curTarget->r && nc == curTarget->c) {
                    return true;
                }
            }
        }
    }

    return false;
}

void lazer() {
    int tmpR = curTarget->r,
        tmpC = curTarget->c;
    // 공격 대상 피해
    curTarget->power -= curAttackPower;
    map[tmpR][tmpC] = curTarget->power;
    // 3. 포탑 부서짐
    if (curTarget->power <= 0) {
        lstWorkingTower.erase(
            mapTowerIdx[tmpR][tmpC]
        );
        mapTowerIdx[tmpR][tmpC] = 0;
        --cntWorkingTower;
    }

    tie(tmpR, tmpC) = mapShortCut[tmpR][tmpC];
    // 공격 경로 피해
    while (tmpR != curAttacker->r || tmpC != curAttacker->c) {
        // debug
        // cout << "Lazer Route::" << "(tmpR, tmpC) = (" << tmpR << ", " << tmpC << ")\n";
        Tower*& curAttacted = lstWorkingTower[
            mapTowerIdx[tmpR][tmpC]
        ];
        // debug
        //cout << "Lazer Route::Before::Tower" << mapTowerIdx[tmpR][tmpC] << "->(" << curAttacted->r << ", " << curAttacted->c << "), power = " << curAttacted->power << "\n";
        //cout << "Lazer Route::" << curAttacted->power << "-" << curAttackPowerHalf << " = ";
        curAttacted->power -= curAttackPowerHalf;
        map[tmpR][tmpC] = curAttacted->power;
        isRelated[curAttacted->r][curAttacted->c] = true;   // 공격과 연관됨. 포탑 정비 대상 제외

        // debug
        //cout << curAttacted->power << "\n";

        // debug
        //cout << "Lazer Route::After::Tower" << mapTowerIdx[tmpR][tmpC] << "->(" << curAttacted->r << ", " << curAttacted->c << "), power = " << curAttacted->power << "\n";
        // 3. 포탑 부서짐
        if (curAttacted->power <= 0) {
            lstWorkingTower.erase(
                mapTowerIdx[tmpR][tmpC]
            );
            mapTowerIdx[tmpR][tmpC] = 0;
            --cntWorkingTower;
        }

        tie(tmpR, tmpC) = mapShortCut[tmpR][tmpC];
    }
}

void bombExplose() {
    // 공격 대상 피해
    curTarget->power -= curAttackPower;
    map[curTarget->r][curTarget->c] = curTarget->power;
    // 3. 포탑 부서짐
    if (curTarget->power <= 0) {
        lstWorkingTower.erase(
            mapTowerIdx[curTarget->r][curTarget->c]
        );
        mapTowerIdx[curTarget->r][curTarget->c] = 0;
        --cntWorkingTower;
    }

    for (int i = 0; i < 8; ++i) {
        int nr = curTarget->r + bombDr[i],
            nc = curTarget->c + bombDc[i];
        if (!inRange(nr, nc)) {
            // 가장자리
            if (nr < 1) nr = N;
            else if (nr > N) nr = 1;

            if (nc < 1) nc = M;
            else if (nc > M) nc = 1;
        }

        if ((nr != curAttacker->r || nc != curAttacker->c)
            && map[nr][nc] > 0) {
            Tower*& curAttacted = lstWorkingTower[
                mapTowerIdx[nr][nc]
            ];
            curAttacted->power -= curAttackPowerHalf;
            map[nr][nc] = curAttacted->power;
            isRelated[curAttacted->r][curAttacted->c] = true;   // 공격과 연관됨. 포탑 정비 대상 제외

            // 3. 포탑 부서짐
            if (curAttacted->power <= 0) {
                lstWorkingTower.erase(
                    mapTowerIdx[nr][nc]
                );
                mapTowerIdx[nr][nc] = 0;
                --cntWorkingTower;
            }
        }
    }
}

/**********class 구현**********/
//class Tower {
//public:
//    int r, c,
//        power,
//        usedTurn;
//    Tower();
//};
Tower::Tower() {}