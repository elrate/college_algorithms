#include <stdio.h>
 
int main() {
 
    int a, b;
    float media;
    
    scanf("%d", &a);
    scanf("%d", &b);
    
    media = (a * b)/12.0;
    
    printf("%.3f\n", media);
    
    return 0;
}
