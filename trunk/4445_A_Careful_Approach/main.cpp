
#include <string>
#include <iostream>
#include <fstream>

using std::string;

using namespace std;

#include "careful.h"

int main (int argc, char* argv[])
{

    int n , begin , end;
    LandingScheduler ls;
    
    ifstream input , output;
    input.open(argv[1]);
    //input.open("approach.in");
    if (!input) {
		cerr << "error: unable to open file " << argv[1] << endl;
        return -1;
    }
  //  output.open("approach.out",ios_base::out);
  //  if (!output) {
		//cerr << "error: unable to open file " << "approach.out" << endl;
  //      return -1;
  //  }
    input >> n;
    if ((n<2||n>8)&&(n!=0))
    {
        cerr << "Error in input file!";
        return -1;
    }
    while (n!=0)
    {
        ls.resetLandingScheduler(n);
        for (int i = 0; i<n ; i++)
        {
            input >> begin;
            input >> end;
            if (end<begin||begin<0||end<0)
            {
                cerr << "Error in input file!";
                return -1;
            }
            ls.insertLandingInterval(begin,end);
        }
        ls.findSolution();
        
        input >> n;
        if ((n<2||n>8)&&(n!=0))
        {
            cerr << "Error in input file!";
            return -1;
        }
    }
    return 0;
}

//ignore
    //List <int> integerlist;
    //int a ;
    //integerlist.insertAtFrontAndSetCurPtr(1);
    //integerlist.print();
    //integerlist.insertAfterCurPtr(2);
    //integerlist.print();
    //integerlist.insertAfterCurPtrAndIncrement(3);
    //integerlist.print();
    //integerlist.setCurPtrToNextNode();
    //integerlist.deleteCurPtr();
    //integerlist.getCurPtrData(a);
    //cout << "\n" << a << "\n" ;
    //integerlist.print();
    //integerlist.removeFromBack();
    //integerlist.print();
    //integerlist.setCurPtrToFirstNode();
    //integerlist.getCurPtrData(a);
    //cout << "\n" << a << "\n" ;
    //integerlist.insertBeforeCurPtr(4);
    //integerlist.print();
    //integerlist.insertBeforeCurPtrAndDecrement(5);
    //integerlist.getCurPtrData(a);
    //cout << "\n" << a << "\n" ;
    //integerlist.print();
    //integerlist.insertAtBack(6);
    //integerlist.print();
    //integerlist.setCurPtrToLastNode();
    //integerlist.setCurPtrToPrevNode();
    //integerlist.setCurPtrToPrevNode();
    //integerlist.getCurPtrData(a);
    //cout << "\n" << a << "\n" ;
    //integerlist.print();
