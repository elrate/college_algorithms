//Atividade de Sistemas Operacionais
//Gabriel Vieira Cavalcante - 2012082044
//Caio Falleiro dos Santos - 2012082018

#include <stdio.h>
#include <stdlib.h>

typedef struct operacoes{
    int registrador_base;
    int registrador_limite;
}operacoes;

int preencher_vet(int vet[],operacoes op[],int count);
int receber_verificar_processo(int *processo);
void mostrar_lista(int vet[],int final);
void mostrar_mapa_bits(int vet[],int final);
void mostrar_grid(int vet[],operacoes op[],int count);
void mostrar_traco(int qtd);

int main(){

    int base,limite,count,processo,verificador;
    operacoes op[5];
    int *vet;

    vet = (int*)calloc(40, sizeof(int));

    count = 0;

    verificador = receber_verificar_processo(&processo);

    while(processo && count < 5){
        verificador = 1;
        printf("\nDigite o endereco base do processo: ");
        scanf("%d",&base);
        printf("\nDigite a quantidade de posicoes que o processo ira ocupar(Limite): ");
        scanf("%d",&limite);
    
        op[count].registrador_base = base;
        op[count].registrador_limite = limite;
        count++;
        
        if(count < 5){
            verificador = receber_verificar_processo(&processo);
        } 
    }

    verificador = preencher_vet(vet,op,count);

    if(verificador){
        mostrar_lista(vet,base);
        mostrar_mapa_bits(vet,base);
        mostrar_grid(vet,op,count);
    }
    return 0;
}


int preencher_vet(int vet[],operacoes op[],int count){
    int limite,base;
    
    for(int i = 0; i < count; i++){
        limite = op[i].registrador_limite;
        base = op[i].registrador_base;
        for(int j = 0; j < limite; j++){
            if(base == 40){
                printf("\nErro!\nTamanho da memoria excedido!");
                return 0;
            }
            if(vet[base] == 0){
                vet[base] = 1;
            }else{
                printf("\nErro!\nAcesso Indevido!");
                return 0;
            }
            base++;
        }
    }
    return 1;
}

int receber_verificar_processo(int *processo){
    int verificador = 1;
    while(verificador){
        printf("\nDeseja inserir um processo? [1/0] ");
        scanf("%d",processo); 
        if((*processo) == 0 || (*processo) == 1){
            verificador = 0;
        }
    }
    return verificador;
}

void mostrar_lista(int vet[],int final){

    printf("\nLista encadeada:\n");
    mostrar_traco(83);
    printf("\n");
    printf("| ");
    for(int i=0;i<40;i++){
        printf("%d ",vet[i]);
    }
    printf("|\n");
    mostrar_traco(83);
}

void mostrar_mapa_bits(int vet[],int final){
    printf("\nMapa de Bits:\n");
    mostrar_traco(19);
    printf("\n| ");
    for(int i=0;i<40;i++){
        if(i == 8 || i == 16 || i == 24 || i == 32)
            printf("|\n| ");
        printf("%d ",vet[i]);
    }
    printf("|\n");
    mostrar_traco(19);
    printf("\n");
}

void mostrar_grid(int vet[],operacoes op[],int count){
    int aux;
    printf("Grid:\n");
    mostrar_traco(19);
    for(int i=0;i<40;i++){
        if(vet[i] == 1){
            for(int j=0;j<count;j++){
                if(op[j].registrador_base == i){
                    //printf("\n|  P  |  %d  |  %d  |",op[j].registrador_base,op[j].registrador_limite);
                    printf("\n|  P  |  ");
                    if(op[j].registrador_base < 10)
                        printf("%d  |",op[j].registrador_base);
                    else
                        printf("%d |",op[j].registrador_base);

                    if(op[j].registrador_limite < 10)
                        printf("  %d  |",op[j].registrador_limite);
                    else
                        printf("  %d |",op[j].registrador_limite);
                }
            }
        }else{
            aux = i;
            while(vet[i] == 0){
                i++;
            }
            //printf("\n|  L  |  %d  |  %d  |",aux,(i - aux));
            printf("\n|  L  |  ");
            if(aux < 10)
                printf("%d  |",aux);
            else
                printf("%d |",aux);

            if((i-aux) < 10)
                printf("  %d  |",(i-aux));
            else
                printf("  %d |",(i-aux));
            i--;
        }
    }
    printf("\n");
    mostrar_traco(19);
    printf("\n");
}

void mostrar_traco(int qtd){
    for(int i=0; i<qtd;i++){
        printf("-");
    }
}