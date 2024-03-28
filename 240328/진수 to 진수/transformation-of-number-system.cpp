#include <iostream>
#include <string>
#include <stack>

using namespace std;

int a, b;
string n;
int lstPow[9][9];

int pow(int base, int exp){
    if(lstPow[base][exp] != 0){
        return lstPow[base][exp];
    }
    if(exp == 0){
        return 1;
    }

    int rt = base * pow(base, exp-1);
    lstPow[base][exp] = rt;
    return rt;
}

int convA2Dec(string nBya){
    int rt = 0,
        nLen = nBya.length();
    for(int i = nLen-1; i >= 0; --i){
        rt += (nBya[i]-'0') * pow(a, nLen-i-1);
    }
    return rt;
}

void convDec2B(int nBydec){
    stack<int> rt;
    while(nBydec > 0){
        if(nBydec < b){
            rt.push(nBydec);
            break;
        }
        rt.push(nBydec%b);
        nBydec/=b;
    }
    while(!rt.empty()){
        printf("%d", rt.top());
        rt.pop();
    }
}

int main() {
    scanf("%d %d", &a, &b);
    cin>>n;
    
    convDec2B(convA2Dec(n));

    return 0;
}