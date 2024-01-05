#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init()
{
    for (int i = 0; i < 80; i++)
        printf("*");
    printf("\n\t\t\tHOME/PLOT ALLOCATION BOT\n\n");
    for (int i = 0; i < 80; i++)
        printf("*");
    printf("\n\n");
}

// Function declarations for different functionalities
void plotFunctionality();
void homeFunctionality();
void commercialFunctionality();

int main()
{
    init();
    int ch;

    while (1)
    {
        printf("About what are you looking for :\n");
        printf("1.Plot.\t\t\t2.Home.\t\t\t3.Commercial.\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            plotFunctionality();
            break;
        case 2:
            homeFunctionality();
            break;
        case 3:
            commercialFunctionality();
            break;
        default:
            printf("The program has been terminated.\n \t\t\tThanking you.");
            exit(0);
        }
        printf("\n");
    }
}

// Function definitions for different functionalities

void plotFunctionality()
{
    int plotChoice;

    printf("1. Ready to move in.\n");
    printf("2. Investment.\n");
    printf("Enter choice: ");
    scanf("%d", &plotChoice);

    switch (plotChoice)
    {
    case 1:
        // Code for ready to move in plots
        break;
    case 2:
        // Code for investment type plots
        break;
    default:
        printf("Invalid choice for plot functionality.\n");
        break;
    }
}

void homeFunctionality()
{
    int homeChoice;

    printf("1. Buy.\n");
    printf("2. Rent.\n");
    printf("Enter choice: ");
    scanf("%d", &homeChoice);

    switch (homeChoice)
    {
    case 1:
        // Code for buy-able houses
        break;
    case 2:
        // Code for rent-able houses
        break;
    default:
        printf("Invalid choice for home functionality.\n");
        break;
    }
}

void commercialFunctionality()
{
    int commercialChoice;

    printf("1. Buy.\n");
    printf("2. Lease.\n");
    printf("3. Both.\n");
    printf("Enter choice: ");
    scanf("%d", &commercialChoice);

    switch (commercialChoice)
    {
    case 1:
        // Code for buy-able buildings
        break;
    case 2:
        // Code for lease-able buildings
        break;
    case 3:
        // Code for both-able buildings
        break;
    default:
        printf("Invalid choice for commercial functionality.\n");
        break;
    }
}
