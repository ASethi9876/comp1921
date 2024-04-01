#include <stdio.h>
#include <stdlib.h>
int main(){
    int newPos[2] = {1,2};
    int current[2] = {0,0};
    current[0] = newPos[0];
    printf("%d",current[0]);
    return 0;
}