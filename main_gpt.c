#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct location
{
    int x, y;
};

struct size
{
    int m, n;
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

struct homeRecord HRecord[20];
int hc = 0;

void init()
{
    for (int i = 0; i < 80; i++)
        printf("*");
    printf("\n\t\t\tHOME/PLOT ALLOCATION BOT\n\n");
    for (int i = 0; i < 80; i++)
        printf("*");
    printf("\n\n");
}

void readHomeData(FILE *fp)
{
    for (hc = 0; !feof(fp) && hc < 20; hc++)
        fscanf(fp, "%s %lld %d %d %d %d %d %c %d", HRecord[hc].house_id, &HRecord[hc].price, &HRecord[hc].l.x, &HRecord[hc].l.y, &HRecord[hc].s.m, &HRecord[hc].s.n, &HRecord[hc].no_of_bedrooms, &HRecord[hc].type, &HRecord[hc].year);
}

void buyHome(int i)
{
    int index = (i - 1) % 20;
    char c;
    printf("Do you want to buy home %s (y/n): ", HRecord[index].house_id);
    scanf(" %c", &c);  // Note the space before %c to consume the newline character
    if (tolower(c) == 'y')
    {
        printf("Congratulations! You have successfully purchased %s.\n", HRecord[index].house_id);
        // Add further actions if needed
    }
    else
    {
        printf("Purchase canceled.\n");
        // Add further actions if needed
    }
}

void searchHomesByPriceRange(long long int minPrice, long long int maxPrice)
{
    for (int i = 0; i < hc; i++)
    {
        if (HRecord[i].price >= minPrice && HRecord[i].price <= maxPrice)
        {
            printf("%s - Price: %lld, Size: %dx%d, Bedrooms: %d\n", HRecord[i].house_id, HRecord[i].price, HRecord[i].s.m, HRecord[i].s.n, HRecord[i].no_of_bedrooms);
        }
    }
}

void searchHomesByLocation(struct location loc)
{
    // Implement searching homes by location based on your criteria
    // You can use the loc.x and loc.y values
}

void searchHomesBySize(struct size sz)
{
    // Implement searching homes by size based on your criteria
    // You can use the sz.m and sz.n values
}

int main()
{
    init();
    int ch, i, j, k;
    char c;
    FILE *fpHome;
    while (1)
    {
        printf("About what are you looking for :\n");
        printf("1.Plot.\t\t\t2.Home.\t\t\t3.Commercial.\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            // Implement functionality for plots
            break;
        case 2:
            printf("Press 'b' to buy and 'r' to rent: ");
            scanf(" %c", &c);
            if (tolower(c) == 'b')
            {
                fpHome = fopen("house_dataset_sale.txt", "r+");
                while (ch != -2)
                {
                    i = 1;
                    readHomeData(fpHome);
                    j = 0, k = 5;
                    while (hc != 0)
                    {
                        for (; j < hc && j < k; j++)
                            printf("%d. %s with price %lld of size %dx%d\n", i++, HRecord[j].house_id, HRecord[j].price, HRecord[j].s.m, HRecord[j].s.n);
                        printf("Enter choice (0 - to next -1 - to prev and -2 - to stop): ");
                        scanf("%d", &ch);
                        if (ch == 0)
                            k += 5;
                        else if (ch == -1 && j == 6)
                            j -= 5, i -= 5, k = 5;
                        else if (ch == -1 && j > 10)
                            j -= 10, k -= 5, i -= 10;
                        else if (ch == -2)
                            break;
                        else if (ch > k - 5 && ch <= k)
                        {
                            buyHome(ch);
                            ch = -2;
                            break;
                        }
                    }
                }
                printf("Search home using [1.Price range.   2.location.   3.size.]\n");
                printf("Enter choice: ");
                int searchChoice;
                scanf("%d", &searchChoice);
                switch (searchChoice)
                {
                case 1:
                    printf("Enter minimum and maximum price: ");
                    long long int minPrice, maxPrice;
                    scanf("%lld %lld", &minPrice, &maxPrice);
                    searchHomesByPriceRange(minPrice, maxPrice);
                    break;
                case 2:
                    // Implement searching homes by location
                    break;
                case 3:
                    // Implement searching homes by size
                    break;
                default:
                    printf("Invalid choice for home search.\n");
                    break;
                }

                fclose(fpHome);
            }
            break;
        case 3:
            // Implement functionality for commercial properties
            break;
        default:
            printf("The program has been terminated.\n \t\t\tThank you.");
            exit(0);
            break;
        }
        printf("\n");
    }
}
