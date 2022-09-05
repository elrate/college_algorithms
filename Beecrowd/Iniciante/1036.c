#include <stdio.h>
#include <math.h> 

int main(){

    float value_1, value_2, value_3,delta,raiz_1,raiz_2;

    scanf("%f %f %f", &value_1, &value_2, &value_3);

    if(value_1 == 0){
        printf("Impossivel calcular\n");
        return 0;   
    }
    
    delta = pow(value_2,2) - (4*value_1*value_3);

    if(delta < 0){
        printf("Impossivel calcular\n");
        return 0;   
    }
    
    raiz_1 = (((-1)*value_2) + sqrt(delta))/(2*value_1);

    raiz_2 = (((-1)*value_2) - sqrt(delta))/(2*value_1);

    printf("R1 = %.5f\n", raiz_1);

    printf("R2 = %.5f\n", raiz_2);

    return 0;
}