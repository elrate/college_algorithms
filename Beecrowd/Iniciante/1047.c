#include <stdio.h>
int main()
{
    int h_inicio, h_final, m_inicio, m_final;
    int diferenca;

    scanf("%d %d %d %d", &h_inicio, &m_inicio, &h_final, &m_final);

    diferenca = ((h_final*60)+m_final) - ((h_inicio*60)+m_inicio);

    if(diferenca<=0) 
        diferenca += 24*60;

    printf("O JOGO DUROU %d HORA(S) E %d MINUTO(S)\n", diferenca/60, diferenca%60);
    return 0;
}