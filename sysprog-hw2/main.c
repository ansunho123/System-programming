#include<stdio.h>
#include<printf.h>

int main(){
int i = 1000;
char c = 'a';
char *s = "test";
int x1 = 7293;
int x2 = -412;


printf("Inter i = %d\n\n", i);
printf("Character c = %c\n\n", c);
printf("String s = %s\n\n" , s);
printf("hex x1 = %x, x2 = %x\n\n", x1,x2);
printf("Multiple arguments : i = %d, c = %c, s = %s, x1 = %x, x2 = %x\n", i ,c, s, x1, x2);

return 0;

}
