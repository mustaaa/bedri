
#include "scanner.h"
#include <iostream>
#include <iomanip>

//#using std::cout;
//#using std::endl;

scanner::scanner()
{
    for (int i=0 ; i<ROW_SIZE ; i++)
    {
        for (int j=0 ; j<COL_SIZE ; j++)
        {  
            table[i][j]=0;
            table1[i][j]=0;
            table2[i][j]=0;
        }
    }
}


void scanner::calculateWeights()
{
    int crosswidth = 0;
    int rowBegin = 0;
    int colBegin = 0;
    int biggerDimension = (ROW_SIZE>=COL_SIZE)?ROW_SIZE:COL_SIZE;
    int smallerDimension = (ROW_SIZE<COL_SIZE)?ROW_SIZE:COL_SIZE;

    
    for (  int i=0 ; i<ROW_SIZE ; i++)
    {
        for (  int j=0 ; j<COL_SIZE ; j++)
        {           
            table[i][j] += ( MAX_WEIGHT * arr1[i] ) / COL_SIZE;     // 1st scan, add the weights of rows from left to right
            //table[i][j] +=  ((( MAX_WEIGHT * arr1[i] ) / (COL_SIZE)) /  COL_SIZE);     // 1st scan, add the weights of rows from left to right
            //table[i][j] +=  arr1[i];
            //table[i][j] += ( (MAX_WEIGHT/COL_SIZE)*(MAX_WEIGHT/COL_SIZE)) * arr1[i] );

            //table[i][j] += ( MAX_WEIGHT * arr3[j] ) / ROW_SIZE ;     // 3rd scan, add the weights of coloumns top down
            table[i][j]  = ( table[i][j] * arr3[j] ) / ROW_SIZE ;
            //table[i][j] +=   ((( MAX_WEIGHT * arr3[j] ) / (ROW_SIZE))   /   ROW_SIZE );     // 3rd scan, add the weights of coloumns top down
            //table[i][j] += arr3[j]; 
            //table[i][j] += ( (MAX_WEIGHT/ROW_SIZE)*(MAX_WEIGHT/ROW_SIZE) ) * arr3[j] )  ;

            if (i+j<smallerDimension)                               // calculate the divider for second scan
                crosswidth = i+j+1;
            else if (i+j<biggerDimension)
                crosswidth = smallerDimension;
            else 
                crosswidth = smallerDimension - 1 - (i + j - biggerDimension) ;
            //table[i][j] += ( MAX_WEIGHT * arr2[i+j] ) / crosswidth;   // 2nd scan, add the weights of cross squares in northeast direction
            table[i][j] = ( table[i][j] * arr2[i+j] ) / crosswidth; 
            //table[i][j] +=  ((( MAX_WEIGHT * arr2[i+j] ) / (crosswidth))/crosswidth );   // 2nd scan, add the weights of cross squares in northeast direction
            //table[i][j] += arr2[i+j];
            //table[i][j] += ( (MAX_WEIGHT/crosswidth)*(MAX_WEIGHT/crosswidth)*arr2[i+j] );

           
            if (ROW_SIZE-i+j<smallerDimension)                               // calculate the divider for second scan
                crosswidth = ROW_SIZE-i+j;
            else if (ROW_SIZE-i+j<=biggerDimension)
                crosswidth = smallerDimension;
            else 
                crosswidth = smallerDimension-(ROW_SIZE-i+j-biggerDimension);
            //table[i][j] += ( MAX_WEIGHT * arr4[ROW_SIZE-i+j-1] ) / crosswidth;   // 2nd pass, add the weights of cross squares in northeast direction
            table[i][j] = ( table[i][j] * arr4[ROW_SIZE-i+j-1] ) / crosswidth;
            //table[i][j] +=   ((( MAX_WEIGHT * arr4[ROW_SIZE-i+j-1] ) / (crosswidth)) / crosswidth );   // 2nd pass, add the weights of cross squares in northeast direction
            //table[i][j] += arr4[ROW_SIZE-i+j-1];
            //table[i][j] += ( (MAX_WEIGHT/ crosswidth)*(MAX_WEIGHT/ crosswidth) * arr4[ROW_SIZE-i+j-1] ) ;
            /* */
        }
    }
    /*
    printWeights(true , 0);
    std::cout << std::endl;
    for (int i=0 ; i<ROW_SIZE ; i++)
    {
        for (int j=0 ; j<COL_SIZE ; j++)
        {  
            table[i][j] += ( MAX_WEIGHT * arr3[j] ) / ROW_SIZE ;     // 3rd scan, add the weights of coloumns top down
            //table[i][j] +=   ((( MAX_WEIGHT * arr3[j] ) / (ROW_SIZE))   /   ROW_SIZE );     // 3rd scan, add the weights of coloumns top down
            //table[i][j] *= arr3[j]; 
        }
    }
    printWeights(true , 0);
    std::cout << std::endl;
    
    for (int i=0 ; i<ROW_SIZE ; i++)
    {
        for (int j=0 ; j<COL_SIZE ; j++)
        {   
            if (i+j<smallerDimension)                               // calculate the divider for second scan
                crosswidth = i+j+1;
            else if (i+j<biggerDimension)
                crosswidth = smallerDimension;
            else 
                crosswidth = smallerDimension - 1 - (i + j - biggerDimension) ;
                table[i][j] += ( MAX_WEIGHT * arr2[i+j] ) / crosswidth;   // 2nd scan, add the weights of cross squares in northeast direction
                //table[i][j] +=  ((( MAX_WEIGHT * arr2[i+j] ) / (crosswidth))/crosswidth );   // 2nd scan, add the weights of cross squares in northeast direction
                //table[i][j] *= arr2[i+j];
        }
    } 
    
    printWeights(true, 0);
    std::cout << std::endl;
    *//*
    for (int i=0 ; i<ROW_SIZE ; i++)
    {
        for (int j=0 ; j<COL_SIZE ; j++)
        {  
            if (ROW_SIZE-i+j<smallerDimension)                               // calculate the divider for second scan
                crosswidth = ROW_SIZE-i+j;
            else if (ROW_SIZE-i+j<=biggerDimension)
                crosswidth = smallerDimension;
            else 
                crosswidth = smallerDimension-(ROW_SIZE-i+j-biggerDimension);
                table[i][j] += ( MAX_WEIGHT * arr4[ROW_SIZE-i+j-1] ) / crosswidth;   // 2nd pass, add the weights of cross squares in northeast direction
                //table[i][j] +=   ((( MAX_WEIGHT * arr4[ROW_SIZE-i+j-1] ) / (crosswidth)) / crosswidth );   // 2nd pass, add the weights of cross squares in northeast direction
            //table[i][j] *= arr4[ROW_SIZE-i+j-1];
        }
    }
    printWeights(true , 0);
    std::cout << std::endl;
    */
}

void scanner::deleteMinimumsHor ()
{
    int minNumber ;
    int maxNumber = 0;
    int prevMaxNumber = 0;
    int minIndex;
    int tableTemp [ ROW_SIZE ][ COL_SIZE ] ;
    
    for ( int i=0 ; i<ROW_SIZE ; i++)
    {
        for ( int k=0 ; k<COL_SIZE ; k++)
        {
            tableTemp [i][k]= table[i][k];
        }
    }

    for ( int i=0 ; i<ROW_SIZE ; i++)
    {
        minNumber=0;
        for ( int k=0 ; k<COL_SIZE ; k++)
        {
            maxNumber = ( tableTemp[i][k] > maxNumber)?tableTemp[i][k]:maxNumber;  
            minNumber = maxNumber;
        }
        for ( int j=0 ; j<(COL_SIZE-arr1[i]) ; j++ )
        {
            minNumber=maxNumber;
            for ( int k=0 ; k<COL_SIZE ; k++)
            {
                if ( (table[i][k] < minNumber) && (tableTemp[i][k]>=0) )
                {
                    minNumber = tableTemp[i][k];
                    minIndex = k;
                }
            }
            tableTemp[i][minIndex] = -1;
        }
    }
    for ( int i=0 ; i<ROW_SIZE ; i++)
    {
        for ( int k=0 ; k<COL_SIZE ; k++)
        {
            table1 [i][k]= (tableTemp[i][k]==-1)?0:1;
        }
    }
}
void scanner::deleteMinimumsVer ()
{
    int minNumber ;
    int maxNumber = 0;
    int minIndex;
    
    int tableTemp [ ROW_SIZE ][ COL_SIZE ] ;
    
    for ( int i=0 ; i<ROW_SIZE ; i++)
    {
        for ( int k=0 ; k<COL_SIZE ; k++)
        {
            tableTemp [i][k]= table[i][k];
        }
    }
    for ( int i=0 ; i<COL_SIZE; i++)
    {
        minNumber=0;
        for ( int k=0 ; k<ROW_SIZE  ; k++)
        {
            maxNumber = ( tableTemp[k][i] > maxNumber)?tableTemp[k][i]:maxNumber;  
        }
        for ( int j=0 ; j<(ROW_SIZE-arr3[i]) ; j++ )
        {
            minNumber=maxNumber;
            for ( int k=0 ; k<ROW_SIZE ; k++)
            {
                if ( (tableTemp[k][i] < minNumber) && (tableTemp[k][i]>=0) )
                {
                    minNumber = tableTemp[k][i];
                    minIndex = k;
                }
            }
            tableTemp[minIndex][i] = -1;
        }
    }
    for ( int i=0 ; i<ROW_SIZE ; i++)
    {
        for ( int k=0 ; k<COL_SIZE ; k++)
        {
            table2 [i][k]= (tableTemp[i][k]==-1)?0:1;
        }
    }
}
void scanner::printWeights(bool printAll , int tableNum)
{
    for (int i=0 ; i<ROW_SIZE ; i++)
    {
        for (int j=0 ; j<COL_SIZE ; j++)
        {  

            if (printAll)
                std::cout << std::setw(6) << table[i][j]  ;
            else 
            {
                switch (tableNum)
                {
                case 0:
                    {
                    if (table[i][j]>0)
                        std::cout << std::setw(1) <<"#"  ;
                    else 
                        std::cout << std::setw(1) << "."  ;
                    break;
                    }
                case 1:
                    {
                    if (table1[i][j]==1)
                        std::cout << std::setw(1) <<"#"  ;
                    else 
                        std::cout << std::setw(1) << "."  ;
                    break;
                    }
                case 2:
                    {
                    if (table2[i][j]==1)
                        std::cout << std::setw(1) <<"#"  ;
                    else 
                        std::cout << std::setw(1) << "."  ;
                    break;
                    }
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void scanner::start()
{
    calculateWeights();
    deleteMinimumsHor();
    deleteMinimumsVer();
    printWeights(true , 0);
    printWeights(false , 1);
    printWeights(false , 2);
}