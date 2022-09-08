#include <stdio.h>

int main(){

    int valor_inicio, valor_final,horas;

    scanf("%d %d",&valor_inicio,&valor_final);

    if(valor_inicio == valor_final)
        horas = 24;
    else if(valor_inicio > valor_final)
        horas = (24 - valor_inicio) + valor_final;
    else    
        horas = valor_final - valor_inicio;

    printf("O JOGO DUROU %d HORA(S)\n",horas);
    return 0;
}