#include <stdio.h>
 
int main() {
 
    int a, b;
    float c, x;
    
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%f", &c);
    
    x = b * c;
    
    printf("NUMBER = %d\n", a);
    printf("SALARY = U$ %.2f\n", x);
 
    return 0;
}