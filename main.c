#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"//function.h causing errors at the moment

struct user_credentials users[2]; // initialize an array of type user_credentials,Adjust the size based on the number of users

int main() {
    
    fp=filePointerinit(fp);//opens the username_password.txt file
    readDataFromFile(users, 2, fp);  // Reads data from username_password.txt and stores it in users array.

    while (1) {
        mainMenu(); // Menu to display the welcome message and prompt the user to enter the username
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

    fclose(fp);
    return 0;
}
