#include "193.h"

using namespace std;

// TODO : input should be made dynamic
//		: cover the special cases like all black, no black nodes
//		: input and output should be in the format requested

void Graph::wp(void)
{
    
    int i=0;
    int path ;
	
    int verticeNum = 8;
    int pathArr[8] = {12,13,24,25,34,36,46,56};
	dimension = 6;
	/*
    int verticeNum = 11;
    int pathArr[11] = {12,16,24,28,35,36,38,56,57,78,89};
	dimension = 9;
    */

    cout<<"Enter the graph connections... first number of nodes\n";
    
    
    //cin >> dimension;
    cout << dimension << "\n";

    table = new int*[dimension];

    for (i=0; i<dimension; i++)
    {
        table[i] = new int[dimension];
    }

    for (i=0; i<dimension; i++) 
    {
        for (int j=0 ; j<dimension ; j++)
        {
            table[i][j] = 0;                    // Initialize all elements to zero.
        }
    }

    cout<<"Enter number of graph connection\n";
    //cin >> verticeNum;
    cout<<verticeNum << "\n";

    cout<<"Enter vertices\n";
    //start getting the vectors
    for (i=0 ; i<verticeNum ; i++)
    {
        //cin >> path;
        path=pathArr[i];

        table [ (path/10)-1 ][ (path%10)-1 ] = 1;
        table [ (path%10)-1 ][ (path/10)-1 ] = 1;
    }
/*
    cout << findTotalCombinationNumber(1 , 1) <<"\n";
    cout << findTotalCombinationNumber(5 , 2) <<"\n";
    cout << findTotalCombinationNumber(6 , 2) <<"\n";
*/

    for( i=1; i<=dimension; i++)
    {
        if(findCombinationsLexicographically (dimension,i,findTotalCombinationNumber(dimension , i)))
            return;
    }

}


void Graph::printTable(void)
{
    for (int i=0; i<dimension; i++) 
    {
        for (int j=0 ; j<dimension ; j++)
        {
            cout << table[i][j] << " ";                    // Initialize all elements to zero.
        }
        cout << "\n";
    }
}


void Graph::destroy (void)
{
    for (int i = 0 ; i<dimension ; i++)
    {
        delete [] table[i];
    }
    delete [] table;
}

int Graph::findTotalCombinationNumber(int n , int r)
{
    int ret = 1;
	if (n>=r)
	{
		if (n > 0 && r > 0)
		{
			for ( int i=0 ; i<r ; i++ )
			{
				ret *=n;
				n--;
			}
			for ( int i=1 ; i<=r ; i++ )
			{
				ret /=i;
			}
			return ret;
		}
		else 
			return 1;	// 0! = 1
	}
	else
	{
		return -1;	// ERROR
	}
}


bool Graph::findCombinationsLexicographically (int n , int r , int C_n_r )
{
    int i,j,m,max_val;
    int *s;

    s = new int[r];

    for (i=0 ; i<r ; i++)
    {
        s[i] = i+1;
    }// first r combination is formed

    // CALL FUNCTION HERE
    int *guess = new int[n-r];
    int indexOrig = 0;
	int indexGuess = 0;
    for (int count = 0; count<n ; count++)
	{
		if ( s[indexOrig] != count+1)
        {
            guess[indexGuess] = count+1;
            indexGuess++;
        }
		else 
		{
			indexOrig++;
		}
	}
    if (checkCandidate(guess,n-r))
	{
		cout << "solution found black nodes are: " ;
		for (int k=0 ; k<n-r ; k++)
			cout << guess[k] << " " ;
		cout << "\n";
		delete [] guess;
		delete [] s;
		return true;
	}
    // CALL FUNCTION HERE

    for (i=1 ; i<C_n_r ; i++)
    {
        m=(r-1);
        max_val = n;
        while ( s[m] == max_val)
        {
            // find the rightmost element not at its maximum value
            m--;
            max_val--;
        }
        // rightmost  element is incremented
        s[m]++;
        // the rest of the elements are the successors of s[m]
        for ( j=m+1 ; j<r ; j++)
        {
            s[j] = s[j-1] + 1;
        }

        // CALL FUNCTION HERE
        int *guess = new int[n-r];
        int indexOrig = 0;
		int indexGuess = 0;
        for (int count = 0; count<n ; count++)
		{
			if ( s[indexOrig] != count+1)
            {
                guess[indexGuess] = count+1;
                indexGuess++;
            }
			else 
			{
				indexOrig++;
			}
		}
        if (checkCandidate(guess,n-r))
		{
			cout << "solution found black nodes are: " ;
			for (int k=0 ; k<n-r ; k++)
				cout << guess[k] << " " ;
			cout << "\n";
			delete [] guess;
			delete [] s;
            return true;
		}
        // CALL FUNCTION HERE
    }
	delete [] guess;
	delete [] s;
	//cout << "could not find a solution for " << n-r << " black nodes, will try with less\n";
    return false;
}

bool Graph::checkCandidate (int *guess , int widthOfGuess )
{
    for (int i=0 ; i<widthOfGuess ; i++)
    {
        for (int k=0 ; k<widthOfGuess ; k++)
        {         
           if ( 
                //(guess[i] != table[guess[i]-1][guess[k]-1])&& //do not check the guess against itsself, there is no "1" entry in the table for that case (path from a point to itsself is not designated) 
                table[guess[i]-1][guess[k]-1]   // if there is a path between two points they cant be black so return false 
               )
           {
               return false;
           }
        }
	}
    return true;
}
