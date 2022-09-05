#include <stdio.h>

int main()
{
    int a, b, c, d;
    float x, y, z;
    
    scanf("%d %d %f", &a, &b, &x);
    scanf("%d %d %f", &c, &d, &y);
    
    z = (b * x) + (d * y);
    
    printf("VALOR A PAGAR: R$ %.2f\n", z);
    
    return 0;
}