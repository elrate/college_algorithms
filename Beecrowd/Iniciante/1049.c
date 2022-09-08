#include <stdio.h>
#include <string.h>

int main(){
    char tipo_1[20];
    char tipo_2[20];
    char tipo_3[20];

    fgets(tipo_1,20,stdin);
    fflush(stdin);
    tipo_1[strlen(tipo_1)-1] = '\0';

    fgets(tipo_2,20,stdin);
    fflush(stdin);
    tipo_2[strlen(tipo_2)-1] = '\0';

    fgets(tipo_3,20,stdin);
    tipo_3[strlen(tipo_3)-1] = '\0';
    
    if(strcmp(tipo_1,"vertebrado") == 0){
        if(strcmp(tipo_2,"ave") == 0){

            if(strcmp(tipo_3,"carnivoro") == 0)
                printf("aguia\n");
            else if(strcmp(tipo_3,"onivoro") == 0)
                printf("pomba\n");

        }else if(strcmp(tipo_2,"mamifero") == 0){
            if(strcmp(tipo_3,"herbivoro") == 0)
                printf("vaca\n");
            else if(strcmp(tipo_3,"onivoro") == 0)
                printf("homem\n");
            
        }
    }else if(strcmp(tipo_1,"invertebrado") == 0){
        if(strcmp(tipo_2,"inseto") == 0){

            if(strcmp(tipo_3,"herbivoro") == 0)
                printf("lagarta\n");
            else if(strcmp(tipo_3,"hematofago") == 0)
                printf("pulga\n");
            
        }else if(strcmp(tipo_2,"anelideo") == 0){
            
            if(strcmp(tipo_3,"onivoro") == 0)
                printf("minhoca\n");
            else if(strcmp(tipo_3,"hematofago") == 0)
                printf("sanguessuga\n");
            
        }
    }
    return 0;
}