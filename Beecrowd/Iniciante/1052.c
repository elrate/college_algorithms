#include <stdio.h>

int main(){

    char mes_string[12][20] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    int valor;

    scanf("%d",&valor);

    printf("%s\n",mes_string[valor-1]);
    return 0;
}