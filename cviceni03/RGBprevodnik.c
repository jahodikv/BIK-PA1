#include <stdio.h>

int checkInterval(int x){

if (x>255)
    return 1;
else if(x<0)
    return 1;
else
    return 0;
}

int main (void){

int x, y, z, q;

printf("Zadejte barvu v RGB formatu:\n");
q=scanf(" rgb ( %d , %d , %d )", &x, &y, &z);
if (getchar()==EOF){
 printf("Nespravny vstup.\n");
    return 0;

}
if(q!=3){

    printf("Nespravny vstup.\n");
    return 0;
}
else{

if (checkInterval(x)==1){
    printf("Nespravny vstup.\n");return 0;}
if (checkInterval(y)==1){
    printf("Nespravny vstup.\n");return 0;}
if (checkInterval(z)==1){
    printf("Nespravny vstup.\n");return 0;}
 
if(x<16 && y<16 && z<16){
    printf("#0%X0%X0%X\n",x,y,z);}
else if(y<16 && x<16){
    printf("#0%X0%X%X\n",x,y,z);}
else if(z<16 && y<16){
    printf("#%X0%X0%X\n",x,y,z);}
else if(x<16 && z<16){
    printf("#0%X%X0%X\n",x,y,z);}
else if(x<16){
    printf("#0%X%X%X\n",x,y,z);}
else if(y<16){
    printf("#%X0%X%X\n",x,y,z);}
else if(z<16){
    printf("#%X%X0%X\n",x,y,z);}
else{
printf("#%X%X%X\n",x,y,z);
return 0;

}


}
}