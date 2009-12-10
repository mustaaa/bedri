// 177_cozum.cpp : Defines the entry point for the console application.
//

#include <iostream>

using namespace std;

void fillArray (int n , int * arr);
void findBorders (int* xMaximum,int* xMinimum,int* yMaximum,int* yMinimum, int n , int* arr );

int main(int argc, char* argv[])
{

    int i , j , n , xMax , xMin, yMax , yMin , x , y;
    int *arr;
    char **charArr;
    cout << "Enter N: \n";
    cin >> n;
    if (n>0||n<16)
    {
        arr = new int[1<<n];
    }
    else
    {
        cout << "n should be between 1 and 15";
        return 0;
    }

    arr[0]=3;
    fillArray(n,arr);
    findBorders (&xMax , &xMin , &yMax , &yMin , n , arr );

    charArr = new char *[1+yMax-yMin];
    for (i=0; i<1+yMax-yMin ; i++)
    {
        charArr[i] = new char[1+xMax-xMin];
    }
    for (i=0 ; i<(1+yMax-yMin)  ; i++)
    {
        for (j=0; j<1+xMax-xMin ; j++)
            charArr[i][j] = ' ';
    }

    x=0-xMin;
    y=yMax;

    for ( i = 0 ; i<(1<<n)-1 ; i++ )
    {
        switch (arr[i])
        {
        case 0:
            charArr[y][x] = '_';
            if (arr[i+1]==3)
            {
                y++;
            }
            x++;
            break;
        case 1:
            charArr[y][x] = '|';
            if (arr[i+1]==0)
            {
                x++;
            }
            else // 2
            {
                x--;
            }
            y--;
            break;
        case 2:
            charArr[y][x] = '_';
            if (arr[i+1]==1)
            {
                x--;
            }
            else    // 3
            {
                y++;
                x--;
            }   
            
            break;
        case 3:
            charArr[y][x] = '|';
            if (arr[i+1]==0)
            {
                x++;
            }
            else    // 2
            {
                x--;
            }
            break;
        }
    }
    if (arr[i] == 1 || arr[i] == 3)
        charArr[y][x] = '|';
    else
        charArr[y][x] = '_';


    for (i=0 ; i<(1+yMax-yMin) ; i++)
    {
        for (j=0; j<1+xMax-xMin ; j++)
            cout << charArr[i][j] ;
        cout << "\n";
    }

    cout << "\n";
    for ( i=0; i<(1<<n) ; i++)
        cout << arr[i];
	return 0;
}

void fillArray (int n , int * arr)
{
    int i, j, k;

    for ( i=0 ; i<n ; i++)
    {
        for( k=j=1<<i ; k>0 ; k-- , j++ )
        {
            arr[j] = (arr[k-1] + 1)%4;
        }
    }
}


void findBorders (int* xMaximum,int* xMinimum,int* yMaximum,int* yMinimum, int n , int* arr )
{
    int xMax    = 0;
    int xMin    = 0;
    int xCur    = 0;
    int yMax    = 0;
    int yMin    = 0;
    int yCur    = 0;
    
    for (int i = 1 ; i<(1<<n) ; i++ )
    {
        switch (arr[i])
        {
        case 0:
            if (arr[i-1]==1)
            {
                yCur++;
            }
            xCur++;
            break;
        case 1:
            if (arr[i-1]==0)
            {
                xCur++;
            }
            else // 2
            {
                xCur--;
            }
            break;
        case 2:
            if (arr[i-1]==1)
            {
                yCur++;
            }
            xCur--;
            break;
        case 3:
            if (arr[i-1]==0)
            {
                xCur++;
            }
            else
            {
                xCur--;
            }
            yCur--;
            break;
        }
        if (xCur>xMax)
            xMax=xCur;
        if (xCur<xMin)
            xMin=xCur;
        if (yCur>yMax)
            yMax=yCur;
        if (yCur<yMin)
            yMin=yCur;
    }
    * xMaximum = xMax;
    * xMinimum = xMin;
    * yMaximum = yMax;
    * yMinimum = yMin;

}