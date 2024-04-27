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
    arr[MAX_N],
    sum[MAX_N];
double answer = -1.0;

void init(){
    cin>>N;
    for(int i = 0; i < N; ++i){
        cin>>arr[i];

        for(int j = 0; j <= i; ++j){
            sum[j] += arr[i];
        }
    }

    // debug
    // for(int i = 1; i <= N-2; ++i){
    //     cout<<i<<"::"<<sum[i]<<"\n";
    // }
}

void solve(){
    priority_queue<int, vector<int>, cmp> pq(arr+N-1, arr+N);
    for(int K = N-2; K >= 1; --K){
        pq.push(arr[K]);

        // debug
        // cout<<K<<"::"<<pq.top()<<"\n";
        // cout<<(sum[K] - pq.top())<<"\n";
        // cout<<N-K<<"\n";

        double tmpAvg = (sum[K] - pq.top()) / (double)(N - K - 1);

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