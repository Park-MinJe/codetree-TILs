#include <iostream>

#define MAX_NM 100001

using namespace std;

int n, m, mid,
    result[MAX_NM];
long long arr[MAX_NM],
    trgtArr[MAX_NM];

void init(){
    cin>>n>>m;
    mid = n/2;
    for(int i = 1; i <= n; ++i){
        cin>>arr[i];
    }
    for(int i = 1; i <= m; ++i){
        cin>>trgtArr[i];
        result[i] = -1;
    }
}

void solve(){
    for(int i = 1; i <= m; ++i){
        int left = 1, right = n;
        while(left <= right){
            mid = (left+right) / 2;
            if(arr[mid] == trgtArr[i]){
                result[i] = mid;
            }

            if(arr[mid] > trgtArr[i]){
                right = mid-1;
            }
            else{
                left = mid+1;
            }
        }
    }
}

void printResult(){
    for(int i = 1; i <= m; ++i){
        cout<<result[i]<<"\n";
    }
}

int main() {
    init();
    solve();
    printResult();
    return 0;
}