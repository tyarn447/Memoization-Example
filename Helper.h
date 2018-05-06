#ifndef INCLUDED_HELPER
#define INCLUDED_HELPER
#include <iostream>
#include <fstream>
using namespace std;

//PRE:ifstream is an input file that is gotten from the cmd line and
//holds information about each rental post, matrix is the matrix that
//all of this information will be held in. numRentals is the number of
//rental posts
//POST:creates a matrix where matrix[i][j] holds the cost it takes to
//rent a canoe from post i to post j.
void readInput(ifstream & inFile, int ** matrix, int numRentals);

//PRE:matrix is a 2d array, numRentals is the number that represents
//both number of rows and number of columns in matrix
//POST:prints the matrix
void printMatrix(int ** matrix, int numRentals);

//PRE:rentalMatrix represents the costs of getting from each rental
//post to another, cheapArray represents the cheapest cost of getting
//from one rental post to another, numRentals represents how many
//rental posts there are.
//POST:fills the cheap array with the cheapest cost of getting to
//rental post i to j when i < j.
void findOptimalRoute(int ** rentalMatrix,int ** cheapArray, int numRentals);

//PRE:column and row represent the optimal route cost we are trying to
//find from column to row, column must always be larger than or equal
//to row,rental matrix is the matrix where the cost
//to get from rental post i-j is held and cheapMatrix is the place
//where the optimal cost of getting from post i-j will be held.
//POST:puts the optimal cost of getting from i-j in cheapMatrix
void optimalRoute(int column, int row, int ** rentalMatrix, int ** cheapMatrix);

//PRE:from is the canoe rental place that you are looking for the best
//route to get to dest from, rentalMatrix and cheap Matrix are 2d matrixes
//POST:outputs to the terminal the minimum cost to go from
//from to dest as well as the route it took to get there.
void outPut(int from, int dest, int ** rentalMatrix, int ** cheapMatrix);


#endif
