#include "cities.h"

/**
 * @author Eduardo Oliveira; Carlos Daniel;
 * @email eduardo.oliveira@ieee.org; carlosdanielmiranda99@gmail.com;
 * @create date 06-05-2020 19:59:00
 * @modify date 05-06-2020 19:59:00
 * @desc Dijkstra path find example
 * @version 0.0.2
 */

/*****************************************************************************************
 * PROCEDURES TO SEARCH VALUES
*****************************************************************************************/

/**
 * Function: Graph binary tree search by key
 * @root: Receives the pointer to the root of the tree
 * @idKey: receives the IDkey
 * Returns: Pointer to the root of the btree or NULL
*/
Graph *graph_btree_search(Graph *root, int idKey)
{
    if (root)
    {
        if (idKey < root->idKey)
            return graph_btree_search(root->left, idKey);
        else if (idKey > root->idKey)
            return graph_btree_search(root->right, idKey);
        else
            return root;
    }
    else
        return NULL;
}

/**
 * Function: Incidence list search by ID
 * @list: Receives the pointer to the head of the list
 * @target: Receives the target ID
*/
IncidenceList *incidence_list_search(IncidenceList *list, int target)
{
    if (list)
    {
        IncidenceList *aux;
        // Free data
        for (aux = list; aux; aux = aux->next)
            if (aux->idDestination == target)
                break;

        if (aux->idDestination == target)
            return aux;
    }
    return NULL;
}

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
Graph *graph_add_edge(Graph *root, int idKey, int idDestination, float weight, char *cityDestination)
{
    Graph *origin_node = graph_btree_search(root, idKey);

    if (origin_node)
    {
        IncidenceList *new = incidence_insert(origin_node, origin_node->incidences, idDestination, weight, cityDestination);
        origin_node->incidences = new;
    }

    return root;
}

/**
 * Function: Nested List inserton for a Graph as a set of edges
 * @root: Receives the root of the btree
 * @lst: Receives the pointer to the head of the list
 * @idDestination: receives the destination ID
 * @weight: Receives the edge weight
 * @cityDestination: Receives the name of the destination city
 * Returns: Pointer to the list head
*/
IncidenceList *incidence_insert(Graph *root, IncidenceList *lst, int idDestination, float weight, char *cityDestination)
{
    if (lst && (lst->idDestination == idDestination))
    {
        if (lst->weight > weight)
            lst->weight = weight;
        return lst;
    }
    else
    {
        if (!lst)
        {
            IncidenceList *aux = MALLOC(IncidenceList);

            // Verify memory alloc
            if (!aux)
            {
                fprintf(stderr, "Memory alloc error! \nPress any key...");
                getchar();
                exit(1);
            }

            aux->cityDestination = strdup(cityDestination);
            aux->idDestination = idDestination;
            aux->weight = weight;
            aux->next = NULL;
            root->counter++;
            return aux;
        }
        else
        {
            lst->next = incidence_insert(root, lst->next, idDestination, weight, cityDestination);
            return lst;
        }
    }
}

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
Graph *graph_btree_insert(Graph *root, int idKey, int population, char *city, char *country, IncidenceList *incidences)
{
    if (root)
    {
        if (idKey < root->idKey)
            root->left = graph_btree_insert(root->left, idKey, population, city, country, incidences);
        if (idKey > root->idKey)
            root->right = graph_btree_insert(root->right, idKey, population, city, country, incidences);
    }
    else
    {
        root = MALLOC(Graph);
        // Verify memory alloc
        if (!root)
        {
            fprintf(stderr, "Memory alloc error! \nPress any key...");
            getchar();
            exit(1);
        }
        root->idKey = idKey;
        root->population = population;
        root->city = strdup(city);
        root->country = strdup(country);
        root->incidences = incidences;
        root->counter = 0;
        root->left = root->right = NULL;
    }
    return root;
}

/*****************************************************************************************
 * FREE MEMORY
*****************************************************************************************/

/**
 * Procedure: Free both Graph btree and IncidenceList
 * @root: Receives the pointer to the root of the btree
*/
void graph_btree_free(Graph *root)
{
    if (root)
    {
        graph_btree_free(root->left);
        graph_btree_free(root->right);

        // Free data
        free(root->city);
        free(root->country);
        incidence_list_free(root->incidences);
        free(root);
    }
}

/**
 * Procedure: Free IncidenceList
 * @list: Receives the pointer to the head of the list
*/
void incidence_list_free(IncidenceList *list)
{
    if (list)
    {
        IncidenceList *aux;
        // Free data
        for (; list; list = aux)
        {
            aux = list->next;
            free(list->cityDestination);
            free(list);
        }
    }
}

/*****************************************************************************************
 * READ/WRITE FILES
*****************************************************************************************/

/**
 * Function: Read and store data from the worldcities file to the Graph set of nodes
 * @fileName: Receives the name of the file to read
 * Returns: Pointer to the root of the btree
*/
Graph *read_graph_file(char *fileName)
{
    // Declarations
    Graph *root = NULL;
    FILE *file = NULL;

    // Local variables
    char line[512];

    // Open the textfile
    file = fopen(fileName, "r");

    // Verify if there's a file, if not, print error and exit
    if (!file)
    {
        fprintf(stderr, "Error - File %s not found!\nPress any key...", fileName);
        getchar();
        exit(1);
    }

    // Place the pointer at the start of the file
    rewind(file);

    // Read and discard the first line
    fgets(line, 512, file);

    // Get line data from file and insert it on the btree.
    while (!feof(file))
    {
        // Read the current line
        fgets(line, 512, file);

        // Check if !end-of-file
        if (!feof(file))
        {
            // Local variables
            char *token[MAXCOLUMNS];

            // Remove the '\n'
            line[strlen(line) - 1] = '\0';

            char *tmp = strdup(line);

            // Tokenize the columns
            int col = 0;
            while (tmp)
            {
                if (col == MAXCOLUMNS)
                {
                    fprintf(stderr, "Wrong file format");
                    getchar();
                    exit(1);
                }
                token[col] = strsep(&tmp, ",");
                col++;
            }

            // Insert data on the binary tree, by idKey
            root = graph_btree_insert(root, atoi(token[10]), atoi(token[9]), token[0], token[4], NULL);

            free(*token);
        }
    }

    // Close the file
    fclose(file);

    // Return the pointer to the root of the btree
    return root;
}

/**
 * Function: Read and store data from the iberia-interrail or cidadesPT files to the Graph set of edges
 * @root: Receives the pointer to the root of the btree
 * @fileName: Receives the name of the file to read
 * Returns: Pointer to the root of the btree
*/
Graph *read_edges_file(Graph *root, char *fileName)
{
    // Declarations
    FILE *file = NULL;

    // Local variables
    char line[512];

    // Open the textfile
    file = fopen(fileName, "r");

    // Verify if there's a file, if not, print error and exit
    if (!file)
    {
        fprintf(stderr, "Error - File %s not found!\nPress any key...", fileName);
        getchar();
        exit(1);
    }

    // Place the pointer at the start of the file
    rewind(file);

    // Get line data from file and insert it by key comparison on the graph edge.
    while (!feof(file))
    {
        // Read the current line
        fgets(line, 256, file);

        // Check if !end-of-file
        if (!feof(file))
        {
            // Local variables
            char *token[MAXCOLUMNS2];

            // Remove the '\n'
            line[strlen(line) - 1] = '\0';

            char *tmp = strdup(line);

            // Tokenize the columns
            int col = 0;
            while (tmp)
            {
                if (col == MAXCOLUMNS)
                {
                    fprintf(stderr, "Wrong file format");
                    getchar();
                    exit(1);
                }
                token[col] = strsep(&tmp, ",");
                col++;
            }

            // Insert edges on the binary tree, by idKey comparison
            root = graph_add_edge(root, atoi(token[0]), atoi(token[2]), atof(token[4]), token[3]);

            free(*token);
        }
    }

    // Close the file
    fclose(file);

    // Return the pointer to the root of the btree
    return root;
}

/*****************************************************************************************
 * DIJKSTRA's ALGORITHM
*****************************************************************************************/
/**
 * Function: Create a new record
 * @rec: Receives the id of the record
 * returns: Pointer to the node
 */
AuxRecord *new_aux_record(int rec)
{
    AuxRecord *new = MALLOC(AuxRecord);
    new->node = rec;
    new->connection = 0;
    new->costSoFar = 0.0f;
    new->next_rec = NULL;
    return new;
}

/**
 * Function: Insert Incidence 
 * @lst: receives the pointer to the head of the list
 * @target: receives the target ID
 * returns: Pointer to the head of the list
 */
EdgeList *insert_incidence(EdgeList *lst, int target)
{
    EdgeList *new = MALLOC(EdgeList);
    new->target = target;
    new->next_edge = lst;
    return new;
}

/**
 * Function: Sorted record insert
 * @lst: receives the pointer to the head of the list
 * @node: receives the pointer to the new node
 * returns: Pointer to the head of the list
 */
AuxRecord *aux_rec_sorted_insert(AuxRecord *lst, AuxRecord *node)
{
    if (!lst)
        lst = node;
    else if (lst->costSoFar > node->costSoFar)
    {
        node->next_rec = lst;
        lst = node;
    }
    else
    {
        lst->next_rec = aux_rec_sorted_insert(lst->next_rec, node);
    }
    return lst;
}

/**
 * Function: Record remove
 * @lst: receives the pointer to the head of the list
 * @node: receives the ID of the node to remove
 * returns: Pointer to the head of the list
 */
AuxRecord *aux_rec_remove(AuxRecord *lst, int id)
{
    if (lst && lst->node == id)
    {
        lst = lst->next_rec;
    }
    else if (lst)
    {
        lst->next_rec = aux_rec_remove(lst->next_rec, id);
    }
    else
        return lst;
}

/**
 * Function: Record search by ID
 * @lst: receives the pointer to the head of the list
 * @node: receives the ID of the node to search
 * returns: Pointer to the head of the list
 */
AuxRecord *aux_rec_search_id(AuxRecord *lst, int id)
{
    if (lst && lst->node == id)
        return lst;
    else if (lst)
        return aux_rec_search_id(lst->next_rec, id);
    else
        return NULL;
}

/**
 * Procedure: Free memory of the record's list
 * @lst: receives the pointer to the head of the list
 */
void aux_rec_list_free(AuxRecord *lst)
{
    if (lst)
    {
        aux_rec_list_free(lst->next_rec);
        free(lst);
    }
}

/**
 * Function: Get cost between the current ID and the destination ID
 * @g: receives the pointer to the graph
 * @current: receives the current ID
 * @destination: receives the destination ID
 * returns: Cost between the two ID's
 */
float get_cost(Graph *g, int current, int destination)
{
    if (g)
    {
        Graph *aux = graph_btree_search(g, current);
        IncidenceList *dest = incidence_list_search(aux->incidences, destination);
        return dest ? dest->weight : 0;
    }
    else
        return 0;
}

/**
 * Function: Get the shortest path between two ID's - Dijkstra algorithm
 * @g: receives the pointer to the graph
 * @origin: receives the origin ID
 * @target: receives the target ID
 * returns: Path between two ID's or NULL
 */
EdgeList *path_find(Graph *g, int origin, int target)
{
    EdgeList *path = NULL;
    AuxRecord *current = NULL;

    AuxRecord *open = new_aux_record(origin);
    AuxRecord *closed = NULL;

    while (open)
    {
        current = open;
        open = open->next_rec;
        current->next_rec = NULL;

        if (current->node == target)
            break;

        Graph *current_node = graph_btree_search(g, current->node);
        IncidenceList *neighbours = current_node ? current_node->incidences : NULL;

        for (; neighbours; neighbours = neighbours->next)
        {
            int need_to_remove_from_open = 0;
            int destination = neighbours->idDestination;
            AuxRecord *destinationRecord = NULL;
            float costSoFar = current->costSoFar + get_cost(g, current->node, destination);

            if (aux_rec_search_id(closed, destination))
                continue;

            destinationRecord = aux_rec_search_id(open, destination);
            if (destinationRecord)
            {
                if (costSoFar >= destinationRecord->costSoFar)
                    continue;
                need_to_remove_from_open = 1;
                destinationRecord->next_rec = NULL;
            }
            else
            {
                destinationRecord = new_aux_record(destination);
            }

            destinationRecord->costSoFar = costSoFar;
            destinationRecord->connection = current->node;

            if (need_to_remove_from_open)
            {
                open = aux_rec_remove(open, destination);
            }
            open = aux_rec_sorted_insert(open, destinationRecord);
        }
        closed = aux_rec_sorted_insert(closed, current);
    }

    if (current->node == target)
    {
        while (current->node != origin)
        {
            path = insert_incidence(path, current->node);
            current = aux_rec_search_id(closed, current->connection);
        }
        path = insert_incidence(path, current->node);
    }

    aux_rec_list_free(closed);
    aux_rec_list_free(open);

    return path;
}