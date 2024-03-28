#include <iostream>

using namespace std;

int n;

void init(){
    scanf("%d", &n);
}

void printStarUpper(int curN){
    if(curN == 0){
        return;
    }

    printStarUpper(curN - 1);
    for(int i = 0; i < curN; ++i){
        printf("*");
    }
    printf("\n");
}
void printStarLower(int curN){
    if(curN == 0){
        return;
    }

    for(int i = 0; i < curN; ++i){
        printf("*");
    }
    printf("\n");
    printStarLower(curN - 1);
}
void printStar(int N){
    printStarUpper(N);
    printStarLower(N-1);
}

int main() {
    init();
    printStar(n);
    return 0;
}