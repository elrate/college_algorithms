#include <stdio.h>
 
int main() {
 
   	int a, h, m, s;
   	
   	scanf("%d", &a);
   	
   	h = (a/60)/60;
   	a = a - ((h * 60) * 60);
   	m = a/60;
   	a = a - (m * 60);
   	s = a;
   	
    printf("%d:%d:%d\n", h,m,s);
 
    return 0;
}