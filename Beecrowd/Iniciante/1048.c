#include <stdio.h>

int main(){

    float salario,percent;
    char caractere = '%';

    scanf("%f",&salario);

    if(salario >= 0 && salario <= 400)
        percent = 15.0/100;
    else if(salario > 400 && salario <= 800)
        percent = 12.0/100;
    else if(salario > 800 && salario <= 1200)
        percent = 10.0/100;
    else if(salario > 1200 && salario <= 2000)
        percent = 7.0/100;
    else
        percent = 4.0/100;

    printf("Novo salario: %.2f\n",(salario + (salario*percent)));
    printf("Reajuste ganho: %.2f\n",(salario*percent));
    printf("Em percentual: %.0f %c\n",(percent*100),caractere);

    return 0;
}