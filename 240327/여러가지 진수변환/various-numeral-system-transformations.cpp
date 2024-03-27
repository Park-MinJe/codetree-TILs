#include <iostream>
#include <stack>

using namespace std;

int main() {
    int N, B;
    stack<int> result;
    cin>>N>>B;
    while(N>0){
        if(N < B){
            result.push(N);
            break;
        }
        result.push(N%B);
        N/=B;
    }
    while(!result.empty()){
        printf("%d", result.top());
        result.pop();
    }
    return 0;
}