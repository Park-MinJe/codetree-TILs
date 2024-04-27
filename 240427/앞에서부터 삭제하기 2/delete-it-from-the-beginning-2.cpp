#include <iostream>
#include <queue>

#define MAX_N 100000

using namespace std;

class cmp{
public:
    bool operator() (int a, int b){
        return a > b;
    }
};

int N,
    arr[MAX_N];
double answer = -1.0;

void init(){
    cin>>N;
    for(int i = 0; i < N; ++i){
        cin>>arr[i];
    }
}

void solve(){
    for(int K = 1; K <= N-2; ++K){
        priority_queue<int, vector<int>, cmp> pq(arr+K, arr+N);
        // debug
        // while(!pq.empty()){
        //     cout<<pq.top()<<" ";
        //     pq.pop();
        // }
        // cout<<"\n";

        pq.pop();

        double tmpAvg = 0;
        double tmpSize = (double)pq.size();
        while(!pq.empty()){
            tmpAvg += pq.top();
            pq.pop();
        }
        tmpAvg /= tmpSize;

        answer = max(answer, tmpAvg);
    }
}

int main() {
    init();
    solve();
    
    cout << fixed;
    cout.precision(2);
    cout<<answer;
    return 0;
}