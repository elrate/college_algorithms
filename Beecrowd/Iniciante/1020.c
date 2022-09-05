#include <stdio.h>
 
int main() {
 
    int a, ano, meses, dias;
    
    scanf("%d", &a);
    
    ano = a/365;
    a = a - (ano * 365);
    meses = a/30;
    a = a - (meses * 30);
    dias = a;
    
    printf("%d ano(s)\n", ano);
    printf("%d mes(es)\n", meses);
    printf("%d dia(s)\n", dias);
 
    return 0;
}