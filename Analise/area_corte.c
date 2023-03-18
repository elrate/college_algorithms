#include <stdio.h>
#include <stdlib.h>

void busca_binaria(double vetor[],double area_esp,int qtd_placas,double lim_inferior,double lim_superior,double *metade);
double soma_cima(double vetor[],double metade,int qtd_placas);

int main(){

    double *vetor;
    double metade,area_esp,maior,area_total;
    int qtd_placas;

    maior = 0;
    area_total = 0;

    scanf("%d",&qtd_placas);
    scanf("%lf",&area_esp);

    vetor = (double*)calloc(qtd_placas,sizeof(double));

    for(int i=0; i<qtd_placas; i++){
        scanf("%lf",&vetor[i]);
        area_total = area_total + vetor[i];
        if(maior < vetor[i])
            maior = vetor[i];
    }

    if(area_total == area_esp)
        printf(":D\n");
    else if(area_total < area_esp)
        printf("-.-\n");
    else{
        busca_binaria(vetor,area_esp,qtd_placas,0,maior,&metade);
        printf("%.4lf\n",metade);
        printf(":D\n");
    }

    return 0;
}

void busca_binaria(double vetor[],double area_esp,int qtd_placas,double lim_inferior,double lim_superior,double *metade){

    double area_calculada;

    while((lim_superior - lim_inferior) >= 0.00000000001){
        
        (*metade) = (lim_inferior + lim_superior)/2;

        area_calculada = soma_cima(vetor,(*metade),qtd_placas);
        if(area_calculada == area_esp)
            return;
        else{
            if(area_calculada > area_esp)
                lim_inferior = (*metade);
            else
                lim_superior = (*metade);
        }
    }
    return;
}

double soma_cima(double vetor[],double metade,int qtd_placas){

    double soma_areas= 0;

    double area_sobrou;

    for(int i=0;i<qtd_placas;i++){
        area_sobrou = vetor[i] - metade;
        if (area_sobrou < 0)
            area_sobrou = 0;

        soma_areas = soma_areas + area_sobrou;
    }

    return soma_areas;
}