// 229.cpp : Defines the entry point for the console application.
//

#include "scanner.h"
/*
const int ROW_SIZE = 10;	    //n
const int COL_SIZE = 15;        //m
const int MAX_WEIGHT = 2520;
const int MAX_LENGTH = ROW_SIZE + COL_SIZE - 1;
*/
const int scanner::arr1 [ scanner::ROW_SIZE ]                 = {10, 10, 6, 4, 6, 8, 13, 15, 11, 6};
const int scanner::arr2 [ scanner::ROW_SIZE + scanner::COL_SIZE - 1 ]  = {0, 1, 2, 2, 2, 2, 4, 5, 5, 6, 7, 6, 5, 6, 6, 5, 5, 6, 6, 3, 2, 2, 1, 0};
const int scanner::arr3 [ scanner::COL_SIZE ]                 = {2, 4, 5, 5, 7, 6, 7, 10, 10, 10, 7, 3, 3, 5, 5};
const int scanner::arr4 [ scanner::ROW_SIZE + scanner::COL_SIZE - 1 ]  = {0, 0, 1, 3, 4, 4, 4, 4, 3, 4, 5, 7, 8, 8, 9, 9, 6, 4, 4, 2, 0, 0, 0, 0};

int _tmain(int argc, _TCHAR* argv[])
{
    scanner wp;
    wp.start();
	return 0;
}

