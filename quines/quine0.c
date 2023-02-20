#include <stdio.h> 
char x[]="#include <stdio.h>char x[]=%c%s%c;%cint main() {printf(x,34,x,34,10,10);return 0;}%c";
int main() {printf(x,34,x,34,10,10);return 0;}
