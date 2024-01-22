#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//including libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include "locals.h"


void mainMenu();
void password_hasher(char *password);
void password_compare(char *user_password, char *password);
void readDataFromFile(struct user_credentials users[], int size, FILE *fp);
int Knuth_Morris_Pratt(const char *text, const char *pattern, int *prefix);
void sign_in_menu();

#endif
