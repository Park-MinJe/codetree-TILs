// #include <iostream>

// using namespace std;

// int n, k,
//     curY, curX,
//     dir;    // 0-N, 1-E, 2-S, 3-W
// char** map;

// int main() {
//     // 격자 크기
//     scanf("%d", &n);
//     // 맵의 정보
//     map = new char*[n+1];
//     for(int i = 1; i<=n; ++i){
//         map[i] = new char[n+1];
//     }
//     for(int i = 1; i<n+1;++i){
//         for(int j = 1;j<n+1;++j){
//             scanf(" %c",&map[i][j]);
//         }
//     }
//     // 쏘는 위치 K
//     scanf("%d", &k);
//     if(k >= 1 && k <= n){
//         curY = 1;
//         curX = k;
//         dir = 2;
//     }
//     else if(k>=(n+1) &&k<=(n*2)){
//         curX = n;
//         curY = k-n;
//         dir = 3;
//     }
//     else if(k>=(n*2+1) && k<=(n*3)){
//         curY = n;
//         curX = (3*n+1)-k;
//         dir = 0;
//     }
//     else if(k>=(n*3+1) && k<=(n*4)){
//         curX = 1;
//         curY = (4*n+1)-k;
//         dir = 1;
//     }

//     int cnt = 0;
//     while(curX >= 1 && curX <= n && curY >= 1 && curY <= n){
//         switch(dir){
//         case 0: 
//             if(map[curY][curX] == '/'){
//                 ++curX;
//                 dir = (dir+1)%4;
//             }
//             else if(map[curY][curX] == '\\'){
//                 --curX;
//                 dir = (dir+3)%4;
//             }
//             break;
//         case 1:
//             if(map[curY][curX] == '/'){
//                 --curY;
//                 dir = (dir+3)%4;
//             }
//             else if(map[curY][curX] == '\\'){
//                 ++curY;
//                 dir = (dir+1)%4;
//             }
//             break;
//         case 2:
//             if(map[curY][curX] == '/'){
//                 --curX;
//                 dir = (dir+1)%4;
//             }
//             else if(map[curY][curX] == '\\'){
//                 ++curX;
//                 dir = (dir+3)%4;
//             }
//             break;
//         case 3:
//             if(map[curY][curX] == '/'){
//                 ++curY;
//                 dir = (dir+3)%4;
//             }
//             else if(map[curY][curX] == '\\'){
//                 --curY;
//                 dir = (dir+1)%4;
//             }
//             break;
//         }
//         ++cnt;
//     }

//     printf("%d", cnt);

//     return 0;
// }

#include <iostream>

#define MAX_N 1000
#define DIR_NUM 4

using namespace std;

int n;
char arr[MAX_N][MAX_N];

int start_num;
int x, y, move_dir;

// 주어진 숫자에 따라
// 시작 위치와 방향을 구합니다.
void Initialize(int num) {
    if(num <= n) {
        x = 0; y = num - 1; move_dir = 0;
    }
    else if(num <= 2 * n) {
        x = num - n - 1; y = n - 1; move_dir = 1;
    }
    else if(num <= 3 * n) {
        x = n - 1; y = n - (num - 2 * n); move_dir = 2;
    }
    else {
        x = n - (num - 3 * n); y = 0; move_dir = 3;
    }
}

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

// (x, y)에서 시작하여 next_dir 방향으로
// 이동한 이후의 위치를 구합니다.
void Move(int next_dir) {
    int dx[DIR_NUM] = {1,  0, -1, 0};
    int dy[DIR_NUM] = {0, -1,  0, 1};
    
    x += dx[next_dir];
    y += dy[next_dir];
    move_dir = next_dir;
}

int Simulate() {
    int move_num = 0;
    while(InRange(x, y)) {
        // 0 <-> 1 / 2 <-> 3
        if(arr[x][y] == '/')
            Move(move_dir ^ 1);
        // 0 <-> 3 / 1 <-> 2
        else
            Move(3 - move_dir);
        
        move_num += 1;
    }
    
    return move_num;
}

int main() {
    // 입력
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> arr[i][j];
    
    cin >> start_num;
 
    // 시작 위치와 방향을 구합니다.
    Initialize(start_num);
    // (x, y)에서 move_dir 방향으로 시작하여
    // 시뮬레이션을 진행합니다.
    int move_num = Simulate();
    
    cout << move_num;
    return 0;
}