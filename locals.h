#ifndef LOCALS_H_INCLUDED
#define LOCALS_H_INCLUDED

struct user_credentials {
    char username[50];
    char hashed_pass[50];
};

struct location
{
    double x, y; // <latitude, longitude>
};

struct size
{
    int m,n; // dimensions of the home/plot
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
FILE *fp;//file pointer to open the username_password.txt file

int choice;
struct user_credentials users[2]; // initialize an array of type user_credentials,Adjust the size based on the number of users
#endif // LOCALS_H_INCLUDED