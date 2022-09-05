#include <stdio.h>

int main(){

    int opcao,qtd;
    float preco[5] = {4.0f,4.5f,5.0f,2.0f,1.5f};

    scanf("%d %d",&opcao,&qtd);

    switch(opcao){
        case 1:
            printf("Total: R$ %.2f\n", qtd*preco[0]);
            break;
        case 2:
            printf("Total: R$ %.2f\n", qtd*preco[1]);
            break;
        case 3:
            printf("Total: R$ %.2f\n", qtd*preco[2]);
            break;
        case 4:
            printf("Total: R$ %.2f\n", qtd*preco[3]);
            break;
        case 5:
            printf("Total: R$ %.2f\n", qtd*preco[4]);
            break;
    }
    return 0;
}