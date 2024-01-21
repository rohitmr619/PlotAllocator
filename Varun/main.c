#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"functions.c"

int main()
{
    //Integer declared to manage loops in main()
    int i;
/*----------------------1.Shortest Path----------------------*/
    //Reads facilty data into array of structures
    facility_pointer = fopen("facilities1.txt","r+");
    read_facilities();         
    fseek(facility_pointer,0,0);                        

    //Populates road-connection matrix
    populate_connection_matrix();

    //Populates cost matrix
    populate_distance_matrix();                             

    //Displays road-connection matrix
    //display_connection_matrix();    

    //Displays cost matrix
    //display_distance_matrix();                              

    /*dijkstras() function called
    First parameter is the no. of vertices or nodes
    Second parameter is source which is 0 in this case*/
    array_dijkstra(20,0);     
/*-----------------------------------------------------------*/

/*----------------------V----------------------*/                                   
}
