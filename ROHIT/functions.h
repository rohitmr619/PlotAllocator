#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//including libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include<stdbool.h>
#include "locals.h"



void mainMenu();
void password_hasher(char *password);
void password_compare(char *user_password, char *password);
void filePointerinit();
int Knuth_Morris_Pratt(const char *text, const char *pattern, int *prefix);
bool search_trie(struct TrieNode *root, const char *key);
void insert_trie(struct TrieNode *root, const char *key);
struct TrieNode *getNode_trie();
void sign_in_menu();

#endif
