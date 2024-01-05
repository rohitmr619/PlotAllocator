#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct location
{
    int x, y;
};

struct size
{
    int m,n;
};

struct homeRecord
{
    char house_id[7];
    long long int price;
    struct location l;
    struct size s;
    int no_of_bedrooms;
    char type;
    int year;
};

struct homeRecord HRecord[20];
int hc = 0;

void init()
{
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\t\t\tHOME/PLOT ALLOCATION BOT\n\n");
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\n");
}

void readHomeData(FILE *fp)
{
    for(hc=0; !feof(fp) && hc<20; hc++)
        fscanf(fp, "%s %lld %d %d %d %d %d %c %d", HRecord[hc].house_id, &HRecord[hc].price, &HRecord[hc].l.x, &HRecord[hc].l.y, &HRecord[hc].s.m, &HRecord[hc].s.n, &HRecord[hc].no_of_bedrooms, &HRecord[hc].type, &HRecord[hc].year);
}

void buyHome(int i)
{
    // right now this function is incomplete
    int index = (i-1)%20;
    char c;
    printf("Do you want to buy home %s (y/n): ", HRecord[index].house_id);
    scanf("%*c%c", &c);
}

int main()
{
    init();
    int ch, i, j, k;
    char c;
    FILE * fpHome;
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
                printf("Press 'b' to buy and 'r' to rent: ");
                scanf("%*c%c", &c);
                if(tolower(c) == 'b')
                {
                    fpHome = fopen("house_dataset_sale.txt", "r+");
                    while(ch !=-2)
                    {
                        i=1;
                        readHomeData(fpHome);
                        j=0, k = 5;
                        while(hc != 0)
                        {
                            for(;j<hc && j<k;j++)
                                printf("%d. %s with price %d of size %dx%d\n", i++, HRecord[j].house_id, HRecord[j].price, HRecord[j].s.m, HRecord[j].s.n);
                            printf("Enter choice (0 - to next -1 - to prev and -2 - to stop): ");
                            scanf("%d", &ch);
                            if(ch == 0)
                                k += 5;
                            else if(ch == -1 && j == 6)
                                j -= 5, i -= 5, k = 5;
                            else if(ch == -1 && j>10)
                                j -= 10, k -=5, i -= 10;
                            else if(ch == -2)
                                break;
                            else if(ch > k-5 && ch <= k)
                            {
                                buyHome(ch);
                                ch = -2;
                                break;
                            }
                        }
                    }
                    printf("Search home using [1.Price range.   2.location.   3.size.]\n");
                    printf("Enter choice: ");


                    fclose(fpHome);
                }
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
