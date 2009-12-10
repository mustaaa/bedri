
#ifndef f193_H
#define f193_H


#include <iostream>
#include <string> 

class Graph 
{
public:
    //    void Wp(void);
    void printTable (void);
    void wp(void);
    void destroy(void);


private:
    int dimension;
    int **table;
    void fillTable (void);
    int findTotalCombinationNumber(int n , int r);      //total number of r combinations of a n element set
    bool findCombinationsLexicographically (int n , int r , int C_n_r /*total combination number*/) ; 
	bool checkCandidate (int *guess , int widthOfGuess );	// check the generated combination for validness 
};


#endif  f193_H