#include <iostream>
#include <unordered_set>

#define MAX_NM 100001

using namespace std;

int n, m;
long long
    arr[MAX_NM],
    trgts[MAX_NM];
unordered_set<long long> nums;

void init(){
    cin>>n>>m;
    for(int i = 0; i < n; ++i){
        cin>>arr[i];
        nums.insert(arr[i]);
    }
    for(int i = 0; i < m; ++i){
        cin>>trgts[i];
    }
}

int getLowerBound(long long trgt){
    int left = 0, right = n-1,
        min_idx = n;
    while(left <= right){
        int mid = (left + right) / 2;
        if(arr[mid] >= trgt){
            right = mid - 1;
            min_idx = min(min_idx, mid);
        }
        else{
            left = mid+1;
        }
    }
    return min_idx;
}

void solve(){
    for(int i = 0; i < m; ++i){
        if(nums.find(trgts[i]) == nums.end()){
            cout<<"-1\n";
            break;
        }
        cout << getLowerBound(trgts[i]) + 1 << "\n";
    }
}

int main() {
    init();
    solve();
    return 0;
}