#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"//function.h causing errors at the moment

int main() {
    
    filePointerinit();//opens the username_password.txt file
    readDataFromFile(users,records, 2);
    for ( int i = 0; i < 20; i++)
    {
        root=insert_into_bst(root, records[i]);
    }
    inorder(root);
    //printf("test");
    while (1) {
        mainMenu(); // Menu to display the welcome message and prompt the user to enter the username
        sign_in_menu();
        printf("Enter your choice:");
        scanf("%d",&choice);
        if(choice==1){
            sign_in();
                if (strcmp(username, "rohit") == 0) {
            printf("Would you like to delete an entry? press 0 to continue: \n");
            }
            printf("Search for specific budget? press 1 to continue: \n");
            printf("Check all the records sorted by price? press 2 to continue: \n");
            printf("Search for a specific locality? press 3 to continue: \n");
            scanf("%d", &choice);
            if(choice==1)
            {
                printf("Enter the budget you want to search for: ");
                scanf("%d", &search_budget);
                search_in_bst(root,search_budget);
            }
            else if(choice==0)
            {
                printf("Enter the budget you want to delete : ");
                scanf("%d", &search_budget);
                delete_from_bst(root,search_budget);
                printf("Deleted successfully\n");
            }
            else if(choice==3)
            {
                printf("Where are you searching a house in? ");
                scanf("%s", search_locality);
                bool a = search_trie(trie_root, search_locality);
                if(a) {
                    printf("There are houses available in this locality\n");
                }
                else {
                    printf("No houses available in this locality\n");
                }
            }
            else
            {
                printf("Invalid choice\n");
                exit(0);
            }
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

    fclose(fp1);
    fclose(fp2);
    return 0;
}
