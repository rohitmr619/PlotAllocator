#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init()
{
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\t\t\tHOME/PLOT ALLOCATION BOT\n\n");
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\n");
}

int main()
{
    init();
    int ch, i;
    while(1)
    {
        printf("About what are you looking for :\n");
        printf("1.Home.\t\t\t2.Plot.\t\t\t3.Commercial.\n");
        printf("Enter choice:");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("1.Find home.\t\t2.Check availability of home at a particular location.\t\t3.List ");
            
            break;
        case 2:

            break;
        case 3:

            break;
        default:
            printf("The program has been terminated.\n \t\t\tThanking you.");
            exit(0);
            break;
        }
        printf("\n");
    }
}
