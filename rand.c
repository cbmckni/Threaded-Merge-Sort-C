#include <stdio.h>
#include <stdlib.h>

int     main(void)
{
    FILE    *fptr;
    int     i;
    int     num;
    char    num2;
    i = 0;

    fptr = fopen("input.txt", "w");
    if (fptr == NULL)
    {
        printf("ERROR Creating File!");
        exit(1);
    }
    for(i = 0;i < 100000;i++)
    {
        num = rand() % 100000;
        num2 = num + '0';
	fprintf(fptr,"%i ", num2);
    }
    
    fclose(fptr);
    return 0;
}
