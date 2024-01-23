#ifndef LOCALS_H_INCLUDED
#define LOCALS_H_INCLUDED
#define NUM_HOUSES 20

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

int graph[20][20] = 
       {{0,  24,  12,  81,  59,  92,  11,  45,  68,  15,  40,  72,  80,  20,  88,  75,  91,  64,  89,  57},
        {24, 0,   73,  19,  18,  48,  95,  65,  76,  86,  97,  28,  72,  71,  30,  99,  29,  90,  42,  49},
        {12, 73,  0,   27,  31,  21,  37,  52,  32,  94,  50,  34,  78,  65,  87,  77,  36,  22,  79,  38},
        {81, 19,  27,  0,   68,  85,  79,  91,  96,  47,  67,  58,  53,  56,  5,   14,  4,   39,  35,  55},
        {59, 18,  31,  68,  0,   41,  10,  26,  8,   2,   63,  69,  62,  85,  97,  82,  63,  9,   93,  15},
        {92, 48,  21,  85,  41,  0,   60,  61,  46,  74,  50,  9,   84,  81,  31,  47,  27,  61,  31,  9},
        {11,  95,  37,  79,  10,  60,  0,   74,  46,  92,  98,  38,  67,  26,  34,  51,  66,  89,  93,  15},
        {45,  65,  52,  91,  26,  61,  74,  0,   71,  96,  21,  27,  66,  7,   5,   98,  41,  1,   35,  80},
        {68,  76,  32,  96,  8,   46,  46,  71,  0,   1,   12,  91,  26,  16,  37,  13,  4,   77,  70,  90},
        {15,  86,  94,  47,  2,   74,  92,  96,  1,   0,   26,  88,  69,  39,  71,  56,  84,  9,   95,  27},
        {40,  97,  50,  67,  63,  50,  98,  21,  12,  26,  0,   44,  84,  87,  22,  93,  11,  58,  78,  71},
        {72,  28,  34,  58,  69,  9,   38,  27,  91,  88,  44,  0,   52,  72,  92,  11,  80,  17,  4,   77},
        {80,  72,  78,  53,  62,  84,  67,  66,  26,  69,  84,  52,  0,   58,  53,  54,  13,  70,  10,  65},
        {20,  71,  65,  56,  85,  81,  26,  7,   16,  39,  87,  72,  58,  0,   7,   61,  48,  13,  86,  43},
        {88,  30,  87,  5,   97,  31,  34,  5,   37,  71,  22,  92,  53,  7,   0,   66,  16,  61,  51,  53},
        {75,  99,  77,  14,  82,  47,  51,  98,  13,  56,  93,  11,  54,  61,  66,  0,   59,  68,  65,  3},
        {91,  29,  36,  4,   63,  27,  66,  41,  4,   84,  11,  80,  13,  48,  16,  59,  0,   89,  14,  23},
        {64,  90,  22,  39,  9,   61,  89,  1,   77,  9,   58,  17,  70,  13,  61,  68,  89,  0,   36,  39}, 
        {89,  42,  79,  35,  93,  31,  93,  35,  70,  95,  78,  4,   10,  86,  51,  65,  14,  36,  0,   74},
        {57,  49,  38,  55,  15,  9,   15,  80,  90,  27,  71,  77,  65,  43,  53,  3,   23,  39,  74,  0}
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

int house_number=0;

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
int nearest_houses[20];
struct user_credentials users[100]; // initialize an array of type user_credentials,Adjust the size based on the number of users
struct homeRecord records[100]; // initialize an array of type homeRecord,Adjust the size based on the number of records
#endif // LOCALS_H_INCLUDED