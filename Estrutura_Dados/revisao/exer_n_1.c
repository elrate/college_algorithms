#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sanduiche{
    char nome_sanduiche[50];
    float preco;
    float peso;
    int avaliacao;
}sanduiche;

void preenche_registro(sanduiche registro[], int qtd);
void sanduiche_a(sanduiche registro[], int qtd);
void mostrar_sanduiches(sanduiche registro[], int lista_a[], int contador);
void melhor_avaliado(sanduiche registro[], int qtd);
void mostrar_melhor_avaliados(sanduiche registro[], int cont, int maior, int lista_avaliacao[]);
void peso_medio(sanduiche registro[], int qtd);
void tres_de_cada_um(sanduiche registro[], int qtd);

int main(){

    sanduiche *registro_sanduiche;
    int qtd_sanduiche = 0;

    while(qtd_sanduiche <= 0){
        printf("\nDigite a quantidade de sanduiches que deseja alocar: ");
        scanf("%d", &qtd_sanduiche);

        if(qtd_sanduiche <= 0){
            printf("\nNumero invalido!\n");
        }
    }

    registro_sanduiche = (sanduiche*)malloc(sizeof(sanduiche) * qtd_sanduiche);

    preenche_registro(registro_sanduiche, qtd_sanduiche);

    sanduiche_a(registro_sanduiche, qtd_sanduiche);
    
    melhor_avaliado(registro_sanduiche, qtd_sanduiche);

    peso_medio(registro_sanduiche, qtd_sanduiche);

    tres_de_cada_um(registro_sanduiche, qtd_sanduiche);

    printf("\n");

    return 0;
}

void preenche_registro(sanduiche registro[], int qtd){

    for(int i = 0; i < qtd; i++){
        printf("\nDigite o nome do Sanduiche %d: ", i + 1);
        fflush(stdin);
        fgets(registro[i].nome_sanduiche, 50, stdin);
        registro[i].nome_sanduiche[strlen(registro[i].nome_sanduiche) - 1] = '\0';
        printf("\nDigite o preco do sanduiche %d: ", i + 1);
        scanf("%f", &registro[i].preco);
        printf("\nDigite o peso do sanduiche %d: ", i + 1);
        scanf("%f", &registro[i].peso);
        printf("\nDigite a avaliacao do sanduiche %d: ", i + 1);
        scanf("%d", &registro[i].avaliacao);
    }
}

void sanduiche_a(sanduiche registro[], int qtd){

    int *lista_a;
    int contador = 0;

    lista_a = (int*)malloc(sizeof(int) * qtd);

    for(int i = 0; i < qtd; i++){
        if(registro[i].nome_sanduiche[0] == 'A'){
            lista_a[contador] = i;
            contador++;
        }else if(registro[i].nome_sanduiche[0] == 'a'){
            lista_a[contador] = i;
            contador++;
        }
    }

    if(contador > 0){
        mostrar_sanduiches(registro, lista_a, contador);
    }else{
        printf("\n--------------------------------\n");
        printf("O registro nao possui nenhum sanduiche com a letra inicial igual 'A'!");
        printf("\n--------------------------------\n");
    }
}

void mostrar_sanduiches(sanduiche registro[], int lista_a[], int contador){
    
    printf("\n--------------------------------\n");
    printf("Sanduiches com letra inical 'a':");

    for(int i = 0; i < contador; i++){
        printf("\n%s", registro[lista_a[i]].nome_sanduiche);
    }
    printf("\n--------------------------------\n");
}

void melhor_avaliado(sanduiche registro[], int qtd){

    int maior = 0, cont = 0;
    int *lista_avaliacao;

    lista_avaliacao = (int*)malloc(sizeof(int) * qtd);

    for(int i = 0; i < qtd; i++){
        if(registro[i].avaliacao > maior){
            maior = registro[i].avaliacao;
        }
    }

    for(int i = 0; i < qtd; i++){
        if(registro[i].avaliacao == maior){
            lista_avaliacao[cont] = i;
            cont++;
        }
    }
    
    mostrar_melhor_avaliados(registro, cont , maior, lista_avaliacao);
}

void mostrar_melhor_avaliados(sanduiche registro[], int cont, int maior, int lista_avaliacao[]){

    if(cont == 1){
        printf("O sanduiche melhor avaliado e o: %s, com uma nota igual a: %d.", registro[lista_avaliacao[0]].nome_sanduiche, maior);
        printf("\n--------------------------------\n");
    }else{
        printf("Os sanduiches melhores avaliados sao:\n");
        printf("|");
        for(int i = 0; i < cont; i++){
            printf("%s |", registro[lista_avaliacao[i]].nome_sanduiche);
        }
        printf("\nCom nota igual a: %d\n", maior);
        printf("--------------------------------\n");
    }
}

void peso_medio(sanduiche registro[], int qtd){

    float peso_medio = 0.0;

    for(int i = 0; i < qtd; i++){
        peso_medio = registro[i].peso + peso_medio;
    }

    peso_medio = peso_medio/qtd;

    printf("O peso medio dos sanduiches e: %f", peso_medio);
    printf("\n--------------------------------\n");
}

void tres_de_cada_um(sanduiche registro[], int qtd){

    float total = 0.0;

    for(int i = 0; i < qtd; i++){
        total = (registro[i].preco * 3) + total;
    }

    printf("Em caso de compra de 3 de cada um dos sanduiches, o valor total sera: R$ %f reais!", total);
    printf("\n--------------------------------\n");
}