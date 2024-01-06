#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char * to_lower_string(char  *string);
struct location {
    int p, q;
};

struct size {
    int e, f;
};

struct plotrecord {
    char plotid[10];
    long long int price;
    struct location l;
    struct size s;
    char type;
};

struct node {
    struct plotrecord data;
    int index;
    struct node *next;
};

struct plotrecord PRecord[20];
int pc = 0;

typedef struct node *Plot;

void init() {
    for (int i = 0; i < 80; i++)
        printf("*");
    printf("\n\t\t\tHOME/PLOT ALLOCATION BOT\n\n");
    for (int i = 0; i < 80; i++)
        printf("*");
    printf("\n\n");
}

void readplotData(FILE *fp) {
    for (pc = 0; !feof(fp) && pc < 30; pc++)
        fscanf(fp, "%s %lld %d %d %d %d %c ", PRecord[pc].plotid, &PRecord[pc].price, &PRecord[pc].l.p, &PRecord[pc].l.q, &PRecord[pc].s.e, &PRecord[pc].s.f, &PRecord[pc].type);
}

void buyplot(int i) {
    int index = (i - 1) % 20;
    char c;
    printf("Do you want to buy plot %s (y/n): ", PRecord[index].plotid);
    scanf(" %c", &c);
}

//Function:     addAtBeg
//Description:  adds contents into nodes of linked list at the beginning
//Input Param:  head reference, struct homeRecord, integer
//Return type:  NULL
void addAtBeg(struct node **head, struct plotrecord *temp, int i) {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = *temp;
    p->index = i;
    p->next = NULL;
    if (*head == NULL) {
        *head = p;
        return;
    }
    p->next = *head;
    *head = p;
}

//Function:     searchplotssInRange
//Description:  searches plotss in range of given price values
//Input Param:  file pointer, head reference, integer, integer
//Return type:  NULL
void searchplotsInRange(FILE *fp, struct node **head, int a, int b) {
    struct plotrecord temp;
    int i = 0;
    while (!feof(fp)) {
        fscanf(fp, "%s %lld %d %d %d %d %c", temp.plotid, &temp.price, &temp.l.p, &temp.l.q, &temp.s.e, &temp.s.f, &temp.type);
        if (temp.price >= a && temp.price <= b)
            addAtBeg(head, &temp, i);
        i++;
    }
}

//Function:     displayList
//Description:  displays the contents of linked list
//Input Param:  head
//Return type:  NULL
void displayplotList(struct node *head) {
    struct node *p = head;
    int i = 1;

    if (head == NULL) {
        printf("----------------No matching results----------------\n");
        return;
    }

    while (p) {
        printf("%d. Plot ID:%s | Price:%lld | Size:%dx%d | Type:%c |\n", i, p->data.plotid, p->data.price, p->data.s.e, p->data.s.f, p->data.type);
        p = p->next;
        i++;
    }
}


//Function:     clearLinkedList
//Description:  clears the common linked list and sets head to NULL
//Input Param:  head
//Return type:  NULL
void clearplotLinkedList(struct node **head) {
    struct node *cur = *head;
    struct node *nextNode;

    while (cur != NULL) {
        nextNode = cur->next;
        free(cur);
        cur = nextNode;
    }

    *head = NULL;
}

//Function:     extract_location
//Description:  extracts locality of plot by considering first 3 characters from plotid string
//Input Param:  file pointer, head reference, string
//Return type:  NULL
void extract_plotlocation(FILE *fp, struct node **head, char *string) {
    char code[4];
    struct plotrecord temp;
    int i = 0;
    fseek(fp, 0, SEEK_SET);
    strcpy(string, to_lower_string(string));
    while (!feof(fp)) {
        if (strcmp(string, "andheri") == 0) {
            while (!feof(fp)) {
                fscanf(fp, "%3s", code);
                if (strcmp(code, "AND") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %c", temp.plotid, &temp.price, &temp.l.p, &temp.l.q, &temp.s.e, &temp.s.f, &temp.type);
                    addAtBeg(head, &temp, i);
                    i++;
                }
            }
        } else if (strcmp(string, "amboli") == 0) {
            while (!feof(fp)) {
                fscanf(fp, "%3s", code);
                if (strcmp(code, "AMB") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %c", temp.plotid, &temp.price, &temp.l.p, &temp.l.q, &temp.s.e, &temp.s.f, &temp.type);
                    addAtBeg(head, &temp, i);
                    i++;
                }
            }
        } else if (strcmp(string, "chembur") == 0) {
            while (!feof(fp)) {
                fscanf(fp, "%3s", code);
                if (strcmp(code, "CHE") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %c", temp.plotid, &temp.price, &temp.l.p, &temp.l.q, &temp.s.e, &temp.s.f, &temp.type);
                    addAtBeg(head, &temp, i);
                    i++;
                }
            }
        } else {
            while (!feof(fp)) {
                fscanf(fp, "%3s", code);
                if (strcmp(code, "BOR") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %c", temp.plotid, &temp.price, &temp.l.p, &temp.l.q, &temp.s.e, &temp.s.f, &temp.type);
                    addAtBeg(head, &temp, i);
                    i++;
                }
            }
        }
    }
}

//Function:     searchplotsInSize
//Description:  searches plots with respect to their size in feet
//Input Param:  file pointer, head reference, integer, integer
//Return type:  NULL
void searchplotsInSize(FILE *fp, struct node **head, int a, int b) {
    struct plotrecord temp;
    int i = 0;
    while (!feof(fp)) {
        fscanf(fp, "%s %lld %d %d %d %d %c", temp.plotid, &temp.price, &temp.l.p, &temp.l.q, &temp.s.e, &temp.s.f, &temp.type);
        if (temp.s.e == a && temp.s.f == b) {
            addAtBeg(head, &temp, i);
            i++;
        }
    }
}

//Function:     to_lower_string
//Description:  converts every character of input string to lowercase
//Input param:  string
//Return type:  char *
char * to_lower_string(char  *string)
{
    int i = 0;
   while(string[i])
    {
        string[i] = tolower(string[i]);
        i++;
    }
    return string;
}

int main() {
    init();
    int ch, i;
    int a, b;
    char c, d;
    char string[20];
    FILE *fpHome;

    while (1) {
        printf("About what are you looking for :\n");
        printf("1.Plot.\t\t\t2.Home.\t\t\t3.Commercial.\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
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


                printf("press b to buy and l to lease a plot\n");
                scanf("%c ",&d);
                if(tolower(d) == 'b')
                    fpHome = fopen("plot_purchase_dataset.txt", 'r');
                else
                    fpHome = fopen("plot_lease_dataset.txt", "r+");
                    while(ch !=-2)
                    {
                        i=1;
                        readplotData(fpHome);
                        int j=0, k = 5;
                        while(pc != 0)
                        {
                            for(;j<pc && j<k;j++)
                                printf("%d. ID:%s | Price:%lld | Type:%c | size:%dx%d |\n", i++, PRecord[j].plotid, PRecord[j].price, PRecord[j].type, PRecord[j].s.e,PRecord[j].s.f);
                            printf("Enter choice (0 - Next Five\t-1 - Previous Five\t-2 - Filter Further): ");
                            scanf("%d", &ch);
                            if(ch == 0)
                                k += 5;
                            else if(ch == -1 && j == 6)
                                j -= 5, i -= 5, k = 5;
                            else if(ch == -1 && j>=10)
                                j -= 10, k -=5, i -= 10;
                            else if(ch == -2)
                                break;
                            else if(ch > k-5 && ch <= k)
                            {
                                buyplot(ch);
                                ch = -2;
                                break;
                            }
                            printf("-----------------------------------------------------\n");
                            printf("-----------------------------------------------------\n");
                        }
                    }
                    struct node *head = NULL;
                    printf("Search plot using \n1.Price range. \n  2.location. \n  3.size.]\n");
                    printf("Enter choice: ");
                    scanf("%d", &ch);
                    switch (ch)
                    {
                    case 1:
                        printf("Enter the price range(min, max): ");
                        scanf("%d %d", &a, &b);
                        fseek(fpHome, 0, 0);
                        searchplotsInRange(fpHome, &head, a, b);
                        displayplotList(head);
                        break;
                    case 2:
                        printf("Enter locality:");
                        scanf("%s",string);
                        fseek(fpHome, 0, 0);
                        clearplotLinkedList(&head);
                        printf("Houses currently available for sale in %s are\n",string);
                        printf("------------------------------------------------------------\n");
                        extract_plotlocation(fpHome, &head, string);
                        displayplotList(head);
                        break;

                    default:
                        printf("Enter the length and breadth of the area in feet:");
                        scanf("%d %d", &a, &b);
                        fseek(fpHome,0,0);
                        clearplotLinkedList(&head);
                        printf("Houses with area of %dx%d feet are\n",a,b);
                        printf("------------------------------------------------------------\n");
                        searchplotsInSize(fpHome,&head,a,b);
                        displayplotList(head);
                        break;
                    }
                    fclose(fpHome);
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
