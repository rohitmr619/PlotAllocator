#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"//function.h causing errors at the moment

int main() {
    
    fp=filePointerinit(fp);//opens the username_password.txt file
    readDataFromFile(users, 2, fp);  // Reads data from username_password.txt and stores it in users array.

    while (1) {
        mainMenu(); // Menu to display the welcome message and prompt the user to enter the username
        sign_in_menu();
        printf("Enter your choice:");
        scanf("%d",&choice);
        if(choice==1){
            sign_in();
            break;
        }
        else if(choice==2){
            sign_up();
            break;
        }
        else if(choice==3)
            continue;
        else{
            printf("Invalid choice\n");
            exit(0);
        }
    }

    fclose(fp);
    return 0;
}
