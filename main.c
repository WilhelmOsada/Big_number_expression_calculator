#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "big_numbers.h"
int main()
{
    char *input1 = malloc(501 * sizeof(char));
    if(!input1)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj wyrazenie matematyczne: ");
    if(!scanf("%500[^\n]",input1))
    {
        printf("Incorrect input");
        free(input1);
        return 1;
    }
    *(input1 + strlen(input1)) = '\0';
    while(getchar()!='\n');
    char *result;
    int ret = calculate(input1,&result);
    if(ret == 2 || ret == 1)
    {
        printf("Incorrect input");
        free(input1);
        return 1;
    }
    if(ret == 3)
    {
        printf("Failed to allocate memory");
        free(input1);
        return 8;
    }
    printf("%s",result);
    free(input1);
    free(result);
    return 0;
}

