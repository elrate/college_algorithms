#include <stdio.h>
 
int main() {
 
    double a, b, m;
    
    scanf("%lf", &a);
    scanf("%lf", &b);
    
    m = ((a * 3.5) + (b * 7.5))/11;

    printf("MEDIA = %.5lf\n", m);
    
    return 0;
}