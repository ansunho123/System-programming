#include <stdio.h>
#include <malloc.h>

int main()
{
    int *p = malloc(32);
    printf("% p\n", p);
    free(p);
    return 0;
}