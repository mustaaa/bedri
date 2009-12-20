
#include <string>
using std::string;

#include "List.h"

int main ()
{
    List <int> integerlist;
    int a ;
    integerlist.insertAtFrontAndSetCurPtr(1);
    integerlist.print();
    integerlist.insertAfterCurPtr(2);
    integerlist.print();
    integerlist.insertAfterCurPtrAndIncrement(3);
    integerlist.print();
    integerlist.setCurPtrToNextNode();
    integerlist.deleteCurPtr();
    integerlist.getCurPtrData(a);
    cout << "\n" << a << "\n" ;
    integerlist.print();
    integerlist.removeFromBack();
    integerlist.print();
    integerlist.setCurPtrToFirstNode();
    integerlist.getCurPtrData(a);
    cout << "\n" << a << "\n" ;
    integerlist.insertBeforeCurPtr(4);
    integerlist.print();
    integerlist.insertBeforeCurPtrAndDecrement(5);
    integerlist.getCurPtrData(a);
    cout << "\n" << a << "\n" ;
    integerlist.print();
    integerlist.insertAtBack(6);
    integerlist.print();
    integerlist.setCurPtrToLastNode();
    integerlist.setCurPtrToPrevNode();
    integerlist.setCurPtrToPrevNode();
    integerlist.getCurPtrData(a);
    cout << "\n" << a << "\n" ;
    integerlist.print();

    return 0;
}