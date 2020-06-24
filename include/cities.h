#ifndef CITIES_H_ /* INCLUDE GUARD */
#define CITIES_H_

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAXCOLUMNS 11
#define MAXCOLUMNS2 5
#define MALLOC(X) (X *)malloc(sizeof(X))

// Structure for the List of Incidences
typedef struct _incidenceList
{
    int idDestination;
    float weight;
    char *cityDestination;
    struct _incidenceList *next;
} IncidenceList;

// Structure for the Graph nodes
typedef struct _graph
{
    int idKey;
    int population;
    char *city;
    char *country;
    int counter;
    IncidenceList *incidences;
    struct _graph *left, *right;
} Graph;

// Dijkstra's data record
typedef struct _auxRecord
{
    int node;
    int connection;
    float costSoFar;
    struct _auxRecord *next_rec;
} AuxRecord;

// Dijkstra's path struct
typedef struct _edgeList
{
    int target;
    struct _edgeList *next_edge;
} EdgeList;

/*****************************************************************************************
 * PROCEDURES TO SEARCH VALUES
*****************************************************************************************/

/**
 * Function: Graph binary tree search by key
 * @root: Receives the pointer to the root of the tree
 * @idKey: receives the IDkey
 * Returns: Pointer to the root of the btree or NULL
*/
Graph *graph_btree_search(Graph *root, int idKey);

/**
 * Function: Incidence list search by ID
 * @list: Receives the pointer to the head of the list
 * @target: Receives the target ID
*/
IncidenceList *incidence_list_search(IncidenceList *list, int target);

/*****************************************************************************************
 * PROCEDURES TO ADD/INSERT VALUES
*****************************************************************************************/

/**
 * Function: Graph edge inserton
 * @root: Receives the root of the btree
 * @idKey: Receives the ID of the city, used as a key value
 * @idDestination: receives the destination ID
 * @weight: Receives the edge weight
 * @cityDestination: Receives the name of the destination city
 * Returns: Pointer to the btree root
*/
Graph *graph_add_edge(Graph *root, int idKey, int idDestination, float weight, char *cityDestination);

/**
 * Function: Nested List inserton for a Graph as a set of edges
 * @root: Receives the root of the btree
 * @lst: Receives the pointer to the head of the list
 * @idDestination: receives the destination ID
 * @weight: Receives the edge weight
 * @cityDestination: Receives the name of the destination city
 * Returns: Pointer to the list head
*/
IncidenceList *incidence_insert(Graph *root, IncidenceList *lst, int idDestination, float weight, char *cityDestination);

/**
 * Function: Binary tree inserton for a Graph as a set of nodes
 * @root: Receives the root of the btree
 * @idKey: Receives the ID of the city, used as a key value
 * @population: receives the city population
 * @city: Receives the city´s name
 * @country: Receives the country´s name where the city belongs
 * @incidences: Receives the incidence list of the city´s ID
 * Returns: Pointer to the btree root
*/
Graph *graph_btree_insert(Graph *root, int idKey, int population, char *city, char *country, IncidenceList *incidences);

/*****************************************************************************************
 * FREE MEMORY
*****************************************************************************************/

/**
 * Procedure: Free both Graph btree and IncidenceList
 * @root: Receives the pointer to the root of the btree
*/
void graph_btree_free(Graph *root);

/**
 * Procedure: Free IncidenceList
 * @list: Receives the pointer to the head of the list
*/
void incidence_list_free(IncidenceList *list);

/*****************************************************************************************
 * READ/WRITE FILES
*****************************************************************************************/

/**
 * Function: Read and store data from the worldcities file to the Graph set of nodes
 * @fileName: Receives the name of the file to read
 * Returns: Pointer to the root of the btree
*/
Graph *read_graph_file(char *fileName);

/**
 * Function: Read and store data from the iberia-interrail or cidadesPT files to the Graph set of edges
 * @root: Receives the pointer to the root of the btree
 * @fileName: Receives the name of the file to read
 * Returns: Pointer to the root of the btree
*/
Graph *read_edges_file(Graph *root, char *fileName);

/*****************************************************************************************
 * DIJKSTRA's ALGORITHM
*****************************************************************************************/
/**
 * Function: Create a new record
 * @rec: Receives the id of the record
 * returns: Pointer to the node
 */
AuxRecord *new_aux_record(int o);

/**
 * Function: Insert Incidence 
 * @lst: receives the pointer to the head of the list
 * @target: receives the target ID
 * returns: Pointer to the head of the list
 */
EdgeList *insert_incidence(EdgeList *lst, int target);

/**
 * Function: Sorted record insert
 * @lst: receives the pointer to the head of the list
 * @node: receives the pointer to the new node
 * returns: Pointer to the head of the list
 */
AuxRecord *aux_rec_sorted_insert(AuxRecord *lst, AuxRecord *node);

/**
 * Function: Record remove
 * @lst: receives the pointer to the head of the list
 * @node: receives the ID of the node to remove
 * returns: Pointer to the head of the list
 */
AuxRecord *aux_rec_remove(AuxRecord *lst, int id);

/**
 * Function: Record search by ID
 * @lst: receives the pointer to the head of the list
 * @node: receives the ID of the node to search
 * returns: Pointer to the head of the list
 */
AuxRecord *aux_rec_search_id(AuxRecord *lst, int id);

/**
 * Procedure: Free memory of the record's list
 * @lst: receives the pointer to the head of the list
 */
void aux_rec_list_free(AuxRecord *lst);

/**
 * Function: Get cost between the current ID and the destination ID
 * @g: receives the pointer to the graph
 * @current: receives the current ID
 * @destination: receives the destination ID
 * returns: Cost between the two ID's
 */
float get_cost(Graph *g, int current, int destination);

/**
 * Function: Get the shortest path between two ID's - Dijkstra algorithm
 * @g: receives the pointer to the graph
 * @origin: receives the origin ID
 * @target: receives the target ID
 * returns: Path between two ID's or NULL
 */
EdgeList *path_find(Graph *g, int origin, int target);
#endif /* CITIES_H_ */