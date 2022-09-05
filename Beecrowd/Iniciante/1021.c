#include <stdio.h>
 
int main() {
    int value_nota,rest,value_moeda;
    double value;
    scanf("%lf", &value);

    value_moeda = (value*100);
    value_moeda = value_moeda%100;
    value_nota = value;

    printf("NOTAS:\n");
    printf("%d nota(s) de R$ 100.00\n", value_nota/100);
    rest = (value_nota%100);

    printf("%d nota(s) de R$ 50.00\n", rest/50);
    rest = (rest%50);

    printf("%d nota(s) de R$ 20.00\n", rest/20);            
    rest = (rest%20);

    printf("%d nota(s) de R$ 10.00\n", rest/10);
    rest = (rest%10);

    printf("%d nota(s) de R$ 5.00\n", rest/5);
    rest = (rest%5);

    printf("%d nota(s) de R$ 2.00\n", rest/2);
    rest = (rest%2);

    printf("MOEDAS:\n");
    printf("%d moeda(s) de R$ 1.00\n", rest/1);

    printf("%d moeda(s) de R$ 0.50\n", value_moeda/50);
    rest = (value_moeda%50);

    printf("%d moeda(s) de R$ 0.25\n", rest/25);
    rest = (rest%25);

    printf("%d moeda(s) de R$ 0.10\n", rest/10);
    rest = (rest%10);

    printf("%d moeda(s) de R$ 0.05\n", rest/5);
    rest = (rest%5);

    printf("%d moeda(s) de R$ 0.01\n", rest/1);
    rest = (rest%1);
    
    return 0;
}