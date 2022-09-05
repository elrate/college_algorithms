#include <stdio.h>
 
int main() {
    
    int x;
    float y, media;
    
    scanf("%d", &x);
    scanf("%f", &y);
    
    media = x/y;
    
    printf("%.3f km/l\n", media);
    
    return 0;
}