// #include <iostream>

// using namespace std;

// int n, m,
//     curR, curC,
//     dir = 2;    // 0-N, 1-E, 2-S, 3-W
// int** board;

// int mvR[4] = {-1, 0, 1, 0}, mvC[4] = {0, 1, 0, -1},
//     mvRLast[4] = {0, -1, 0, 1}, mvCLast[4] = {-1, 0, 1, 0};

// bool inRange(int nr, int nc){
//     return nr >= 0 && nr < n && nc >= 0 && nc < m;
// }

// int main() {
//     scanf("%d %d", &n, &m);
//     int rSize = n,
//         cSize = m;

//     board = new int*[n];
//     for(int i = 0; i<n; ++i){
//         board[i] = new int[n];
//         for(int j = 0; j<m; ++j){
//             board[i][j] = -1;
//         }
//     }

//     curR = 0;
//     curC = 0;
//     board[curR][curC] = 1;
//     for(int i = 2; i <= n*m; ++i){
//         while(true){
//             int nr = curR + mvR[dir];
//             int nc = curC + mvC[dir];
//             //printf("%d %d\n", nr, nc);

//             if(inRange(nr, nc) && board[nr][nc] == -1){
//                 curR = nr;
//                 curC = nc;
//                 board[curR][curC] = i;
//                 break;
//             }
//             else{
//                 dir = (dir+3)%4;
//             }
//         }
//     }

//     for(int i = 0; i < rSize; ++i){
//         for(int j = 0; j < cSize; ++j){
//             printf("%d ", board[i][j]);
//         }
//         printf("\n");
//     }

//     delete[] board;

//     return 0;
// }

#include <iostream>

#define MAX_N 100
#define DIR_NUM 4

using namespace std;

int n, m;
int arr[MAX_N][MAX_N];

int dx[DIR_NUM] = {0, 1,  0, -1};
int dy[DIR_NUM] = {1, 0, -1,  0};

int curr_x, curr_y;  // 시작은 (0, 0) 입니다.
int dir = 1;             // 0: 오른쪽, 1: 아래쪽, 2: 왼쪽, 3: 위쪽

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

int main() {
    // 입력:
    cin >> n >> m;

    // 처음 시작 위치에 초기값을 적습니다.
    arr[curr_x][curr_y] = 1;

    // n*m개의 숫자를 적어야 합니다. 
    for(int i = 2; i <= n * m; i++) { // 숫자 i를 어디에 적을지 결정합니다.
        while(true) { // 나아갈 수 있을때까지 방향을 바꿔가며 확인해봅니다. 
            // 현재 방향 dir를 기준으로 그 다음 위치 값을 계산합니다.
            int nx = curr_x + dx[dir];
            int ny = curr_y + dy[dir];
            
			// 그 위치로 나아갈 수 있는지 확인합니다.
            if(InRange(nx, ny) && arr[nx][ny] == 0) {
                // 나아갈 수 있다면 위치를 갱신해주고 배열에 올바른 값을 채워넣습니다.
                curr_x = nx; 
                curr_y = ny;
                arr[curr_x][curr_y] = i;
                break;
            } else {
                // 나아갈 수 없다면 반시계방향으로 90'를 회전하여 
				// 그 다음 방향을 확인해봐야 합니다.
                dir = (dir + 3) % 4;
            }
        }
    }
    
    // 출력:
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) 
            cout << arr[i][j] << " ";
        cout << endl;
    }
    return 0;
}