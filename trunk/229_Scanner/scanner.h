
#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <tchar.h>


class scanner 
{
public:
scanner();
void start();

static const int ROW_SIZE = 10;	    //n
static const int COL_SIZE = 15;        //m
static const int MAX_WEIGHT = 2520;
static const int MAX_LENGTH = ROW_SIZE + COL_SIZE - 1;
static const int arr1 [ ROW_SIZE ] ;
static const int arr2 [ ROW_SIZE + COL_SIZE - 1 ] ;
static const int arr3 [ COL_SIZE ] ;
static const int arr4 [ ROW_SIZE + COL_SIZE - 1 ] ;

private:
void calculateWeights();
void printWeights(bool, int);
void deleteMinimumsHor ();
void deleteMinimumsVer ();


int table [ ROW_SIZE ][ COL_SIZE ] ;
int table1 [ ROW_SIZE ][ COL_SIZE ] ;
int table2 [ ROW_SIZE ][ COL_SIZE ] ;
};


#endif