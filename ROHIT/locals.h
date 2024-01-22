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
    char house_id[7];
    long long int price;
    struct location l;
    struct size s;
    int no_of_bedrooms;
    char type;
    int year;
};

struct user_profile
{
    char username[50];
    char name[50];
    long long int budget;
    char location[50];
    char hashed_pass[50];
};

struct tree
{
	struct homeRecord data;
	struct tree *left;
	struct tree *right;
};
typedef struct tree TREE;

char username[20];//stores the username entered by the user
char password[20];//stores the password entered by the user
char usname[20];//stores the username entered by the user(temporary variable)
char psword[20];//stores the password entered by the user(temporary variable)

FILE *fp, *fp1;//file pointer to open the username_password.txt file

int choice;
struct user_credentials users[100]; // initialize an array of type user_credentials,Adjust the size based on the number of users
#endif // LOCALS_H_INCLUDED