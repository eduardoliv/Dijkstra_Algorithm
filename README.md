# Dijkstra path find algorithm example in C Language
Example of a C program that returns the shortest path between two cities.

## Usage
* Open Linux terminal, navigate to the application folder and run ./Interrail \<file1\> \<file2\>
    * \<file1\> Is the first file specified below. (You can use the worldcities.csv file, included here!) 
    * \<file2\> Is the second file specified below. (You can use the cidadesPT.txt file, included here!)
* You can create your own paths, for example, with the two files provided, you can edit cidadesPT.txt and create a simple route to test, with a short path.

## File format
* This program requires two files (.txt, .csv, ...)
    * The first file must contain 11 columns, separated by comma (without spaces). Columns are: "city,city_ascii,lat,lng,country,iso2,iso3,admin_name,capital,population,id" and must provide information about the cities. (You can use the worldcities.csv file, included here!)
    * The second file must provide the connections between cities, each city ID and the distance/cost. Must contain 5 columns, separated by comma (without spaces). "ID_origin,city_origin,ID_destination,city_destination,distance_km". (You can use the cidadesPT.txt file, included here!)

## Compilation
* Compile via Linux make command
    * Use \<make\> to create the executable
    * Use \<make clean\> to clean the objects folder

## Release History
* 0.0.2
    * Added makefile
    * Create README.md
 
## Meta
> Eduardo Oliveira - eduardo.oliveira@ieee.org; 
> Carlos Daniel - carlosdanielmiranda99@gmail.com;
