#include <stdio.h>

int main(){

    float nota_1, nota_2, nota_3, nota_4,media,nova_nota;
    
    scanf("%f %f %f %f", &nota_1, &nota_2, &nota_3, &nota_4);

    media = (((nota_1*2)+(nota_2*3)+(nota_3*4)+(nota_4))/10);

    if(media >= 7){
        printf("Media: %.1f\n",media);
        printf("Aluno aprovado.\n");
        return 0;
    }else if(media < 5){
        printf("Media: %.1f\n",media);
        printf("Aluno reprovado.\n");
        return 0;
    }

    printf("Media: %.1f\n",media);
    printf("Aluno em exame.\n");

    scanf("%f",&nova_nota);

    printf("Nota do exame: %.1f\n",nova_nota);

    if(((media+nova_nota)/2) >= 5){
        printf("Aluno aprovado.\n");
    }else{
        printf("Aluno reprovado.\n");
    }

    printf("Media final: %.1f\n",(media+nova_nota)/2);
    return 0;
}