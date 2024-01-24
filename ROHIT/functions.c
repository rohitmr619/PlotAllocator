#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "locals.h"
#include"functions.h"


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
void filePointerinit(){
    fp1=fopen("username_password.txt","r");
    fp2=fopen("house_dataset_sale.txt","r");
    if (fp1 == NULL || fp2 == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
}

/*
Function Name: password_hasher
Input Params:  password(char *) - Password entered by the user
Return Type:   NULL
Description:   Hashes the password entered by the user
efficiency: O(n)
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

void readDataFromFile(struct user_credentials users[],struct homeRecord records[], int size) 
{
    trie_root = getNode_trie();
    int counter=0;
    int budget=0;
    char cities[4];
    int i = 0;
    int temp;
    char temp_c;
    //printf("lama");
   for(counter=0; !feof(fp1) && counter<size; counter++){
        fscanf(fp1, "%s %s %s %d %d %d", users[counter].username, users[counter].hashed_pass, users[counter].user_locality, &users[counter].user_budget, &users[counter].user_size.m, &users[counter].user_size.n);
   }

   for(i=0; !feof(fp2); i++){
        fscanf(fp2, "%s %d %d %d %d %d %d %c %d",records[i].location, &records[i].price, &records[i].x_cord, &records[i].y_cord, &records[i].sizel, &records[i].sizeb, &records[i].no_of_bedrooms, &records[i].type, &records[i].year);
   }
   fseek(fp2, 0, SEEK_SET);
   while (fscanf(fp2, "%s %d %d %d %d %d %d %c %d", cities, &budget_sort[i], &temp, &temp, &temp, &temp, &temp, &temp_c, &temp) != EOF) 
    {
        //printf("%s", cities);
       insert_trie(trie_root, cities);
       i++;
    }
    
    //printf("lama");
    budget_size = i;
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


/*
Function Name: insert_into_bst
Input Params:  Root of the tree and data item to be inserted
Return Type:   Updated root of the tree
Description:   Inserts a node into a binary search tree at
               appropriate position
*/
TREE * insert_into_bst(TREE * root, struct homeRecord temp)
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
	newnode->data = temp;
	newnode->left = NULL;
	newnode->right = NULL;

	// When the first insertion happens which is the root node
	if(root == NULL)
	{
		root = newnode;
		//printf("Root node inserted into tree\n");
		return root;
	}

	// Traverse through the desired part of the tree using
	// currnode and parent pointers
	currnode = root;
	parent = NULL;
	while(currnode != NULL)
	{
		parent = currnode;
		if(newnode->data.price < currnode->data.price)
			currnode = currnode->left;
		else
			currnode = currnode->right;
	}

    // Attach the node at appropriate place using parent
	if(newnode->data.price < parent->data.price)
		parent->left = newnode;
	else
		parent->right = newnode;

    // print the successful insertion and return root
    //printf("Node inserted successfully into the tree\n");
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
        	printf("%s\t %d\t %d\t %d\t %d\t %d\t %d\t %c\t %d\t \n",troot->data.location,
            troot->data.price,troot->data.x_cord,troot->data.y_cord,troot->data.sizel,troot->data.sizeb,troot->data.no_of_bedrooms,troot->data.type,troot->data.year);
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
    while (currnode != NULL && data != currnode->data.price)
    {
        parent = currnode;
        if(data < currnode->data.price)
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

/*
Function Name: search_in_bst
Input Params:  Root of the tree, item data to be searched
Return Type:   1 if found, 0 if not found
Description:   Searches for the specified data in the tree
*/
int search_in_bst(TREE * root, int data)
{
    TREE * currnode;
    currnode = root;
    while (currnode != NULL && data != currnode->data.price)
    {
        if(data < currnode->data.price)
            currnode  = currnode->left;
        else
            currnode = currnode->right;
    }

    if(currnode == NULL)  {
        printf("Item not found\n");
        return 0;
    }
    else
    {
        printf("There is a house for that budget!\n");
        printf("%s\t %d\t %d\t %d\t %d\t %d\t %d\t %c\t %d\t \n",currnode->data.location,currnode->data.price,currnode->data.x_cord,currnode->data.y_cord,currnode->data.sizel,currnode->data.sizeb,currnode->data.no_of_bedrooms,currnode->data.type,currnode->data.year);
        return 1;
    }
}

/*
Function Name: merge
Input Params:  arr(int []) - Array to be sorted
               l(int) - Left index
               m(int) - Middle index
               r(int) - Right index
Return Type:   NULL
Description:   Merges two subarrays of arr[]
*/
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

/*
Function Name: mergesort
Input Params:  arr(int []) - Array to be sorted
               l(int) - Left index
               r(int) - Right index
Return Type:   NULL
Description:   Sorts the array using the merge sort algorithm
*/
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

/*
Function Name: quicksort
Input Params:  arr(int []) - Array to be sorted
               low(int) - Left index
               high(int) - Right index
Return Type:   NULL
Description:   Sorts the array using the quick sort algorithm
*/
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

/*
Function Name: bubble_sort
Input Params:  arr(int []) - Array to be sorted
               n(int) - Size of the array
Return Type:   NULL
Description:   Sorts the array using the bubble sort algorithm
*/
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

/*
Function Name: selection_sort
Input Params:  arr(int []) - Array to be sorted
               n(int) - Size of the array
Return Type:   NULL
Description:   Sorts the array using the selection sort algorithm
*/
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

/*
Function Name: insertion_sort
Input Params:  arr(int []) - Array to be sorted
               n(int) - Size of the array
Return Type:   NULL
Description:   Sorts the array using the insertion sort algorithm
*/
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
/*
Function Name: shuffle
Input Params:  arr(int []) - Array to be shuffled
               n(int) - Size of the array
Return Type:   NULL
Description:   Shuffles the array
*/
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

/*
Function Name: is_sorted
Input Params:  arr(int []) - Array to be checked
               n(int) - Size of the array
Return Type:   1 if sorted, 0 if not sorted
Description:   Checks if the array is sorted
*/
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
/*
Function Name: bad_luck_sort
Input Params:  arr(int []) - Array to be sorted
               n(int) - Size of the array
Return Type:   NULL
Description:   Sorts the array using the bad luck sort algorithm
*/
void bad_luck_sort(int arr[],int n)
{
    int i;
    while(!is_sorted(arr,n))
    {
        shuffle(arr,n);
    }
}


struct TrieNode
{
    struct TrieNode *children[26];
 
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

/*
Function Name: getNode_trie
Input Params:  NULL
Return Type:   struct TrieNode *
Description:   Returns new trie node (initialized to NULLs)
*/
struct TrieNode *getNode_trie()
{
    struct TrieNode *pNode = NULL;
 
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
 
    if (pNode)
    {
        int i;
 
        pNode->isEndOfWord = false;
 
        for (i = 0; i <26; i++)
            pNode->children[i] = NULL;
    }
 
    return pNode;
}
 
/*
Function Name: insert_trie
Input Params:  root(struct TrieNode *) - Root of the trie
               key(const char *) - Key to be inserted
Return Type:   NULL
Description:   Inserts the key into the trie
*/
void insert_trie(struct TrieNode *root, const char key[4])
{
    int level;
    int length = strlen(key);
    int index;
 
    struct TrieNode *pCrawl = root;
 
    for (level = 0; level < length; level++)
    {
        index = (int)key[level] - 'A';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode_trie();
 
        pCrawl = pCrawl->children[index];
    }
 
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}
 

/*
Function Name: search_trie
Input Params:  root(struct TrieNode *) - Root of the trie
               key(const char *) - Key to be searched for
Return Type:   bool
Description:   Searches for the key in the trie
*/
bool search_trie(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
 
    for (level = 0; level < length; level++)
    {
        index = (int)key[level] - 'A';
 
        if (!pCrawl->children[index])
            return false;
 
        pCrawl = pCrawl->children[index];
    }
 
    return (pCrawl->isEndOfWord);
}


/*
Function Name: dijikstra
Input Params:  graph(int [][NUM_HOUSES]) - Adjacency matrix of the graph
               src(int) - Source vertex
               nearestHouses(int [NUM_HOUSES]) - Array to store the nearest houses
Return Type:   NULL
Description:   Finds the shortest path from the source vertex to all other vertices
*/
void dijikstra(int graph[NUM_HOUSES][NUM_HOUSES], int src, int nearestHouses[NUM_HOUSES]) {
    int dist[NUM_HOUSES]; // Shortest distance from source to each house
    int visited[NUM_HOUSES]; // Marks whether a house is visited or not

    // Initialize distances and visited array
    for (int i = 0; i < NUM_HOUSES; i++) {
        dist[i] = 999;
        visited[i] = 0;
    }

    dist[src] = 0; // Distance from source to itself is 0

    for (int count = 0; count < NUM_HOUSES - 1; count++) {
        int minDist = 999;
        int minIndex;

        // Find the house with the minimum distance
        for (int i = 0; i < NUM_HOUSES; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }

        visited[minIndex] = 1; // Mark the selected house as visited

        // Update the distance values of adjacent houses
        for (int i = 0; i < NUM_HOUSES; i++) {
            if (!visited[i] && graph[minIndex][i] && dist[minIndex] != 999
                && dist[minIndex] + graph[minIndex][i] < dist[i]) {
                dist[i] = dist[minIndex] + graph[minIndex][i];
                nearestHouses[i] = minIndex; // Store the row number of the nearest house
            }
        }
    }
}

/*
Function Name: agents_load()
Input Params:  NULL
Return Type:   NULL
Description:   Loads the agents data from the real_agents_contacts.txt file
*/
void agents_load()
{
    fp3=fopen("real_agents_contacts.txt","r");
    if (fp1 == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while(!feof(fp3))
    {
        fscanf(fp3,"%s %11d %s %11d",agents[i].name, &agents[i].ph_no, agents[i].locality, &agents[i].salary);
        i++;
    }
    fclose(fp3);
}

/*
Function Name: display_agents()
Input Params:  agents(struct agent_data []) - Array of type agent_data
               start(int) - Starting index
               end(int) - Ending index
Return Type:   NULL
Description:   Displays the agents data
*/
void display_agents(struct agent_data agents[24], int start, int end) {
    printf("\n---------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-20s | %-10s |\n", "Name", "Phone Number", "Locality", "Salary");
    printf("---------------------------------------------------------\n");
    
    for (int i = start; i < end; i++) {
        printf("| %d | %-15s | %-15lld | %-20s | %-10d |\n",i+1, agents[i].name, agents[i].ph_no, agents[i].locality, agents[i].salary);
    }

    printf("---------------------------------------------------------\n");
}

/*
Function Name: display_fav_agents()
Input Params:  agents(struct agent_data []) - Array of type agent_data
               start(int) - Starting index
               end(int) - Ending index
Return Type:   NULL
Description:   Displays the favourite agents data
*/
void add_to_favs()
{
    int i=0,axt=1;
    printf("Would you like to add any to favourites?\n");
    printf("1.Yes\n");
    printf("2.No\n");
    scanf("%d",&choice);
    //use linked list to add to favourites
    switch(choice)
    {
        case 1: while(axt)
                {
                    printf("Enter the agent number you want to add to favourites\n");
                    scanf("%d",&agent_selected);
                    if(agent_selected>0 && agent_selected<25)
                    {
                        fav_list[i]=agent_selected;
                        i++;
                        printf("Agent added to favourites\n");
                        printf("Would you like to add more?\n");
                        printf("1.Yes\n");
                        printf("0.No\n");
                        scanf("%d",&axt);
                    }
                }
                break;
        case 2: break;
        default: printf("Invalid choice\n");
                 exit(0);
    }
}


/*
Function Name: display_fav_agents()
Input Params:  agents(struct agent_data []) - Array of type agent_data
               start(int) - Starting index
               end(int) - Ending index
Return Type:   NULL
Description:   Displays the favourite agents data
*/
struct Node* create_node(struct agent_data data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

/*
Function Name: insert_node()
Input Params:  head(struct Node **) - Pointer to the head of the linked list
               data(struct agent_data) - Data to be inserted
Return Type:   NULL
Description:   Inserts a node into the linked list
*/
void insert_node(struct Node** head, struct agent_data data) {
    struct Node* new_node = create_node(data);

    new_node->next = *head;
    *head = new_node;
}

/*
Function Name: print_list()
Input Params:  head(struct Node *) - Pointer to the head of the linked list
Return Type:   NULL
Description:   Prints the linked list
*/
void print_list(struct Node* head) {
    while (head != NULL) {
        printf("| %-15s | %-15lld | %-20s | %-10d |\n", head->data.name, head->data.ph_no, head->data.locality, head->data.salary);
        head = head->next;
    }
    printf("----------------------------------------------\n");
}