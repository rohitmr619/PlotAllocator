#ifndef LOCALS_H_INCLUDED
#define LOCALS_H_INCLUDED

struct location
{
    double x, y; // <latitude, longitude>
};

struct size
{
    int m,n; // dimensions of the home/plot
};

struct user_credentials {
    char username[50];
    char hashed_pass[50];
    char user_locality[20];
    int user_budget;
    struct size user_size;
};

struct homeRecord
{
    char location[4];
    int price;
    int x_cord;
    int y_cord;
    int sizel;
    int sizeb;
    int no_of_bedrooms;
    char type;
    int year;
};

struct tree
{
	struct homeRecord data;
	struct tree *left;
	struct tree *right;
};
typedef struct tree TREE;
TREE * root=NULL;
int choice = 0;
int data = 0;
int count = 0;



char username[20];//stores the username entered by the user
char password[20];//stores the password entered by the user
char usname[20];//stores the username entered by the user(temporary variable)
char psword[20];//stores the password entered by the user(temporary variable)

FILE *fp1, *fp2;//file pointer to open the username_password.txt file
struct TrieNode *trie_root;
int budget_sort[100];
int budget_size;
int choice;
int search_budget;
char search_locality[20];
struct user_credentials users[100]; // initialize an array of type user_credentials,Adjust the size based on the number of users
struct homeRecord records[100]; // initialize an array of type homeRecord,Adjust the size based on the number of records
#endif // LOCALS_H_INCLUDED