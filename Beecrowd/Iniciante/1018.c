#include <stdio.h>

int main() {
 
    int value,rest;
    scanf("%d", &value);

    printf("%d\n", value);
    printf("%d nota(s) de R$ 100,00\n", value/100);
    rest = (value%100);


    printf("%d nota(s) de R$ 50,00\n", rest/50);
    rest = (rest%50);

    printf("%d nota(s) de R$ 20,00\n", rest/20);                                                                                                                        
    rest = (rest%20);

    printf("%d nota(s) de R$ 10,00\n", rest/10);
    rest = (rest%10);

    printf("%d nota(s) de R$ 5,00\n", rest/5);
    rest = (rest%5);

    printf("%d nota(s) de R$ 2,00\n", rest/2);
    rest = (rest%2);

    printf("%d nota(s) de R$ 1,00\n", rest/1);
    
    return 0;
}