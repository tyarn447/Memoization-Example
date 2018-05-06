#include "Helper.h"
#include<iostream>
#include<fstream>
#include "LinkedList.h"
using namespace std;
//PRE:ifstream is an input file that is gotten from the cmd line and
//holds information about each rental post, matrix is the matrix that
//all of this information will be held in. numRentals is the number of
//rental posts
//POST:creates a matrix where matrix[i][j] holds the cost it takes to
//rent a canoe from post i to post j.
void readInput(ifstream & inFile, int ** matrix, int numRentals){
  while(!inFile.eof()){
    //ASSERT:we are not at the end of the input file
    int index1;
    int index2;
    int cost;
    inFile >> index1;
    inFile >> index2;
    inFile >> cost;
    matrix[index1][index2] = cost;
    matrix[index2][index1] = cost;
  }
  //done filling up everything but diagonal
  //fill up diagonal
  for(int index = 0; index < numRentals; index ++){
    matrix[index][index] = 0;
  }
  //done creating matrix;
}

//PRE:matrix is a 2d array, numRentals is the number that represents
//both number of rows and number of columns in matrix
//POST:prints the matrix
void printMatrix(int ** matrix, int numRentals){
  for(int index1 = 0; index1 < numRentals; index1 ++){
   
    for(int index2 = 0; index2 < numRentals; index2 ++){
      cout << matrix[index1][index2] << " ";
      
    }
    cout << endl;
  }
  
}


//PRE:rentalMatrix represents the costs of getting from each rental
//post to another, cheapMatrix represents the cheapest cost of getting
//from one rental post to another, numRentals represents how many
//rental posts there are.
//POST:fills the cheap array with the cheapest cost of getting to
//rental post i to j when i < j.
void findOptimalRoute(int ** rentalMatrix,int ** cheapMatrix, int numRentals){
  //to fill in, fill in where they differ by 1, then where they differ by 2, then by 3 ect,
  //when they start differing by  more than 1 you have to define a function to return the minimum of your
  //recurrence relation that you stated.
  int difference = 0;// variable helps fill in the diagonals of cheapMatrix
  while(difference != numRentals){
    int farDown = numRentals - difference;
    for(int index = 0; index < farDown; index ++){
      int column = index + difference;
      int row = index;
      optimalRoute(column,row,rentalMatrix,cheapMatrix);
    }
    difference ++;
  }
}

//PRE:column and row represent the optimal route cost we are trying to
//find from column to row, column must always be larger than or equal
//to row,rental matrix is the matrix where the cost
//to get from rental post i-j is held and cheapMatrix is the place
//where the optimal cost of getting from post i-j will be held.
//POST:puts the optimal cost of getting from i-j in cheapMatrix
void optimalRoute(int column, int row, int ** rentalMatrix,int ** cheapMatrix){
  if(column == row){
    //ASSERT:column and row are the same
    cheapMatrix[column][row] = 0;
    cheapMatrix[row][column] = 0;
  }
  else if(row + 1 == column){
    //ASSERT:there is only one way to get from rental post column to
    //row because the rental posts are right next to eachother.
    cheapMatrix[column][row] = rentalMatrix[column][row];
    cheapMatrix[row][column] = rentalMatrix[row][column];
  }
  else{
    //ASSERT:There is one or more rental posts inbetween rental post
    //column and row.
    int minimum = rentalMatrix[row][column];
    int lookAtNum = column - row;
    for(int index = 1; index < lookAtNum; index++){
      
      int posMin = cheapMatrix[row][row + index] + cheapMatrix[row + index][column];
      if(posMin < minimum){
	//ASSET:posMin is less than minimum.
	minimum = posMin;
      }
    }
    cheapMatrix[row][column] = minimum;
    cheapMatrix[column][row] = minimum; 
  }
}

//PRE:from is the canoe rental place that you are looking for the best
//route to get to dest from. rental matrix and cheapmatrix are both 2d
//integer matrixes
//POST:outputs to the terminal the minimum cost to go from
//from to dest as well as the route it took to get there.
void outPut(int from, int dest, int ** rentalMatrix, int ** cheapMatrix){
  cout << "This is the minimum cost to get from rental node " << from
	  <<" to rental node "<< dest<<" : ($"<<cheapMatrix[from][dest]<<")"<<endl;
  cout<<"The path of rental places to go from node "<<from<<" to node "<<dest<<
    " to get this minimum cost is"<<endl;
  LinkedList <int> stack;
  int currDest = dest;
  stack.addToFront(dest);
  while(currDest != from){
    //ASSERT:from isnt equal to currdest
    if(cheapMatrix[from][currDest] == rentalMatrix[from][currDest]){
      //ASSERT:the last place we came from is where we started so end
      //loop.
      stack.addToFront(from);
      currDest = from;
    }
    else{
      //ASSERT:we did not come straight from our destination.
      int index = from + 1;//it is 1 because we already looked at 0 in if
      int min = cheapMatrix[from][currDest];
      int minIndex = 0;
      while((index < currDest)){
	int posNum = cheapMatrix[index][currDest];
	if(posNum < min){
	  //ASSERT:we have found where currdest came from
	  minIndex = index;
	}
	//always iterate..
	index++;
      }
      stack.addToFront(minIndex);
      currDest = minIndex;
      
    }
  }//end while
  //ASSERT:stack is finished.
  int numNodes = stack.getNumNodes();
  for(int index = 0; index < numNodes - 1; index ++){
    int num1 = stack.getNth(index);
    int num2 = stack.getNth(index + 1);
    cout << num1<<" ---> "<<num2<<" ($"
	    <<cheapMatrix[num1][num2]<<")"<<endl;
  }
  cout<<endl;
}


