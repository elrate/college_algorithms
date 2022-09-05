#include <stdio.h>
 
int main() {
 
   char nome[10000];
   double a, b, c;
   
   scanf("%s", nome);
   scanf("%lf", &a);
   scanf("%lf", &b);
   
   c = a + (b * 0.15);
   printf("TOTAL = R$ %.2lf\n", c);
 
    return 0;
}