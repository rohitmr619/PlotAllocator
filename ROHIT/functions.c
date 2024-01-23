#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locals.h"


/*
Function Name: mainMenu
Input Params:  NULL
Return Type:   NULL
Description:   Displays the welcome message and prompts the user to enter the username
*/
void mainMenu() {
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\t\t\tHOME PURCHASE BOT\n\n");
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\n");
}

/*
Function Name: filePointerinit
Input Params:  NULL
Return Type:   FILE *
Description:   Opens the username_password.txt file

*/
FILE* filePointerinit(FILE *fp){
    fp=fopen("username_password.txt","r");
    fp1=fopen("house_dataset_sale.txt","r");
    if (fp == NULL || fp1 == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return fp;
}

/*
Function Name: password_hasher
Input Params:  password(char *) - Password entered by the user
Return Type:   NULL
Description:   Hashes the password entered by the user
*/
void password_hasher(char *password) {
    int i;
    for (i = 0; password[i] != '\0'; i++) {
        password[i] = (password[i] + 3);
    }
}

/*
Function Name: brute_force_compare
Input Params:  str1(char *) - String 1
               str2(char *) - String 2
Return Type:   int
Description:   Compares two strings using the brute force method
*/
int brute_force_compare(char *str1, char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return 0; // Strings are not equal
        }
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0'); // Both strings are equal if both are null-terminated
}

/*
Function Name: password_compare
Input Params:  user_password(char *) - Hashed password stored in the users array
               password(char *) - Hashed password entered by the user
Return Type:   NULL
Description:   Compares the hashed password entered by the user with the hashed password stored in the users array
*/
void password_compare(char *user_password, char *password) {
    password_hasher(password);
    if (brute_force_compare(user_password, password)) {
        printf("\nPassword accepted!\n");
    } else {
        printf("\nPassword incorrect!\n");
        exit(0);
    }
}

/*
Function Name: readDataFromFile
Input Params:  users(struct user_credentials []) - Array of type user_credentials
               size(int) - Size of the users array
               fp(FILE *) - File pointer to open the username_password.txt file
Return Type:   NULL
Description:   Reads data from username_password.txt and stores it in users array.
*/
void readDataFromFile(struct user_credentials users[], int size,FILE *fp) {
    int counter=0;
    int budget=0;
   for(counter=0; !feof(fp) && counter<size; counter++){
        fscanf(fp, "%s %s %s %d %d %d", users[counter].username, users[counter].hashed_pass, users[counter].user_locality, &users[counter].user_budget, &users[counter].user_size.m, &users[counter].user_size.n);
   }
   for(counter=0;!feof(fp);counter++)
   {
        fscanf(fp1,"%d",&budget);
        insert_into_bst(root,budget);
   }
    fclose(fp);
}

/*
Function Name: buildPrefix
Input Params:  pattern(char *) - Pattern to be searched for
               m(int) - Length of the pattern
               prefix(int *) - Prefix array
Return Type:   NULL
Description:   Builds the prefix array for the Knuth-Morris-Pratt algorithm
*/
void buildPrefix(char *pattern, int m, int *prefix) {
    int length = 0;
    int i = 1;

    prefix[0] = 0;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            prefix[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = prefix[length - 1];
            } else {
                prefix[i] = 0;
                i++;
            }
        }
    }
}

/*
Function Name: Knuth_Morris_Pratt
Input Params:  text(char *) - Text to be searched
               pattern(char *) - Pattern to be searched for
               prefix(int *) - Prefix array
Return Type:   int
Description:   Searches for the pattern in the text using the Knuth-Morris-Pratt algorithm
*/
int Knuth_Morris_Pratt(const char *text, const char *pattern, int *prefix){
    int i = 0;
    int j = 0;
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);

    while (i < text_len) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        } 
        else {
            if (j != 0) {
                j = prefix[j - 1];
            } else {
                i++;
            }
        }

        if (j == pattern_len) {
            return i - j;
        }
    }

    return -1;
}

/*
Function Name: sign_in_menu
Input Params:  NULL
Return Type:   NULL
Description:   Displays the sign in menu
*/
void sign_in_menu()
{
    int choice;
    printf("1.Sign in \n");
    printf("2.Register \n");
    printf("3.Continue as a Guest \n\n");
}

/*
Function Name: sign_in
Input Params:  NULL
Return Type:   NULL
Description:   Prompts the user to enter the username and password
*/
void sign_in()
{
    printf("Enter username:");
    scanf("%s", username);

        int index = -1;//stores the index of the username in the users array
        for (int i = 0; i < 3; i++) {
            int prefix[50]; // Adjust the size based on the maximum length of the username
            if(strlen(users[i].username)==strlen(username))
            {
            Knuth_Morris_Pratt(users[i].username, username, prefix);//calls the Knuth_Morris_Pratt function to find the index of the username in the users array
            index = Knuth_Morris_Pratt(username, users[i].username, prefix);//stores the index of the username in the users array if found, else -1 remains.
            }
            else
            {
                //printf("Username not found! \n");
                break;
            }
            if (index != -1) {
                printf("Welcome %s \n", username);
                printf("Enter the password to continue\n");
                scanf("%s", password);
                password_compare(users[index].hashed_pass, password);
                break;
            }
        }

        if (index == -1) {
            printf("Username not found! \n");
        }
}



/*
Function Name: sign_up
Input Params:  NULL
Return Type:   NULL
Description:   Prompts the user to enter the username and password  
*/
void sign_up()
{
    int temp_budget;
    char temp_locality[20];
    struct size temp_size;

    printf("Enter username:");
    scanf("%s", usname);

    printf("Enter password:");
    scanf("%s", psword);

    password_hasher(psword);

    printf("Account created successfully!\n\n");

    printf("Let us know what you are looking for to receive personalised recommendations\n");
    printf("----------------------------------------------------------------------------\n");

    printf("Locality:");
    scanf("%s",temp_locality);

    printf("Budget:");
    scanf("%d",&temp_budget);

    printf("Size of Property(feet x feet):");
    scanf("%d %d",&temp_size.m,&temp_size.n); 

    FILE *fp;
    fp=fopen("username_password.txt","a");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s %s %s %d %d %d\n", usname, psword, temp_locality, temp_budget, temp_size.m, temp_size.n);
    fclose(fp);
}

struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
};
typedef struct tree TREE;
TREE * root;
root = NULL;
int choice = 0;
int data = 0;
int count = 0;

/*
Function Name: insert_into_bst
Input Params:  Root of the tree and data item to be inserted
Return Type:   Updated root of the tree
Description:   Inserts a node into a binary search tree at
               appropriate position
*/
TREE * insert_into_bst(TREE * root, int data)
{
	TREE *newnode,*currnode,*parent;

	// Dynamically allocate the memory using malloc
	newnode=(TREE*)malloc(sizeof(TREE));

	// Check if the memory allocation was successful
	if(newnode==NULL)
	{
        printf("Memory allocation failed\n");
        return root;
	}

	// Initialize the tree node elements
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;

	// When the first insertion happens which is the root node
	if(root == NULL)
	{
		root = newnode;
		printf("Root node inserted into tree\n");
		return root;
	}

	// Traverse through the desired part of the tree using
	// currnode and parent pointers
	currnode = root;
	parent = NULL;
	while(currnode != NULL)
	{
		parent = currnode;
		if(newnode->data < currnode->data)
			currnode = currnode->left;
		else
			currnode = currnode->right;
	}

    // Attach the node at appropriate place using parent
	if(newnode->data < parent->data)
		parent->left = newnode;
	else
		parent->right = newnode;

    // print the successful insertion and return root
    printf("Node inserted successfully into the tree\n");
    return root;
}

/*
Function Name: inorder
Input Params:  Root of the tree
Return Type:   void
Description:   Recursively visits the tree in the order of
               Left, Root, Right
*/
void inorder(TREE *troot)
{
	if(troot != NULL)
    	{
        	inorder(troot->left);
        	printf("%d\t",troot->data);
        	inorder(troot->right);
	}
}

/*
Function Name: preorder
Input Params:  Root of the tree
Return Type:   void
Description:   Recursively visits the tree in the order of
               Root, Left, Right
*/
void preorder(TREE *troot)
{
	if(troot != NULL)
	{
        	printf("%d\t",troot->data);
        	preorder(troot->left);
        	preorder(troot->right);
	}
}


/*
Function Name: postorder
Input Params:  Root of the tree
Return Type:   void
Description:   Recursively visits the tree in the order of
               Left, Right, Root
*/
void postorder(TREE *troot)
{
	if(troot != NULL)
	{
        	postorder(troot->left);
        	postorder(troot->right);
        	printf("%d\t",troot->data);
	}
}


/*
Function Name: delete_from_bst
Input Params:  Root of the tree, item data to be deleted
Return Type:   Updated root of the tree
Description:   Deletes the specified data and re-adjusts the
               tree structure according to bst tree constraints
*/

TREE * delete_from_bst(TREE * root, int data)
{
    TREE * currnode, *parent, *successor, *p;

    // Check if the tree is empty
    if(root == NULL)
    {
        printf("Tree is empty\n");
        return root;
    }

    // Traverse and reach the appropriate part of the tree
    parent = NULL;
    currnode = root;
    while (currnode != NULL && data != currnode->data)
    {
        parent = currnode;
        if(data < currnode->data)
            currnode  = currnode->left;
        else
            currnode = currnode->right;
    }

    // If the data is not present in the tree
    if(currnode == NULL)  {
        printf("Item not found\n");
        return root;
    }

    // Check and manipulate if either left subtree is absent,
    // or right subtree is absent
    // or both are present
    if(currnode->left == NULL)
        p = currnode->right;
    else if (currnode->right == NULL)
        p = currnode->left;
    else
    {
	 // Process of finding the inorder successor
        successor = currnode->right;
        while(successor->left != NULL)
            successor = successor->left;

        successor->left = currnode->left;
        p = currnode->right;
    }

    // The case of root deletion
    if (parent == NULL) {
        free(currnode);
        return p;
    }

    if(currnode == parent ->left)
        parent->left = p;
    else
        parent->right = p;

    free(currnode);
    return root;
}

search(TREE *root,int data)
{
    if(root==NULL)
    {
        //printf("Tree is empty\n");
        return 0;
    }
    if(root->data==data)
    {
        //printf("Item found\n");
        return 1;
    }
    if(data<root->data)
        search(root->left,data);
    else
        search(root->right,data);
}


void merge(int arr[],int l,int m,int r)
{
    int i,j,k;
    int n1=m-l+1;
    int n2=r-m;
    int L[n1],R[n2];
    for(i=0;i<n1;i++)
        L[i]=arr[l+i];
    for(j=0;j<n2;j++)
        R[j]=arr[m+1+j];
    i=0;
    j=0;
    k=l;
    while(i<n1 && j<n2)
    {
        if(L[i]<=R[j])
        {
            arr[k]=L[i];
            i++;
        }
        else
            {
                arr[k]=R[j];
                j++;
            }
        k++;
    }
    while(i<n1)
    {
        arr[k]=L[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        arr[k]=R[j];
        j++;
        k++;
    }
}

void mergesort(int arr[],int l,int r)
{
    if(l<r)
    {
        int m=(l+r)/2;
        mergesort(arr,l,m);
        mergesort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}

void quicksort(int arr[],int low,int high)
{
    int i,j,pivot,temp;
    if(low<high)
    {
        pivot=low;
        i=low;
        j=high;
        while(i<j)
        {
            while(arr[i]<=arr[pivot] && i<high)
                i++;
            while(arr[j]>arr[pivot])
                j--;
            if(i<j)
            {
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
        temp=arr[pivot];
        arr[pivot]=arr[j];
        arr[j]=temp;
        quicksort(arr,low,j-1);
        quicksort(arr,j+1,high);
    }
}


void bubble_sort(int arr[],int n)
{
    int i,j,temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
            {
                if(arr[j]>arr[j+1])
                {
                    temp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }

            }
    }
}


void selection_sort(int arr[],int n)
{
    int i,j,min,temp;
    for(i=0;i<n-1;i++)
    {
        min=i;
        for(j=i+1;j<n;j++)
            {
                if(arr[j]<arr[min])
                    min=j;
            }
        temp=arr[i];
        arr[i]=arr[min];
        arr[min]=temp;
    }
}


void insertion_sort(int arr[],int n)
{
    int i,j,key;
    for(i=1;i<n;i++)
    {
        key=arr[i];
        j=i-1;
        while(j>=0 && arr[j]>key)
            {
                arr[j+1]=arr[j];
                j=j-1;
            }
        arr[j+1]=key;
    }
}

void shuffle(int arr[],int n)
{
    int i,temp;
    for(i=0;i<n;i++)
    {
        temp=arr[i];
        arr[i]=arr[rand()%n];
        arr[rand()%n]=temp;
    }
}

int is_sorted(int arr[],int n)
{
    int i;
    for(i=0;i<n-1;i++)
    {
        if(arr[i]>arr[i+1])
            return 0;
    }
    return 1;
}

void bad_luck_sort(int arr[],int n)
{
    int i;
    while(!is_sorted(arr,n))
    {
        shuffle(arr,n);
    }
}

//use trie data structure to store the locality names and search for the locality name entered by the user

struct trie_node
{
    int value;
    struct trie_node *children[26];
};

struct trie_node *get_node()
{
    struct trie_node *pnode=NULL;
    pnode=(struct trie_node *)malloc(sizeof(struct trie_node));
    if(pnode)
    {
        int i;
        pnode->value=0;
        for(i=0;i<26;i++)
            pnode->children[i]=NULL;
    }
    return pnode;
}

void insert(struct trie_node *root,char *key)
{
    int level;
    int length=strlen(key);
    int index;
    struct trie_node *pnode=root;
    for(level=0;level<length;level++)
    {
        index=key[level]-'a';
        if(!pnode->children[index])
            pnode->children[index]=get_node();
        pnode=pnode->children[index];
    }
    pnode->value=1;
}

int search(struct trie_node *root,char *key)
{
    int level;
    int length=strlen(key);
    int index;
    struct trie_node *pnode=root;
    for(level=0;level<length;level++)
    {
        index=key[level]-'a';
        if(!pnode->children[index])
            return 0;
        pnode=pnode->children[index];
    }
    return (pnode!=NULL && pnode->value);
}

int is_leaf_node(struct trie_node *root)
{
    return root->value!=0;
}

int is_free_node(struct trie_node *root)
{
    int i;
    for(i=0;i<26;i++)
    {
        if(root->children[i])
            return 0;
    }
    return 1;
}


