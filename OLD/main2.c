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

struct node 
{
    struct homeRecord data;
    int index;
    struct node *next;
};

void init()
{
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\t\t\tHOME/PLOT ALLOCATION BOT\n\n");
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\n");
}

//Function:     readHomeData
//Description:  reads the data from file into array of structures
//Input Param:  file pointer
//Return type:  NULL
void readHomeData(FILE *fp)
{
    for(hc=0; !feof(fp) && hc<30; hc++)
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

//Function:     addAtBeg
//Description:  adds contents into nodes of linked list at the beginning
//Input Param:  head reference, struct homeRecord, integer
//Return type:  NULL
void addAtBeg(struct node **head, struct homeRecord *temp, int i)
{
    struct node * p = (struct node *)malloc(sizeof(struct node));
    p->data = *temp;
    p->index = i;
    p->next = NULL;
    if(head == NULL)
    {
        *head = p;
        return ;
    }
    p->next = *head;
    *head = p;
}

//Function:     searchHomesInRange
//Description:  searches homes in range of given price values
//Input Param:  file pointer, head reference, integer, integer
//Return type:  NULL
void searchHomesInRange(FILE * fp, struct node **head, int a, int b)
{
    struct homeRecord temp;
    int i=0;
    while(!feof(fp))
    {
        fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
        if(temp.price >=a && temp.price <=b)
            addAtBeg(head, &temp, i);
        i++;
    }
}

//Function:     displayList
//Description:  displays the contents of linked list
//Input Param:  head
//Return type:  NULL
void displayList(struct node *head)
{
    struct node *p = head;
    int i=1;
    
    if(head == NULL) {
        printf("----------------No matching results----------------\n");
        return;
    }

    while(p)
    {   
        if(p->data.type == 'F') {
            printf("%d. House ID:%s | Price:%lld | Size:%dx%d | No.of.Bedrooms:%d | Type:Flat | Year of Construction:%d |\n",i,p->data.house_id, p->data.price, p->data.s.m, p->data.s.n, p->data.no_of_bedrooms, p->data.year);
            p = p->next;
            i++;
        }
        else {
            printf("%d. House ID:%s | Price:%lld | Size:%dx%d | No.of.Bedrooms:%d | Type:Single | Year of Construction:%d |\n",i,p->data.house_id, p->data.price, p->data.s.m, p->data.s.n, p->data.no_of_bedrooms, p->data.year);
            p = p->next;
            i++;
        }

    }
}

//Function:     to_lower_string
//Description:  converts every character of input string to lowercase
//Input param:  string
//Return type:  char * 
char * to_lower_string(char * string)
{
    int i = 0;
    while(string[i])
    {
        string[i] = tolower(string[i]);
        i++;
    }
    return string;
}


//Function:     clearLinkedList
//Description:  clears the common linked list and sets head to NULL
//Input Param:  head
//Return type:  NULL
void clearLinkedList(struct node** head) {
    struct node* cur = *head;
    struct node* nextNode;

    while (cur != NULL) {
        nextNode = cur->next;
        free(cur);
        cur = nextNode;
    }

    // Update the head pointer to NULL
    *head = NULL;
}

//Function:     extract_location
//Description:  extracts locality of house by considering first 3 characters from house_id string
//Input Param:  file pointer, head reference, string
//Return type:  NULL
void extract_location(FILE * fp, struct node **head, char * string) {
    char code[4];
    struct homeRecord temp;
    int i=0;
    fseek(fp,0,0);
    strcpy(string,to_lower_string(string));
    while(!feof(fp)) {
        if(strcmp(string,"andheri") == 0) {
            while(!feof(fp)) {
                fscanf(fp,"%3s",code);
                if(strcmp(code,"AND") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
                    addAtBeg(head,&temp,i);
                    i++;
                }
            }
        }
        
        else if(strcmp(string,"amboli") == 0) {
            while(!feof(fp)) {
                fscanf(fp,"%3s",code);
                if(strcmp(code,"AMB") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
                    addAtBeg(head,&temp,i);
                    i++;
                }
            }
        }

        else if(strcmp(string,"chembur") == 0) {
            while(!feof(fp)) {
                fscanf(fp,"%3s",code);
                if(strcmp(code,"CHE") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
                    addAtBeg(head,&temp,i);
                    i++;
                }
            }
        }

        else{
            while(!feof(fp)) {
                fscanf(fp,"%3s",code);
                if(strcmp(code,"BOR") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
                    addAtBeg(head,&temp,i);
                    i++;
                }
            }
        }
    }
}

//Function:     searchHomesInSize
//Description:  searches homes with respect to their size in feet
//Input Param:  file pointer, head reference, integer, integer
//Return type:  NULL
void searchHomesInSize(FILE * fp,struct node **head,int a,int b) {
    struct homeRecord temp;
    int i=0;
    while(!feof(fp))
    {
        fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
        if(temp.s.m == a && temp.s.n == b)
            addAtBeg(head, &temp, i);
        i++;
    }
}

int main()
{
    init();
    int ch, i, j, k;
    int a, b;
    char c;
    char string[20];
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
                    fpHome = fopen("house_dataset_sale.txt", "r+");
                else
                    fpHome = fopen("house_dataset_rent.txt", "r+");
                while(ch !=-2)
                    {
                        i=1;
                        readHomeData(fpHome);
                        j=0, k = 5;
                        while(hc != 0)
                        {
                            for(;j<hc && j<k;j++)
                                printf("%d. ID:%s | Price:%lld | Size:%dx%d |\n", i++, HRecord[j].house_id, HRecord[j].price, HRecord[j].s.m, HRecord[j].s.n);
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
                                buyHome(ch);
                                ch = -2;
                                break;
                            }
                            printf("-----------------------------------------------------\n");
                            printf("-----------------------------------------------------\n");
                        }
                    }
                    struct node *head = NULL;
                    printf("Search home using [1.Price range.   2.location.   3.size.]\n");
                    printf("Enter choice: ");
                    scanf("%d", &ch);
                    switch (ch)
                    {
                    case 1:
                        printf("Enter the price range(min, max): ");
                        scanf("%d %d", &a, &b);
                        fseek(fpHome, 0, 0);
                        searchHomesInRange(fpHome, &head, a, b);
                        displayList(head);
                        break;
                    case 2:
                        printf("Enter locality:");
                        scanf("%s",string);
                        fseek(fpHome, 0, 0);
                        clearLinkedList(&head);
                        printf("Houses currently available for sale in %s are\n",string);
                        printf("------------------------------------------------------------\n");
                        extract_location(fpHome, &head, string);
                        displayList(head);
                        break;

                    default:
                        printf("Enter the length and breadth of the area in feet:");
                        scanf("%d %d", &a, &b);
                        fseek(fpHome,0,0);
                        clearLinkedList(&head);
                        printf("Houses with area of %dx%d feet are\n",a,b);
                        printf("------------------------------------------------------------\n");
                        searchHomesInSize(fpHome,&head,a,b);
                        displayList(head);
                        break;
                    }
                    fclose(fpHome);
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
