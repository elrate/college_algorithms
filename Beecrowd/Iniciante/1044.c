#include <stdio.h>

int main(){

    int value_1, value_2;

    scanf("%d %d",&value_1,&value_2);

    if(value_2%value_1 == 0 || value_1%value_2 == 0)
        printf("Sao Multiplos\n");
    else
        printf("Nao sao Multiplos\n");

    return 0;
}