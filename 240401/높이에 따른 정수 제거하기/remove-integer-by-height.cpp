#include <iostream>
#include <vector>

#define INF 999999999
#define MAX_N 100001

using namespace std;

int n, maxNum = 0, minNum = INF,
    ans = INF;
vector<int> arr;

int main() {
    cin>>n;
    arr.resize(n);
    for(int i = 0; i < n; ++i){
        cin>>arr[i];
        if(maxNum < arr[i]) maxNum = arr[i];
        if(minNum > arr[i]) minNum = arr[i];
    }

    for(int start = maxNum; start >= minNum; --start){
        int k = start,
            cntVisited = 0,
            tmpCnt = 0;
        bool isVisited[n];

        while(cntVisited < n){
            for(int i = 0; i < n; ++i){
                if(!isVisited[i]){
                    if(arr[i] == k){
                        isVisited[i] = true;
                        --k;
                    }
                }
                // k가 0이 된 경우
                if(k == 0){
                    
                }
            }
        }
        
        // 프로세스 끝난 후
        if(ans > tmpCnt) ans = tmpCnt;
    }

    return 0;
}