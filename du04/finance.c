#include  <stdio.h>
#include <stdlib.h>
#define MAX_INPUT 25000


int main(void) {
    int balance[MAX_INPUT];
    int x=0, i = 0;
    while ( i< MAX_INPUT) {

        x=scanf("%d", &balance[i]);
        if(x==EOF){
            break;
        }
        else if(x!=1){
            printf("Nespravny vstup.\n");
            return 0;
        }
        ++i;

    }

    printf("%d",balance[0]);
    return 0;


}