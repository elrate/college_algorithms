#include <stdio.h>
#include <stdlib.h>

void mostrar_matriz(int ** mat, int l , int c);

int main()
{

    int **mat;
    int qtd_vertices,qtd_arestas,par_1, par_2;

    printf("\nDigite a qtd de vertices: ");
    scanf("%d",&qtd_vertices);
    printf("\nDigite a quantidade de arestas: ");
    scanf("%d",&qtd_arestas);

    mat = (int**)calloc(qtd_vertices+1,sizeof(int*));

    for(int i=0;i<qtd_vertices+1;i++)
        mat[i] = (int*)calloc(qtd_vertices+1,sizeof(int));

    for(int i = 0; i < qtd_arestas;i++){
        scanf("%d %d",&par_1,&par_2);
        mat[par_1][par_1] = 1;
        mat[par_1][par_2] = 1;
        mat[par_2][par_2] = 1;
        mat[par_2][par_1] = 1;
    }

    mostrar_matriz(mat,qtd_vertices,qtd_vertices);
    return 0;
}


void mostrar_matriz(int **mat, int l , int c)
{
    int i,j;

    for(i=1;i<=l;i++)
    {
        
        for(j=1;j<=c;j++)
        {
            printf("\t%d",mat[i][j]);
        }
        printf("\n");
    }
}