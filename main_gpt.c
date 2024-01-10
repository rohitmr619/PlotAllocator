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

void readHomeData(FILE *fp)
{
    for(hc=0; !feof(fp) && hc<40; hc++)
        fscanf(fp, "%s %lld %lf %lf %d %d %d %c %d", HRecord[hc].house_id, &HRecord[hc].price, &HRecord[hc].l.x, &HRecord[hc].l.y, &HRecord[hc].s.m, &HRecord[hc].s.n, &HRecord[hc].no_of_bedrooms, &HRecord[hc].type, &HRecord[hc].year);
}

void readplotData(FILE *fp) {
    for (pc = 0; !feof(fp) && pc < 40; pc++)
        fscanf(fp, "%s %lld %lf %lf %d %d", PRecord[pc].plotid, &PRecord[pc].price, &PRecord[pc].l.x, &PRecord[pc].l.y, &PRecord[pc].s.m, &PRecord[pc].s.n);
}

void printHomeData(int start, int end)
{
    int a=1;
    for(int i=start; i<end && i<hc; i++)
    {
        printf("%d. %s\t%lld\t%lf\t%lf\t%d\t%d\t%d\t%c\t%d\n", a++, HRecord[i].house_id, HRecord[i].price, HRecord[i].l.x, HRecord[i].l.y, HRecord[i].s.m, HRecord[i].s.n, HRecord[i].no_of_bedrooms, HRecord[i].type, HRecord[i].year);
    }
}

void expand_data(int index)
{
    printf("House ID: %s\n", HRecord[index].house_id);
    printf("Price: %lld\n", HRecord[index].price);
    printf("Location: %lf, %lf\n", HRecord[index].l.x, HRecord[index].l.y);
    printf("Size: %d, %d\n", HRecord[index].s.m, HRecord[index].s.n);
    printf("No of bedrooms: %d\n", HRecord[index].no_of_bedrooms);
    printf("Type: %c\n", HRecord[index].type);
    printf("Year: %d\n", HRecord[index].year);
}

int main ()
{
    init();
    int ch, i, j, k; //ch - holds the value i,j,k - loop variables 
    int a, b; // used to hold price range values
    char c; // used to hold the type
    char string[20];
    FILE * fpHome;
    while(1)
    {
        printf("About what are you looking for :\n");
        printf("1.Home.\t\t\t2.Plot.\t\t\t3.Commercial.\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                 printf("Press 'b' to buy and 'r' to rent: ");
                scanf("%*c%c", &c);
                    if(tolower(c) == 'b')
                        fpHome = fopen("house_dataset_sale.txt", "r+");
                    else if(tolower(c) == 'r')
                        fpHome = fopen("house_dataset_rent.txt", "r+");

                    c = '\0';
                    while(c != 's')
                    {
                        readHomeData(fpHome);
                        i=0;
                        while(c != 's')
                        {
                            printHomeData(i, i+5);
                            i += 5;
                            printf("[n-next, p-previous, s-filter further/stop, 1,2,3,4,5-to buy]\n");
                            printf("Enter choice: ");
                            scanf("%*c%c", &c);
                            if(i>=40)
                                break;
                            switch(c)
                            {
                                case 'n':
                                    i += 5;
                                    break;
                                case 'p':
                                    if(i == 5)
                                    {
                                        i = 0;
                                        break;
                                    }
                                    else
                                        i -= 10;
                                    break;
                                case 's':
                                    break;
                                case '1' ... '5':
                                    expand_data(c-49);
                                    break;
                            }
                        }
                    }
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                printf("Inva\n");
                break;
        }
    }
}
