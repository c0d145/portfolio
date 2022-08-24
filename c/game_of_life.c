/*
* Conway's Game of Life
* ---------------------
*
* parameters from command line:
* 1. number of fields
* 2. number of generations
* 3. delay in milliseconds
*
* living cells = *
* refresh all cells "at once".
* All edges are neighbours of each other. Modulo operation to realize geometry.
*
* RULES (through function "examinator"):
* (1) A cell comes to life when exactly three of its eight neighbours are alive.
* (2) A cell dies when only one (isolation) or more then three (overpopulation) of its eight neighbours are alive
* (3) Otherwise unchanged.
*
* Compiling on console with:
* gcc -Wall -c game_of_life.c
* gcc -o game_of_life game_of_life.o
*
* Author: c0d145
* Created: 	2009-??-??
* Modified:	2022-08-22: Reworked the comments, typo correction and recompile as I wasn't sure if it was the final version.
*/

/*
* Memory initialization ahead of program start.
*/
#define allocate_playing_field(type, var, x, y) {                   \
	(var) = calloc(x, sizeof(type **));                       \
									\
	if ((var) == NULL) {                                         \
		perror("Error while allocating memory.\n");                    \
	}                                                            \
								\
	int ii;                                                    \
	for (ii = 0; ii < x; ii++) {                                    \
		(var)[ii] = calloc(x, sizeof(type*));                  \
		if ((var)[ii] == NULL) {                                  \
			perror("Error while allocating memory.\n");                \
		}                                                        \
                                              \
	}                                                            \
}								\

#define allocate_playing_field_dub(type, var, x2, y2) {                   \
	(var) = calloc(x2, sizeof(type **));                       \
									\
	if ((var) == NULL) {                                         \
		perror("Error while allocating memory.\n");                    \
	}                                                            \
								\
	int iii;                                                    \
	for (iii = 0; iii < x2; iii++) {                                    \
		(var)[iii] = calloc(x2, sizeof(type*));                  \
		if ((var)[iii] == NULL) {                                  \
			perror("Error while allocating memory.\n");                \
		}                                                        \
                                              \
	}                                                            \
}								\



#include <stdio.h>
// Needed for memory allocation.
#include <stdlib.h> 
// Contains memcopy.
#include <string.h>

// Prototypes of functions.
int examinator(int alive, int status_old);
int count(int currentrow, int currentcolumn, int field_size, int **playing_field);
int neighbours(int positionX, int positionY, int field_size, int **playing_field);
void output_field(int delay, int field_size, int **playing_field2);
void output_numbers(int delay, int field_size, int **playing_field2);
void initialize_startfield (char form, int **playing_field, int field_size);
//void playing_field_reset(int field_size, int playing_field[][field_size], int playing_field2[][field_size]);


int
main (int argc, char *argv[]) 
{
	// Read the size of the field from program parameters.
	int field_size = atoi(argv[1]); 		
	// Read the number of generations from program parameters.
	int generations = atoi(argv[2]);
	// Read display time in milliseconds Anzeigezeit in Millisekunden.
	int latency = atoi(argv[3]);

	int i = 0;
	int j = 0;
	int k = 0;

	// Memory allocation for the playing_field.
	int **playing_field;
	allocate_playing_field(int, playing_field, field_size, field_size);

	// Memory allocation for the updated playing_field.
	int **playing_field2;
	allocate_playing_field_dub(int, playing_field2, field_size, field_size);
	initialize_startfield('g', playing_field, field_size);

	// Output of the start-state of the playing field.
	printf("---Initial playing field---\n");
	output_field(latency, field_size, playing_field);

	// This loop calculates through the current generation.
	for(i=0; i<generations; i++) { 
	printf("-- Generation %d --\n", i+1);
		// Iteration over lines.
		for(k=0; k<field_size; k++) {
			// Iteration over columns.
			for(j=0; j<field_size; j++) {
				//printf(" %d,", k);
				//printf(" %d \n", j);
				playing_field2[k][j] = neighbours(k,j,field_size,playing_field);
			}

		}
		output_field(latency, field_size, playing_field2);
	
	// Write updated playing playing_field in the old array.
		// Iteration over lines.
		for(k=0; k<field_size; k++) {
			// Iteration over columns.
			for(j=0; j<field_size; j++) {
				playing_field[k][j] = playing_field2[k][j]; 
			}
		}
	}
}


/*
* Function that returns the new status of a field / implements / checks the rules.
*/
int
examinator (int alive, int status_old)
{
	int status;
	switch(alive)
	{
		// Set cell alive.
		case 3: status=1; break; 			
		// Cell unchanged.
		case 2: status=status_old; break;
		// Kill cell.
		default: status=0; break;
	}
//	printf("%d",lebend);
	return status;
}

/*
* Counts the neighbours of a cell with given x and y postion and field size. 
* The result will then be passed to the examinator function.
*/
int
neighbours (int positionX, int positionY, int field_size, int **playing_field)
{
	int topCenter = playing_field[positionX][((positionY + field_size+1) % field_size)];
	int topLeft = playing_field[((positionX + field_size-1) % field_size)][((positionY + field_size+1) % field_size)];
	int topRight = playing_field[((positionX + field_size+1) % field_size)][((positionY + field_size+1) % field_size)];
	int centermiddle = playing_field[positionX][positionY];
	int centerLeft = playing_field[((positionX + field_size-1) % field_size)][positionY];
	int centerRight = playing_field[((positionX + field_size+1) % field_size)][positionY];
	int bottommiddle = playing_field[positionX][((positionY + field_size-1) % field_size)];
	int bottomRight = playing_field[((positionX + field_size+1) % field_size)][((positionY + field_size-1) % field_size)];
	int bottomLeft = playing_field[((positionX + field_size-1) % field_size)][((positionY + field_size-1) % field_size)];

	int livingCells = topCenter + topLeft + topRight + centerLeft + centerRight + bottommiddle + bottomRight + bottomLeft;
	//printf(" %d,", livingCells);

	return examinator(livingCells, centermiddle);
}


/*
* Prints the playing_field on the console.
*/
void
output_field(int delay, int field_size, int **playing_field2)
{
	int k,j;
	// Iteration over lines.
	for(k=0; k<field_size; k++) {	
		// Iteration over columns.
		for(j=0; j<field_size; j++) {
	//		printf(" %d,", k);
	//		printf(" %d \n", j);
			if (playing_field2[k][j] == 1) { printf("*"); } else { printf(" "); }
		}
		printf("\n");
	}
	sleep(1*delay/1000);
}



/*
* Prints the playing_field as digits on the console.
*/
void
output_numbers(int delay, int field_size, int **playing_field2)
{
	int k,j;
	// Iteration over lines.
	for(k=0; k<field_size; k++) {
		// Iteration over columns.
		for(j=0; j<field_size; j++) {
			printf(" %d,", playing_field2[k][j]);
		}
		printf("\n");
	}
	sleep(1*delay/1000);

}

/*
* Sets classic start configuartions.
*/
void
initialize_startfield(char form, int **playing_field, int field_size) 
{
	if (form == 'g') {
		// 'Glider' as start configuration.
		playing_field[0][1] = 1;
		playing_field[1][2] = 1;
		playing_field[2][0] = 1;
		playing_field[2][1] = 1;
		playing_field[2][2] = 1;
	} else if (form == 'e' ) {
		// Living cells at the edges as start configuarion.
		playing_field[0][0] = 1;
		playing_field[field_size-1][0] = 1;
		playing_field[0][field_size-1] = 1;
		playing_field[field_size-1][field_size-1] = 1;
	} else if (form == 'p') {
		// Pi as start configuarion.
		playing_field[0][0] = 1;
		playing_field[0][1] = 1;
		playing_field[0][2] = 1;
		playing_field[1][0] = 1;
		playing_field[1][2] = 1;	
		playing_field[2][1] = 1;
	}
}
