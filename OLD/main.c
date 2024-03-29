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
        printf("1.Plot.\t\t\t2.Home.\t\t\t3.Commercial.\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            //print all ready-to-move-in plots(print 3 only, functional navigation buttons required)
            //print all investment type plots(print 3 only, sort by rate of average growth)

            //take choice input 
            //case 1 : ready to move in
                //take inputs - locality,budget(min-max input),size
                //print output for all the matching parameters(navigation button)(single source shortest path)
                //take input for prime facility
                //print output according to prime facility(closest,navigation button)(sorting)
                //recommendation system
            //case 2 : investment
                //take inputs - locality,budget(min-max input),size
                //print output for all the matching parameters(navigation button)(sorted by average increase)
                //recommendation system
            break;
        case 2:
            //take input on rent or buy(case 1 or 2)
            //1.print all buy-able houses(print 3 only, functional navigation buttons required)
            //2.print all rent-able houses(print 3 only, functional navigation buttons required)

            //take input on single or flat(case 1 or 2)
            //1.print all single-standing type houses(print 3 only, functional navigation buttons required)
            //2.print all flat houses(print 3 only, functional navigation buttons required)

            //case 1 : single standing
                //take inputs - locality,budget(min-max input),no_of_bedrooms,size
                //print output for all the matching parameters(navigation button)(single source shortest path)
                //take input for prime facility
                //print output according to prime facility(closest,navigation button)(sorting)
                //recommendation system

            //case 2 : flat
                //take inputs - locality,budget(min-max input),no_of_bedrooms,size
                //print output for all the matching parameters(navigation button)(single source shortest path)
                //take input for prime facility
                //print output according to prime facility(closest,navigation button)(sorting)
                //recommendation system
            break;
        case 3:
            //print all buy-able buildings(print 3 only, functional navigation buttons required)
            //print all lease-able buildings(print 3 only, functional navigation buttons required)
            //print all both-able buildings(print 3 only, functional navigation buttons required)
            //take input on lease or buy(chooses from lease and both, or buy and both)
            break;
        default:
            printf("The program has been terminated.\n \t\t\tThanking you.");
            exit(0);
            break;
        }
        printf("\n");
    }
}
