#include "Helper.h"
#include <iostream>
#include<fstream>
using namespace std;

int main (int argc, char * argv[]) {

  if (argc == 2) {
    // ASSERT: The number of arguments is correct.
    ifstream inFile (argv[1]); // inFile is the input file stream
			       // corresponding to the file with name in
			       // argv[1].
    
    if ((inFile != NULL)) {
      int numRentals;
      inFile >> numRentals; //numRentals holds the first number in the
			    //infile which represents the number of
			    //rental places.
      if(numRentals >= 1){
	//CREATE NEW MATRIX
	int ** rentalMatrix;//initalze matrix
	rentalMatrix = new int * [numRentals];
	for(int index = 0; index < numRentals; index++){
	  rentalMatrix[index] =  new int [numRentals];
	}
	//END CREATE NEW MATRIX
	
	
	readInput(inFile,rentalMatrix,numRentals);
	printMatrix(rentalMatrix,numRentals);
	cout<<"________________"<<endl;
	cout<<endl;
	//create optimal cost array
	int ** cheapMatrix;
	cheapMatrix = new int * [numRentals];
	for(int index = 0; index < numRentals; index ++){
	  cheapMatrix[index] = new int [numRentals];
	  //cheapArray [index][0] will be the minimum cost to get to
	  //rental place index, cheapArray[index][1] will number of
	  //the rental place we came from to get that min cost.
	}

	findOptimalRoute(rentalMatrix,cheapMatrix,numRentals);
	printMatrix(cheapMatrix, numRentals);

	bool userInput = true;
	int start;
	int end;
	while(userInput){
	  cout<<"if you wish to end the program please input 0 after both questions"<<endl;
	  cout<<"Enter the starting post : ";
	  cin >> start;
	  cout<<"Enter the ending post : ";
	  cin >> end;
	  if((end == 0) && (start ==0)){
	    //ASSERT:user wants to end the program
	    cout<<"Ending program"<<endl;
	    userInput = false;
	  }
	  else if(start > end){
	    //ASSERT:incorrect input
	    cout<<"Error in program input"<<endl;
	  }
	  else if((start > numRentals - 1) || (end > numRentals - 1)){
	    cout<<"One of the rental posts you have inputted are invalid,"
		<<" the rental posts go from 0 to "<<numRentals - 1<<endl;
	  }
	  else{
	    outPut(start,end,rentalMatrix, cheapMatrix);
	    cout<<endl;
	  }
	}
	

	
	inFile.close();//must close infile
	//ASSERT:infile has been closed
	
	//need to deallocate matrix after everything is done.
	for(int index = 0; index < numRentals; index++){
	  delete rentalMatrix[index];
	  delete cheapMatrix[index];
	}
	//ASSERT:all submatrixes have been deleted
	delete cheapMatrix;
	delete rentalMatrix;
	//ASSERT:matrixs has been deleted.
      }
      else{
	cout<<"invalid number of rental places"<<endl;
      }
      
    }
    else {
      // ASSERT: Input file or output file could not be opened
      cout << "Input file could not be opened or outputfile could not be opened" << endl;
    }
  }
  else {
    // ASSERT: incorrect number of arguments
    cout << "Usage: ./bestRental <input file name>" << endl; 
  }
 
  return (0);
}
