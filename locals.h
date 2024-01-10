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

char username[20];//stores the username entered by the user
char password[20];//stores the password entered by the user
FILE *fp;//file pointer to open the username_password.txt file



#endif // LOCALS_H_INCLUDED