#include <iostream>
#include <string>
#include <stack>

using namespace std;

int binary[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

int convert2Decimal(string b){
    int rt = 0,
        bLen = b.length();
    for(int i = 0; i < bLen; ++i){
        rt += (b[i]-'0') * binary[bLen-i-1];
    }
    return rt;
}

void convert2Binary(int n){
    stack<int> rt;

    while(n > 0){
        if(n < 2){
            rt.push(n);
            break;
        }

        rt.push(n%2);
        n/=2;
    }

    while(!rt.empty()){
        printf("%d", rt.top());
        rt.pop();
    }
}

int main() {
    string nAsBinary;
    cin>>nAsBinary;
    int n = convert2Decimal(nAsBinary) * 17;

    convert2Binary(n);

    return 0;
}