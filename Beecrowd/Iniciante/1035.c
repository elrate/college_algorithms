#include <stdio.h>
#include <stdlib.h>

int main(){

    int A,B,C,D;

    scanf("%d %d %d %d",&A,&B,&C,&D);

    if(B > C){
        if(D > A){
            if((C+D) > (A+B)){
                if((C != (C*(-1))) && (D != (D*(-1)))){ 
                    if(A%2 == 0){
                        printf("Valores aceitos\n");
                        return 0;
                    }
                }
            }
        }
    }

    printf("Valores nao aceitos\n");

    return 0;
}