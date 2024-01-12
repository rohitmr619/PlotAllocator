#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locals.h"
//#include "functions.h" //Causing errors at the moment


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
    if (fp == NULL) {
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
Function Name: password_compare
Input Params:  user_password(char *) - Hashed password stored in the users array
               password(char *) - Hashed password entered by the user
Return Type:   NULL
Description:   Compares the hashed password entered by the user with the hashed password stored in the users array
*/
void password_compare(char *user_password, char *password) {
    password_hasher(password);
    if (strcmp(user_password, password) == 0) {
        printf("\n");
        printf("Password accepted!\n");
    } else {
        printf("\n");
        printf("Password incorrect!\n");
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
void readDataFromFile(struct user_credentials users[], int size, FILE *fp) {
    int counter=0;
   for(counter=0; !feof(fp) && counter<size; counter++)
        fscanf(fp, "%s %s", users[counter].username,users[counter].hashed_pass);
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
        for (int i = 0; i < 2; i++) {
            int prefix[50]; // Adjust the size based on the maximum length of the username
            Knuth_Morris_Pratt(users[i].username, username, prefix);//calls the Knuth_Morris_Pratt function to find the index of the username in the users array
            index = Knuth_Morris_Pratt(username, users[i].username, prefix);//stores the index of the username in the users array if found, else -1 remains.

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
    printf("Enter username:");
    scanf("%s", usname);
    printf("Enter password:");
    scanf("%s", psword);
    password_hasher(psword);
    FILE *fp;
    fp=fopen("username_password.txt","a");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s %s\n", usname, psword);
    fclose(fp);
    printf("Account created successfully!\n");
}

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


void profile_set_up()
{
    printf("Enter your budget range: ");
    scanf("%lld",&budget);
    printf("Enter the location: ");
    scanf("%s",location);
}

