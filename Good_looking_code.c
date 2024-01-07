#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Holds the X and Y coordinates of a location
struct location
{
    int x,y;
};

//Holds the length and breadth of plot
struct size
{
    int m,n;
};

//Holds the data of houses(House ID, Price[Rent or Sale], Location, Size, No. of Bedrooms, Type[Flat or Single],Year of Construction)
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

//Singly Linked List that maintains an index
struct node
{
    struct homeRecord data;
    int index;
    struct node *next;
};

//File pointer used to access the datasets
FILE * fp;

//String made use of in different functions
char string[20];

//Integer used as menu choice
int choice;

//Used to access 20 lines of file at a single time
struct homeRecord HRecord[20];

//Used to limit the no. of file lines read and stored
int hc = 0;

//Singly linked list maintained to filter and store data
struct node *head = NULL;

//Function:     init()
//Description:  Introduction screen
//Input Param:  NULL
//Return type:  NULL
void init()
{
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\t\t\tHOME-PLOT-ALLOCATOR\n");
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\n");
}

//Function:     menu1()
//Description:  First menu allowing choice b/w House, Plot, Commercial
//Input Param:  NULL
//Return type:  NULL
void menu1() 
{
    printf("1.House\n");
    printf("2.Plot\n");
    printf("3.Commercial\n\n");
}

//Function:     menu2()
//Description:  Second menu allowing choice b/w Buy and Rent
//Input Param:  NULL
//Return type:  NULL
void menu2()
{
    printf("1.Buy\n");
    printf("2.Rent\n");
}

//Function:     menu3()
//Description:  Third menu allowing navigation of 5 spaces or to break off and filter further
//Input Param:  NULL
//Return type:  NULL
void menu3() 
{
    printf("0.Next Five Options\n");
    printf("-1.Previous Five Options\n");
    printf("-2.Filter Further\n\n");
}

//Function:     menu4()
//Description:  Fourth menu allowing choice b/w Filtering by Price, Locality, Size 
//Input Param:  NULL
//Return type:  NULL
void menu4()
{
    printf("1.Filter based on Price\n");
    printf("2.Filter based on Locality\n");
    printf("3.Filter based on Size\n");
}

//Function:     readHomeData
//Description:  Reads the data from file into array of structures
//Input Param:  NULL
//Return type:  NULL
void readHomeData() 
{
    for(hc=0; !feof(fp) && hc<20; hc++)
        fscanf(fp, "%s %lld %d %d %d %d %d %c %d", HRecord[hc].house_id, &HRecord[hc].price, &HRecord[hc].l.x, &HRecord[hc].l.y, &HRecord[hc].s.m, &HRecord[hc].s.n, &HRecord[hc].no_of_bedrooms, &HRecord[hc].type, &HRecord[hc].year);
}

//Function:     addAtEnd()
//Description:  Adds data at the end of the linked list
//Input Param:  Head reference, data stored in a struture, index integer i
//Return type:  NULL 
void addAtEnd(struct node **head, struct homeRecord *temp, int i)
{
    struct node * p = (struct node *)malloc(sizeof(struct node));
    struct node * cur = *head;
    p->data = *temp;
    p->index = i;
    p->next = NULL;
    if(*head == NULL)
    {
        *head = p;
        return ;
    }
    while(cur->next!=NULL)
    {
        cur = cur->next;
    }
    cur->next = p;
}

//Function:     clearLinkedList()
//Description:  Deletes all nodes of linked list except head and sets head to NULL, clearing the contents
//Input Param:  Singly Linked list
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

//Function:     displayList()
//Description:  Displays the contents of Singly linked list
//Input Param:  NULL
//Return type:  NULL
void displayList()
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

//Function:     filterHomes_range()
//Description:  Filters data according to price range input by user and stores in a linked list
//Input Param:  Singly linked list, two integers input by user(minPrice and maxPrice)
//Return type:  NULL
void filterHomes_range(struct node **head, int a, int b)
{
    struct homeRecord temp;
    int i=0;
    while(!feof(fp))
    {
        fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
        if(temp.price >=a && temp.price <=b)
            addAtEnd(head, &temp, i);
        i++;
    }
}

//Function:     filterHomes_locality()
//Description:  Filters data according to locality input by user and stores in a linked list
//Input Param:  Singly linked list
//Return type:  NULL
void filterHomes_locality(struct node **head) {
    char code[4];
    struct homeRecord temp;
    int i=0;
    fseek(fp,0,0);
    while(!feof(fp)) {
        if(strcasecmp(string,"andheri") == 0) {
            while(!feof(fp)) {
                fscanf(fp,"%3s",code);
                if(strcmp(code,"AND") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
                    addAtEnd(head,&temp,i);
                    i++;
                }
            }
        }
        
        else if(strcasecmp(string,"amboli") == 0) {
            while(!feof(fp)) {
                fscanf(fp,"%3s",code);
                if(strcmp(code,"AMB") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
                    addAtEnd(head,&temp,i);
                    i++;
                }
            }
        }

        else if(strcasecmp(string,"chembur") == 0) {
            while(!feof(fp)) {
                fscanf(fp,"%3s",code);
                if(strcmp(code,"CHE") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
                    addAtEnd(head,&temp,i);
                    i++;
                }
            }
        }

        else{
            while(!feof(fp)) {
                fscanf(fp,"%3s",code);
                if(strcasecmp(code,"BOR") == 0) {
                    fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
                    addAtEnd(head,&temp,i);
                    i++;
                }
            }
        }
    }
}

//Function:     filterHomes_size()
//Description:  Filters data based on size input by user and stores it in a linked list
//Input Param:  Singly linked list and two user input integers(length and breadth)
//Return type:  NULL
void filterHomes_size(struct node **head,int a,int b) {
    struct homeRecord temp;
    int i=0;
    while(!feof(fp))
    {
        fscanf(fp, "%s %lld %d %d %d %d %d %c %d", temp.house_id, &temp.price, &temp.l.x, &temp.l.y, &temp.s.m, &temp.s.n, &temp.no_of_bedrooms, &temp.type, &temp.year);
        if(temp.s.m == a && temp.s.n == b)
            addAtEnd(head, &temp, i);
        i++;
    }
}

//Function:     house_filter()
//Description:  Menu that lets user filter based on price, locality and size 
//Input Param:  NULL
//Return type:  NULL
void house_filter()
{
    int a,b;

    menu4();
    printf("Enter your choice:");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1: printf("Enter the price range(min, max): ");
                scanf("%d %d", &a, &b);
                fseek(fp, 0, 0);
                filterHomes_range(&head,a,b);
                displayList();
                clearLinkedList(&head);
                break;
        
        case 2: printf("Enter locality:");
                scanf("%s",string);
                fseek(fp,0,0);
                filterHomes_locality(&head);
                displayList();
                clearLinkedList(&head);
                break;

        case 3: printf("Enter the length and breadth of the area in feet:");
                scanf("%d %d", &a, &b);
                fseek(fp,0,0);
                clearLinkedList(&head);
                printf("Houses with area of %dx%d feet are\n",a,b);
                printf("------------------------------------------------------------\n");
                filterHomes_size(&head,a,b);
                displayList();
                break;

        default: printf("Invalid input\n");
                 break;
    }
}

//Function:     house_info()
//Description:  Menu that lets user access and navigate the house data
//Input Param:  NULL
//Return type:  NULL
void house_info()
{
    int i,j,k;
    while(choice!=-2)
    {
        i = 1; 
        readHomeData();
        j = 0;
        k = 5;

        while(hc != 0)
        {
            for(;j<hc && j<k;j++)
                printf("%d. ID:%s | Price:%lld | Size:%dx%d |\n", i++, HRecord[j].house_id, HRecord[j].price, HRecord[j].s.m, HRecord[j].s.n);
            printf("-----------------------------------------------------\n");
            menu3();
            printf("Enter your choice:");
            scanf("%d",&choice);

            if(choice == 0)
            {
                if(j<20)
                    k += 5;
                if(j>=20)
                {
                    printf("No more data\n------------\n");
                    i -= 5;
                    j = 15;
                }
            }

            else if(choice == -1 && j == 6)
                j -= 5, i -= 5, k = 5;

            else if(choice == -1 && j>=10)
                j -= 10, k -=5, i -= 10;

            else if(choice == -1 && k == 5)
            {
                printf("Cannot move left\n----------------\n");
                j = 0; 
                i -= 5;
            }

            else if(choice == -2)
                break;
            /*else
                expand_data(choice-1);*/
            printf("-----------------------------------------------------\n");
        }
    }
}

int main()
{
    init();
    
    while(1)
    {
        menu1();
        printf("Enter your choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: menu2();
                    printf("Enter your choice:");
                    scanf("%d",&choice);

                    if(choice == 1)
                        fp = fopen("house_dataset_sale.txt", "r+");
                    else
                        fp = fopen("house_dataset_rent.txt", "r+");

                    house_info();
                    house_filter();
                    break;
        }
    }
}
