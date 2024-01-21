#ifndef LOCALS_H_INCLUDED
#define LOCALS_H_INCLUDED

#include<stdio.h>
#include<math.h>

FILE *facility_pointer;

struct location
{
    int x;
    int y;
};

//Stores 
struct facilities_data
{
    int facility_index;
    char facility_type[10];
    struct location coords;
    char facility_name[30];
    char connections[20];
};  

/*-------------------------------------1.Dijkstras-------------------------------------*/

//2D arr that stores the connectivity or road info(0 or 1)
int connection_matrix[20][20];

//2D arr that stores the cost of the edges or roads
int distance_matrix[20][20];

//Array of struct facilities_data that stores data from file
struct facilities_data temp[25];

//Array that stores shortest distance from source
int dist[20];

//Array that stores the previous nodes 
int path[20];

//Array that shows whether a node is visited or not(1 or 0)
int visited[20];
/*-------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
// A structure to represent a 
// node in adjacency list
struct adj_list_node
{
	int dest;
	int weight;
	struct adj_list_node* next;
};

// A structure to represent 
// an adjacency list
struct adj_list
{
// Pointer to head node of list
struct adj_list_node *head; 
};

// A structure to represent a graph. 
// A graph is an arr of adjacency lists.
// Size of arr will be V (number of 
// vertices in graph)
struct Graph
{
	int V;
	struct adj_list* arr;
};

struct Graph* graph;

// Structure to represent a min heap node
struct MinHeapNode
{
	int v;
	int dist;
};

// Structure to represent a min heap
struct MinHeap
{
	
	// Number of heap nodes present currently
	int size;	 

	// Capacity of min heap
	int capacity; 

	// This is needed for decreaseKey()
	int *pos; 
	struct MinHeapNode **arr;
};
#endif // LOCALS_H_INCLUDED
