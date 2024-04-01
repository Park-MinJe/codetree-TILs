// #include <iostream>
// #include <unordered_map>
// #include <vector>

// using namespace std;

// int n, k;
// long long cnt;
// unordered_map<long long, vector<int>> map;
// unordered_map<long long, bool> mapIsUsed;

// int main() {
//     cin>>n>>k;
//     for(int i = 0; i < n; ++i){
//         long long tmp;
//         cin>>tmp;
//         map[tmp].push_back(i);
//         mapIsUsed[tmp] = false;
//     }
    
//     unordered_map<long long, vector<int>>::iterator it;
//     for(it = map.begin(); it != map.end(); ++it){
//         if(!mapIsUsed[it->first]){
//             mapIsUsed[it->first] = true;
//             int minus = k - it->first;
//             if(minus != it->first){
//                 if(!mapIsUsed[minus]){
//                     mapIsUsed[minus] = true;
//                     cnt += it->second.size() * map[minus].size();
//                 }
//                 //cout<<minus<<" "<<cnt<<"\n";
//             }
//             else{
//                 int tmpSize = (it->second).size();
//                 cnt += tmpSize * (tmpSize-1) / 2;
//             }
            
//         }
//     }

//     cout<<cnt;
    
//     return 0;
// }

#include <iostream>
#include <unordered_map>

using namespace std;

#define MAX_N 100000

// 변수 선언
int n, k;
int arr[MAX_N];
unordered_map<long long, int> count;

int main() {
    // 입력:
    cin >> n >> k;
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int ans = 0;

    // 배열을 앞에서부터 순회하며 쌍을 만들어줍니다.
    for(int i = 0; i < n; i++) {
        long long diff = (long long)k - arr[i];
        // 가능한 모든 쌍의 수를 세어줍니다.
        ans += count[diff];

        // 현재 숫자의 개수를 하나 증가시켜줍니다.
        count[arr[i]]++;
    }

    cout << ans;
    return 0;
}