#include <stdio.h>
#include <stdlib.h>

void busca_binaria(double vetor[],double area_esp,double inicio,int qtd_placas,double maior,double *metade);
double soma_cima(double meio,double vetor[],int qtd_placas);

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
    }

    for(int i = 0; i < qtd_placas;i++){
        area_total = area_total + vetor[i];

        if(maior < vetor[i]){
            maior = vetor[i];
        }
    }

    if(area_total == area_esp){
        printf(":D\n");
    }else if(area_total < area_esp){
        printf("-.-\n");
    }else{
        busca_binaria(vetor,area_esp,0,qtd_placas,maior,&metade);
        printf("%.4lf\n",metade);
        printf(":D\n");
    }

    return 0;
}

void busca_binaria(double vetor[],double area_esp,double inicio, int qtd_placas,double maior,double *metade){

    double area_calculada;

    while((maior - inicio) >= 0.00000000001){
        
        (*metade) = (inicio + maior)/2;

        area_calculada = soma_cima((*metade),vetor,qtd_placas);
        if(area_calculada == area_esp){
            return;
        }else{
            if(area_calculada > area_esp){
                inicio = (*metade);
            }else{
                maior = (*metade);
            }
        }
    }
    return;
}

double soma_cima(double metade,double vetor[],int qtd_placas){

    double soma_areas= 0;

    double area_sobrou;

    for(int i=0;i<qtd_placas;i++)
    {
        area_sobrou = vetor[i] - metade;
        if (area_sobrou < 0)
            area_sobrou =0;

        soma_areas = soma_areas + area_sobrou;
    }

    return soma_areas;
}