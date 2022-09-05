#include <stdio.h>
 
int main() {
 
    int a, b, c, maior = 0;
    
    scanf("%d %d %d", &a, &b, &c);
    
    if(a > maior){
        maior = a;
    }
    if(b > maior){
        maior = b;
    }
    if(c > maior){
        maior = c;
    }
    
    printf("%d eh o maior\n", maior);
    
    return 0;
}