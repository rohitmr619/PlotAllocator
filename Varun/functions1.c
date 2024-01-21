#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include"locals.h"

//Function:     read_facilities1()
//Description:  reads facilities data into arr of structures 
//Input Param:  File pointer
//Return type:  NULL
void read_facilities()
{
    if (facility_pointer == NULL)
    {
        perror("Error opening file");
        return;
    }

    int i   = 1;        //Used to mark assign index to access later

    while(!feof(facility_pointer))
    {
        fscanf(facility_pointer,"%s %d %d %s %s",temp[i].facility_type, &temp[i].coords.x, &temp[i].coords.y, temp[i].facility_name,temp[i].connections);
        temp[i].facility_index = i;
        i++;
    }
    /*for(i = 1; i <= 19; i++)
    {
        printf("%d %s %d %d %s %s\n",temp[i].facility_index, temp[i].facility_type, temp[i].coords.x, temp[i].coords.y, temp[i].facility_name,temp[i].connections);
    }*/

    fclose(facility_pointer);
}

//Function:     dist_formula
//Description:  Finds the distance between 2 points using the distance formula 
//Input Param:  4 integers, that are the X and Y coordinates of both points
//Return type:  Integer : Distance calculated
int dist_formula(int x1, int y1, int x2, int y2)
{
    double temp_distance;
    temp_distance = pow((x2-x1),2) + pow((y2-y1),2);
    temp_distance = sqrt(temp_distance);
    return temp_distance;
}

//Function:     populate_connection_matrix()
//Description:  Populates the connection matrix 
//Input Param:  NULL
//Return type:  NULL
void populate_connection_matrix()
{
    struct location house_coords;
    temp[0].coords.x = 3122;                                           //Dummy house X coordinate
    temp[0].coords.y = 2713;                                           //Dummy house Y coordinate
    char house_connection_string[21] = "01101001000010100101";         //Dummy house connection with facilities

    int i,j;
    for(i=0;i<=19;i++)
    {
        if(i==0)
        {
            for(j=0;j<=19;j++)
                connection_matrix[i][j] = house_connection_string[j]-48;
        }

        else
        {
            for(j=0;j<=19;j++)
                connection_matrix[i][j] = temp[i].connections[j] - 48;
        }
    }
}

//Function:     populate_distance_matrix()
//Description:  Populates the distance matrix 
//Input Param:  NULL
//Return type:  NULL
void populate_distance_matrix()
{
    int i,j;
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            if(connection_matrix[i][j] == 1)
            {
                distance_matrix[i][j] = dist_formula(temp[i].coords.x,temp[i].coords.y,temp[j].coords.x,temp[j].coords.y);
            }
            else if(connection_matrix[i][j] == 0 && i != j)
            {
                distance_matrix[i][j] = 9999;
            }
            else
            {
                distance_matrix[i][j] = 0;
            }
        }
    }
}

//Function:     minimum()
//Description:  A simple function to find minimum between two numbers that makes use of one if statement
//Input Param:  Integer: Number 1, Integer: Number 2
//Return type:  Integer: 1 if a < b, else 0 if a > b
int minimum(int a, int b) {
    if(b > a) 
        return 1;
    return 0;
}

//Function:     calculate_nearest_facilities()
//Description:  Makes use of multiple arrs to determine the nearest facilities of each type to the house
//Input Param:  NULL
//Return type:  NULL
void calculate_nearest_facilities(int dist[])
{
    int min[4] = {9999,9999,9999,9999};
    int index[4] = {0,0,0,0};

    int i;

    for(i=1;i<=19;i++)
    {
        if(!strcmp(temp[i].facility_type,"Hospital") && dist[i] <= min[0])
        {
            min[0] = dist[i];
            index[0] = i;
        }
        else if(!strcmp(temp[i].facility_type,"School") && dist[i] <= min[1])
        {
            min[1] = dist[i];
            index[1] = i;
        }
        else if(!strcmp(temp[i].facility_type,"College") && dist[i] <= min[2])
        {
            min[2] = dist[i];
            index[2] = i;
        }
        else if(!strcmp(temp[i].facility_type,"Park") && dist[i] <= min[3])
        {
            min[3] = dist[i];
            index[3] = i;
        }
    }
    
    printf("Nearest hospital: %s %s which is %d metres away\n",temp[index[0]].facility_name,temp[index[0]].facility_type,min[0]);
    printf("Nearest school:   %s %s which is %d metres away\n",temp[index[1]].facility_name,temp[index[1]].facility_type,min[1]);
    printf("Nearest college:  %s %s which is %d metres away\n",temp[index[2]].facility_name,temp[index[2]].facility_type,min[2]);
    printf("Nearest park:     %s %s which is %d metres away\n",temp[index[3]].facility_name,temp[index[3]].facility_type,min[3]);
}

//Function:     dijkstras()
//Description:  Finds the shortest path between house chosen and all the facilities
//Input Param:  Integer : No.of vertices, Integer : Source node
//Return type:  NULL
void array_dijkstra(int v, int src) 
{
    int i,j,k;
    int u;
    int flag = 0;
    dist[src] = 0;
    
    for(i=0;i<20;i++) {                                    
        dist[i] = distance_matrix[0][i];
        path[i] = 0;
    }

    for(i=0;i<v;i++) {
        u = -1;
        for(j=0;j<v;j++) {
            if(!visited[j] && (dist[j] < dist[u] || u == -1))
                u = j;
        }
        visited[u] = 1;
        for(k=0;k<v;k++) {
            if(!visited[k]){
                flag = minimum(dist[k], dist[u] + distance_matrix[u][k]);
                if(!flag) {
                    dist[k] = dist[u] + distance_matrix[u][k];
                    path[k] = u;
                }
            }
        }
    }
    calculate_nearest_facilities(dist);
}

/**********************************************************************/
//Function:     create_graph()
//Description:  Creates a graph on which dijkstras will be applied on
//Input Param:  An integer that holds the no. of nodes
//Return type:  struct Graph *
struct Graph* create_graph(int V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;

	// Create an arr of adjacency lists. 
	// Size of arr will be V
	graph->arr = (struct adj_list*)malloc(V * sizeof(struct adj_list));

	// Initialize each adjacency list 
	// as empty by making head as NULL
	for (int i = 0; i < V; ++i)
		graph->arr[i].head = NULL;

	return graph;
}

//Function:     new_adj_list_node
//Description:  Creates a new adjacency list node
//Input Param:  Destination node and the weight between destination and source
//Return type:  struct adj_list_node*
struct adj_list_node* new_adj_list_node(int dest, int weight)
{
	struct adj_list_node* new_node = (struct adj_list_node*)malloc(sizeof(struct adj_list_node));
	new_node->dest = dest;
	new_node->weight = weight;
	new_node->next = NULL;
	return new_node;
}

// Adds an edge to an undirected graph
//Function:     addEdge
//Description:  Adds the edges into graph 
//Input Param:  Source, Destination, Weight between them
//Return type:  NULL
void addEdge(int src, int dest, int weight)
{
	// Add an edge from src to dest. 
	// A new node is added to the adjacency
	// list of src. The node is 
	// added at the beginning
	struct adj_list_node* new_node = new_adj_list_node(dest, weight);
	new_node->next = graph->arr[src].head;
	graph->arr[src].head = new_node;
}
//Function:     insert_into_graph()
//Description:  Finds the proper weight of edges to be inserted and calls addEdge function for it
//Input Param:  NULL
//Return type:  NULL
void insert_into_graph()
{
    int i,j;
	int distaaance;

    for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		{
			if(distance_matrix[i][j] != 9999 && distance_matrix[i][j] != 0)
			{
				addEdge(i,j,distance_matrix[i][j]);
			}
		}
	}
}

//Function:     new_MinHeapNode()
//Description:  Adds a new MinHeapNode
//Input Param:  Vertex integer, Weight of edge
//Return type:  struct MinHeapNode*
struct MinHeapNode* new_MinHeapNode(int v, int dist)
{
	struct MinHeapNode* min_heap_node = (struct MinHeapNode*) 
	malloc(sizeof(struct MinHeapNode));
	min_heap_node->v = v;
	min_heap_node->dist = dist;
	return min_heap_node;
}

//Function:     create_min_heap()
//Description:  Function to create a min-heap
//Input Param:  Capacity
//Return type:  struct MinHeap*
struct MinHeap* create_min_heap(int capacity)
{
	struct MinHeap* minimum_heap = (struct MinHeap*) 
	malloc(sizeof(struct MinHeap));
	minimum_heap->pos = (int *)malloc(capacity * sizeof(int));
	minimum_heap->size = 0;
	minimum_heap->capacity = capacity;
	minimum_heap->arr = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
	return minimum_heap;
}

//Function:     swap_min_heap_node()
//Description:  Function to swap two MinHeap nodes
//Input Param:  2 MinHeapNodes a and b that are to  be swapped
//Return type:  NULL
void swap_min_heap_node(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

//Function:     minimum_heapify
//Description:  A function to heapify at given index. It also updates position of nodes when they are swapped
//Input Param:  minimum_heap, intger index
//Return type:  NULL
void minimum_heapify(struct MinHeap* minimum_heap, int index)
{
	int smallest, left, right;
	smallest = index;
	left = 2 * index + 1;
	right = 2 * index + 2;

	if (left < minimum_heap->size &&
		minimum_heap->arr[left]->dist < 
		minimum_heap->arr[smallest]->dist )
	smallest = left;

	if (right < minimum_heap->size &&
		minimum_heap->arr[right]->dist <
		minimum_heap->arr[smallest]->dist )
	smallest = right;

	if (smallest != index)
	{
		// The nodes to be swapped in min heap
		struct MinHeapNode *smallestNode; 
		struct MinHeapNode *indexNode;

		smallestNode = minimum_heap->arr[smallest];
		indexNode = minimum_heap->arr[index];

		// Swap positions
		minimum_heap->pos[smallestNode->v] = index;
		minimum_heap->pos[indexNode->v] = smallest;

		// Swap nodes
		swap_min_heap_node(&minimum_heap->arr[smallest], 
						&minimum_heap->arr[index]);

		minimum_heapify(minimum_heap, smallest);
	}
}

//Function:     isEmpty()
//Description:  Checks if minimum_heap is empty or not
//Input Param:  minimum_heap
//Return type:  Integer
int isEmpty(struct MinHeap* minimum_heap)
{
	return minimum_heap->size == 0;
}

//Function:     extract_min
//Description:  Function to extract minimum node from heap
//Input Param:  minimum_heap
//Return type:  struct MinHeapNode*
struct MinHeapNode* extract_min(struct MinHeap* minimum_heap)
{
	if (isEmpty(minimum_heap))
		return NULL;

	// Store the root node
	struct MinHeapNode* root = 
				minimum_heap->arr[0];

	// Replace root node with last node
	struct MinHeapNode* lastNode = 
		minimum_heap->arr[minimum_heap->size - 1];
	minimum_heap->arr[0] = lastNode;

	// Update position of last node
	minimum_heap->pos[root->v] = minimum_heap->size-1;
	minimum_heap->pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
	--minimum_heap->size;
	minimum_heapify(minimum_heap, 0);

	return root;
}

//Function:     decrease_key()
//Description:  Function to decrease key dist value of a given vertex v.This function 
			    //uses pos[] of min heap to get the
			    //current index of node in min heap
//Input Param:  minimum_heap, Vertex, Distance
//Return type:  NULL
void decrease_key(struct MinHeap* minimum_heap, 
						int v, int dist)
{
	// Get the index of v in heap arr
	int i = minimum_heap->pos[v];

	// Get the node and update its dist value
	minimum_heap->arr[i]->dist = dist;

	// Travel up while the complete 
	// tree is not heapified.
	// This is a O(Logn) loop
	while (i && minimum_heap->arr[i]->dist < 
		minimum_heap->arr[(i - 1) / 2]->dist)
	{
		// Swap this node with its parent
		minimum_heap->pos[minimum_heap->arr[i]->v] = 
									(i-1)/2;
		minimum_heap->pos[minimum_heap->arr[
							(i-1)/2]->v] = i;
		swap_min_heap_node(&minimum_heap->arr[i], 
				&minimum_heap->arr[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
//Function:		is_in_MinHeap()
//Description:  Function to check if a given vertex is in min heap or not
//Input Param:  minimum_heap ,vertex v
//Return type:  Bool
bool is_in_MinHeap(struct MinHeap *minimum_heap, int v)
{
	if (minimum_heap->pos[v] < minimum_heap->size)
		return true;
	return false;
}

//It is a O(ELogV) function
//Function:     heap_dijkstra()
//Description:  Calculates the distances of shortest paths from source to all other nodes
//Input Param:  Source node integer
//Return type:  NULL
void heap_dijkstra(int src)
{
	
	// Get the number of vertices in graph
	int V = graph->V;

	// dist values used to pick
	// minimum weight edge in cut
	int dist[V];	 

	// minimum_heap represents set E
	struct MinHeap* minimum_heap = create_min_heap(V);

	// Initialize min heap with all 
	// vertices. dist value of all vertices 
	for (int v = 0; v < V; ++v)
	{
		dist[v] = INT_MAX;
		minimum_heap->arr[v] = new_MinHeapNode(v, dist[v]);
		minimum_heap->pos[v] = v;
	}

	// Make dist value of src vertex 
	// as 0 so that it is extracted first
	minimum_heap->arr[src] = new_MinHeapNode(src, dist[src]);
	minimum_heap->pos[src] = src;
	dist[src] = 0;
	decrease_key(minimum_heap, src, dist[src]);

	// Initially size of min heap is equal to V
	minimum_heap->size = V;

	// In the following loop, 
	// min heap contains all nodes
	// whose shortest distance 
	// is not yet finalized.
	while (!isEmpty(minimum_heap))
	{
		// Extract the vertex with 
		// minimum distance value
		struct MinHeapNode* min_heap_node = extract_min(minimum_heap);
	
		// Store the extracted vertex number
		int u = min_heap_node->v; 

		// Traverse through all adjacent 
		// vertices of u (the extracted
		// vertex) and update 
		// their distance values
		struct adj_list_node* crawler = graph->arr[u].head;
		while (crawler != NULL)
		{
			int v = crawler->dest;

			// If shortest distance to v is
			// not finalized yet, and distance to v
			// through u is less than its 
			// previously calculated distance
			if (is_in_MinHeap(minimum_heap, v) && dist[u] != INT_MAX && crawler->weight + dist[u] < dist[v])
			{
				dist[v] = dist[u] + crawler->weight;

				// update distance 
				// value in min heap also
				decrease_key(minimum_heap, v, dist[v]);
			}
			crawler = crawler->next;
		}
	}
    calculate_nearest_facilities(dist);
}
