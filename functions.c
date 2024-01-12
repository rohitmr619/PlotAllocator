#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locals.h"
//#include "functions.h" //Causing errors at the moment


//Function:     mainMenu
//Description:  Displays the welcome message and prompts the user to enter the username
//Input param:  NULL
//Return Type:  NULL
void mainMenu() {
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\t\t\tHOME PURCHASE BOT\n\n");
    for(int i = 0; i<80; i++)
        printf("*");
    printf("\n\n");
}

//Function:     filePointerinit
//Description:  Opens the username_password.txt file
//Input param:  fp(FILE *) - File pointer to open the username_password.txt file
//Return Type:  FILE * - File pointer to open the username_password.txt file

FILE* filePointerinit(FILE *fp){
    fp=fopen("username_password.txt","r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return fp;
}
//Function:     password_hasher
//Description:  Hashes the password entered by the user
//Input param:  password(char *) - Unhashed
//Return Type:  NULL
void password_hasher(char *password) {
    int i;
    for (i = 0; password[i] != '\0'; i++) {
        password[i] = (password[i] + 3);
    }
}

//Function:     password_compare
//Description:  Compares the hashed password entered by the user with the hashed password stored in the file
//Input param:  user_password(char *) - Hashed password
//Return Type:  NULL
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

//Function:     readDataFromFile
//Description:  Reads the username and hashed password from the file and stores it in the users array
//Input param:  users(struct user_credentials []) - Array of type user_credentials
//              size(int) - Size of the array
//              fp(FILE *) - File pointer to open the username_password.txt file
//Return Type:  NULL
void readDataFromFile(struct user_credentials users[], int size, FILE *fp) {
    int counter=0;
   for(counter=0; !feof(fp) && counter<size; counter++)
        fscanf(fp, "%s %s", users[counter].username,users[counter].hashed_pass);
    fclose(fp);
}

//Function:     Knuth_Morris_Pratt
//Description:  Finds the index of the username in the users array
//Input param:  text(const char *) - Username entered by the user
//              pattern(const char *) - Username stored in the users array
//              prefix(int *) - Array to store the prefix values
//Return Type:  int - Index of the username in the users array
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


void sign_in_menu()
{
    int choice;
    printf("1.Sign in \n");
    printf("2.Register \n");
    printf("3.Continue as a Guest \n\n");
}

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
            printf("Username not found\n");
        }
}

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

