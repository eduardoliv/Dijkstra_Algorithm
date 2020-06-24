#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "common.h"
#include "cities.h"

/**
 * @author Eduardo Oliveira; Carlos Daniel;
 * @email eduardo.oliveira@ieee.org; carlosdanielmiranda99@gmail.com;
 * @create date 06-05-2020 19:59:00
 * @modify date 05-06-2020 22:10:00
 * @desc Dijkstra Algorithm example
 * @version 0.0.2
 */

/**
 * Procedure: Path find between two given city ID's
 * @g: Receives the pointer to the root of the graph
*/
void find_path(Graph *root)
{
    // Clean console
    cls();

    // Local variables
    int originCity, destinationCity;

    // Presentation
    puts("");
    puts("\t ---------------------------------------- WORLD INTERRAIL ------------------------------------------");
    puts("\t|                                                                                                   |");
    puts("\t|        BUILD ITINERARY BETWEEN TWO CITIES                                                         |");
    puts("\t|                                                                                                   |");
    puts("\t ---------------------------------------------------------------------------------------------------");
    puts("");

    // Get the ID of the city
    printf("\t Insert the ID of the origin city >>: ");
    scanf("%d", &originCity);

    // Get the ID of the city
    printf("\t Insert the ID of the destination city >>: ");
    scanf("%d", &destinationCity);

    // Clean stdin
    cleanStdin();

    EdgeList *path = path_find(root, originCity, destinationCity);

    if (path)
        while (path)
        {
            Graph *g = graph_btree_search(root, path->target);
            printf("\t ID: %11d | city: %75.75s\n", path->target, g->city);
            path = path->next_edge;
        }
    else
        printf("No path\n");

    puts("\t > Press Enter to continue...");
    getchar();
}

/**
 * Main
 * @*argv[1]: Receives the worldcities.csv file as argument by command line
 * @*argv[2]: Receives the cityConnections.txt as argument by command line
*/
int main(int argc, char *argv[])
{
    // Local Variables
    unsigned int optn;
    bool exit = false;
    Graph *root = NULL;

    // Read data from files
    root = read_graph_file(argv[1]);
    root = read_edges_file(root, argv[2]);

    // Menu and subroutine selection
    while (!exit)
    {
        // Clean console
        cls();

        // Variable initialization - "Guard" for the character inputs
        optn = 999;

        // Print the principal menu
        puts("");
        puts("\t ---------------------------------------- WORLD INTERRAIL ------------------------------------------");
        puts("\t|                                                                                                   |");
        puts("\t|     1. BUILD ITINERARY BETWEEN TWO CITIES - DIJKSTRA                                              |");
        puts("\t|     0. EXIT                                                                                       |");
        puts("\t|                                                                                                   |");
        puts("\t ---------------------------------------------------------------------------------------------------");
        puts("");

        // Ask the user to choose prom the menu
        printf("\t >>> Insert the option: ");
        scanf("%u", &optn);

        // Clean the buffer from the keyboard
        cleanStdin();

        // Choose the pretended subroutine
        switch (optn)
        {
        case 1:
            cls();
            find_path(root);
            break;
        case 0:
            exit = true;
            break;
        default:
            puts("\t >x Invalid Option!\n\t You may choose the option available from the menu...\n\t Press Enter to continue...");
            getchar();
            break;
        }
    }

    // Memory free
    graph_btree_free(root);

    puts("\t > Press Enter to continue...");
    getchar();

    // Close Console
    return 0;
}