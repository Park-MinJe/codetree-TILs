#include <iostream>
#include <stack>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    stack<int> result;
    while(n > 0){
        if(n < 2){
            result.push(n);
            n /= 2;
            break;
        }
        result.push(n%2);
        n/=2;
    }
    while(!result.empty()){
        printf("%d", result.top());
        result.pop();
    }
    return 0;
}