#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


struct location
{
    double x, y; // <latitude, longitude>
};

struct size
{
    int m,n; // dimensions of the home/plot
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

struct plotRecord {
    char plotid[7];
    long long int price;
    struct location l;
    struct size s;
};

struct hnode 
{
    struct homeRecord data;
    int index;
    struct hnode * next;
};

struct pnode 
{
    struct plotRecord data;
    int index;
    struct pnode * next;
};

struct homeRecord HRecord[40];
int hc = 0; // Home records count

struct plotRecord PRecord[40];
int pc = 0; // plot records count

void init()
{
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\t\t\tHOME/PLOT ALLOCATION BOT\n\n");
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\n");
}

void readHomeBuyData(FILE *fp)
{
    for(hc=0; !feof(fp) && hc<40; hc++)
        fscanf(fp, "%s %lld %lf %lf %d %d %d %c %d", HRecord[hc].house_id, &HRecord[hc].price, &HRecord[hc].l.x, &HRecord[hc].l.y, &HRecord[hc].s.m, &HRecord[hc].s.n, &HRecord[hc].no_of_bedrooms, &HRecord[hc].type, &HRecord[hc].year);
}

void readplotData(FILE *fp) {
    for (pc = 0; !feof(fp) && pc < 40; pc++)
        fscanf(fp, "%s %lld %lf %lf %d %d", PRecord[pc].plotid, &PRecord[pc].price, &PRecord[pc].l.x, &PRecord[pc].l.y, &PRecord[pc].s.m, &PRecord[pc].s.n);
}

int main ()
{
    init();
    int ch, i, j, k; //ch - holds the value of choice i,j,k - loop variables 
    int a, b; // used to hold price range values
    char c; // used to hold the type
    char string[20];
    FILE * fpHome;
    while(1)
    {
        printf("About what are you looking for :\n");
        printf("1.Plot.\t\t\t2.Home.\t\t\t3.Commercial.\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                 printf("Press 'b' to buy and 'r' to rent: ");
                scanf("%*c%c", &c);
                if(tolower(c) == 'b')
                {
                    fpHome = fopen("house_dataset_sale.txt", "r+");
                    i=0;
                    c = '\0';
                    while(c == 's')
                    {
                        readHomeBuyData(fpHome);
                        while(1)
                        {
                            printHomeBuyData(i, i+5);
                            i += 5;
                            printf("[n-next, p-previous, s-filter further/stop, 1,2,3,4,5-to buy]\n");
                            printf("Enter choice: ");
                            scanf("%*c%c", &c);
                            switch(c)
                            {
                                case 'n':
                                    
                                    break;
                            }
                        }
                    }
                }
                else if(tolower(c) == 'r')
                {
                    fpHome = fopen("house_dataset_rent.txt", "r+");
                }
                else
                    printf("Invalid Choice\n");
                    
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
}
