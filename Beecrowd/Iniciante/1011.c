#include <stdio.h>
 
int main() {
 
    double a, b;
    
    scanf("%lf", &a);
    
    b = (4 * 3.14159 * (a * a * a))/3.0;
   
    printf("VOLUME = %.3lf\n", b);
 
    return 0;
}  