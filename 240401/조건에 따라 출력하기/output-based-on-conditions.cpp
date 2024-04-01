#include <iostream>
#include <queue>

#define MAX_N 51

using namespace std;

int n,
    arr[MAX_N];
bool isStoped = false;
queue<int> ans;

int main() {
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>arr[i];

        if(arr[i] == 0){
            isStoped = true;
        }
        if(!isStoped){
            if(arr[i] % 3 == 0){
                ans.push(arr[i]/3);
            }
            else{
                ans.push(arr[i] + 2);
            }
        }
    }
    while(!ans.empty()){
        cout<<ans.front()<<"\n";
        ans.pop();
    }
    return 0;
}