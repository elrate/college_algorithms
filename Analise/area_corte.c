#include <stdio.h>
#include <stdlib.h>

void busca_binaria(double vetor[],double area,double inicio,int qtd_placas,double maior,double *metade);
double soma_cima(double meio,double vetor[],int qtd_placas);

int main(){

    double *vetor;
    double metade;
    int qtd_placas;
    double verificador;
    double area,maior,area_total;
    maior = 0;
    area_total = 0;

    scanf("%d",&qtd_placas);
    scanf("%lf",&area);

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

    if(area_total == area){
        printf(":D\n");
    }else if(area_total < area){
        printf("-.-\n");
    }else{
        busca_binaria(vetor,area,0,qtd_placas,maior,&metade);
        printf("%.4lf\n",metade);
        printf(":D\n");
    }

    return 0;
}

void busca_binaria(double vetor[],double area,double inicio, int qtd_placas,double maior,double *metade){

    double area_calculada;

    while(inicio - maior >= 0.00000001){
        
        (*metade) = (inicio + maior)/2;
        printf("metade = %lf\n",(*metade));

        area_calculada = soma_cima((*metade),vetor,qtd_placas);
        if(area_calculada == area){
            return;
        }else{
            if(area_calculada < area){
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