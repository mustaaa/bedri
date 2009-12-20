
#ifndef LIST_H
#define LIST_H

#include <iostream>
using std::cout ;
#include "ListNode.h"


//Doubly Linked List implementation with a current pointer
template <typename NODETYPE>
class List  
{
public:
    List();
    ~List();

// Basic linked list functions, be careful using removeFromFront and removeFromBack functions as they might delete the CurPtr
// so you migth run into inconsistencies 
    void insertAtFront( const NODETYPE &);
    void insertAtBack ( const NODETYPE &);
    bool removeFromFront( /*NODETYPE &*/);
    bool removeFromBack ( /*NODETYPE &*/);
    bool isEmpty () const;
    void print () const;

// functions related with the current ptr, this ptr should be abstracted from user (i.e. list should be capable of being handled 
// only by its public interface yet should be flexible) all functions return true if requested operation is done correctly 
// here the functions that come to my mind in the initial implementation :
// ps. this interface could be extended so that List class has more than one curPtr but multiple pointers (through curPtrArr ?)
    bool setCurPtrToFirstNode() ;
    bool setCurPtrToLastNode() ;
    bool getCurPtrData( NODETYPE & data) const;
    bool setCurPtrData( const NODETYPE & data) ;
    bool setCurPtrToNextNode() ; // returns false if CurPtr is the last node
    bool setCurPtrToPrevNode() ; // returns false if CurPtr is the first node 
    bool insertAtFrontAndSetCurPtr(const NODETYPE &data) ; // inserts an element to the head of the list and sets the curPtr to this
    bool insertAtBackAndSetCurPtr(const NODETYPE &data) ; // inserts an element to the back of the list and sets the curPtr to this
    bool insertAfterCurPtr(const NODETYPE data) ; // creates a new node and links it after CurPtr, does not modify the CurPtr
    bool insertAfterCurPtrAndIncrement(const NODETYPE data) ; // creates a new node and links it after CurPtr, then modifies CurPtr to be this new node
    bool insertBeforeCurPtr(const NODETYPE data) ; // creates a new node and links it before CurPtr, does not modify the CurPtr
    bool insertBeforeCurPtrAndDecrement(const NODETYPE data) ; // creates a new node and links it before CurPtr, then modifies CurPtr to be this new node
    bool setCurPtrToNull(); // after calling this current ptr is void
    bool deleteCurPtr(); // deletes the node pointed by the curPtr, if there was a node after curPos before deletion, new curPos is that node, if not curPos is the lastPtr; namely the last node

private:
    ListNode <NODETYPE> *firstPtr;
    ListNode <NODETYPE> *lastPtr;
    ListNode <NODETYPE> *curPtr;        // this pointer is supplied for the use of client of this class  

    ListNode<NODETYPE> *getNewNode(const NODETYPE &);

};

template <typename NODETYPE>
List<NODETYPE>::List()
:firstPtr(0) , lastPtr(0) , curPtr(0)
{

}

template <typename NODETYPE>
List<NODETYPE>::~List()
{
    if( !isEmpty() )
    {
        cout << "Destroying nodes ...\n" ; 

        ListNode <NODETYPE> *currentPtr = firstPtr;
        ListNode <NODETYPE> *tempPtr; 

        while (currentPtr != 0)
        {
            tempPtr = currentPtr;
//            cout << tempPtr->data << '\n';
            currentPtr = currentPtr->nextPtr;
            delete tempPtr;
        }
    }
    cout << "all nodes deleted";
}

template <typename NODETYPE>
void List<NODETYPE>::insertAtFront(const NODETYPE &value)
{
    ListNode <NODETYPE> *newPtr = getNewNode(value);

    if (isEmpty())
    {
        firstPtr = lastPtr = newPtr; // curPtr is not set to anything here, user should explicitly set it using utility functions
    }
    else 
    {
        newPtr->nextPtr = firstPtr;
        firstPtr->prevPtr = newPtr;
        firstPtr = newPtr;
    }
}

template <typename NODETYPE>
void List<NODETYPE>::insertAtBack(const NODETYPE &value)
{
    ListNode<NODETYPE> *newPtr = getNewNode(value);
    
    if( isEmpty() )
        firstPtr = lastPtr = newPtr;
    else 
    {
        lastPtr->nextPtr = newPtr;
        newPtr->prevPtr = lastPtr;
        lastPtr = newPtr;
    }
}

template <typename NODETYPE>
bool List<NODETYPE>::removeFromFront(/*NODETYPE &value*/)
{
    if (isEmpty())
    {
        return false;
    }
    else 
    {
        ListNode<NODETYPE> *tempPtr = firstPtr; 
        
        if (firstPtr == curPtr)
            curPtr = 0;             // in this case clear the curPtr as well
            
        if ( firstPtr == lastPtr)
            firstPtr = lastPtr = 0;
        else 
        {
            firstPtr->nextPtr->prevPtr = 0;
            firstPtr = firstPtr->nextPtr;
        }
//        value = tempPtr->data;  // return data being removed , why ? dont know may be helpful
        delete tempPtr;
        return true;
    }
}

template <typename NODETYPE>
bool List<NODETYPE>::removeFromBack(/*NODETYPE &value*/)
{
    if ( isEmpty() )
        return false ;
    else
    {
        ListNode<NODETYPE> *tempPtr = lastPtr;

        if (lastPtr == curPtr)      // if pointer for user "curPtr" points to the last node, set it to null 
            curPtr = 0;

        if (firstPtr == lastPtr)
            firstPtr = lastPtr = 0;
        else 
        {
            lastPtr->prevPtr->nextPtr=0;
            lastPtr = lastPtr->prevPtr;
        }
//        value = tempPtr->data;
        delete tempPtr;
        return true;
    }
}


template <typename NODETYPE>
bool List<NODETYPE>::isEmpty() const
{
    return firstPtr == 0;
}


template <typename NODETYPE>
ListNode<NODETYPE> * List<NODETYPE>::getNewNode( const NODETYPE &value)
{
    return new ListNode <NODETYPE> (value);
}


template <typename NODETYPE>
void List<NODETYPE>::print() const
{
    if (isEmpty())
    {
        cout << "\nThe list is empty \n";
        return;
    }
    ListNode <NODETYPE> * currentPtr = firstPtr;
    cout << "\nThe list goes like: "  ;
    while ( currentPtr!=0 )
    {
        cout << currentPtr->data << " -> ";      // here we are assuming of data to be a "printable" data value
        currentPtr = currentPtr->nextPtr;
    }
    cout << "NULL \n";
}


// function implementations for curPtr


template <typename NODETYPE>
bool List<NODETYPE>::setCurPtrToFirstNode() 
{
    if (firstPtr)
    {
        curPtr = firstPtr;
        return true;
    }
    else // list is empty
    {
        return false;
    }
}

template <typename NODETYPE>
bool List<NODETYPE>::setCurPtrToLastNode() 
{
    if (lastPtr)
    {
        curPtr = lastPtr;
        return true;
    }
    else // list is empty
    {
        return false;
    }
}


template <typename NODETYPE>
bool List<NODETYPE>::getCurPtrData( NODETYPE & data) const
{
    if (curPtr)
    {
        data = curPtr->data;
        return true;
    }
    else 
        return false;
}

template <typename NODETYPE>
bool List<NODETYPE>::setCurPtrData(const NODETYPE & data) 
{
    if (curPtr)
    {
        curPtr->data = data;
        return true;
    }
    else 
        return false;
}

template <typename NODETYPE>
bool List<NODETYPE>::setCurPtrToNextNode()
{
    if (curPtr)
    {
        if (curPtr->nextPtr)
        {
            curPtr = curPtr->nextPtr;
            return true;
        }
        else 
            return false;
    }
    else 
        return false;
}

template <typename NODETYPE>
bool List<NODETYPE>::setCurPtrToPrevNode()
{
    if (curPtr)
    {
        if (curPtr->prevPtr)
        {
            curPtr = curPtr->prevPtr;
            return true;
        }
        else 
            return false;
    }
    else 
        return false;
}

template <typename NODETYPE>
bool List<NODETYPE>::insertAtFrontAndSetCurPtr(const NODETYPE &data)
{
    insertAtFront(data);
    return setCurPtrToFirstNode();
}

template <typename NODETYPE>
bool List<NODETYPE>::insertAtBackAndSetCurPtr(const NODETYPE &data)
{
    insertAtBack(data);
    return setCurPtrToLastNode();
}

template <typename NODETYPE>
bool List<NODETYPE>::insertAfterCurPtr(const NODETYPE data) 
{
    if (curPtr)
    {
        ListNode <NODETYPE> *newPtr = getNewNode(data);
        
        if (curPtr->nextPtr)    
        {
            curPtr->nextPtr->prevPtr = newPtr;
        }
        else    // curPtr is the last node, so new node should be the new lastPtr
        {
            lastPtr = newPtr;
        }
        newPtr->nextPtr = curPtr->nextPtr;
        curPtr->nextPtr = newPtr;
        newPtr->prevPtr = curPtr;
        return true;
    }
    else 
        return false;
}

template <typename NODETYPE>
bool List<NODETYPE>::insertAfterCurPtrAndIncrement(const NODETYPE data) // this func seems unnecessary
{
    if (insertAfterCurPtr(data))
    {
        return setCurPtrToNextNode();      // no need to check the return value
    }
    else
        return false;
}

template <typename NODETYPE>
bool List<NODETYPE>::insertBeforeCurPtr(const NODETYPE data) 
{
    if (curPtr)
    {
        ListNode <NODETYPE> *newPtr = getNewNode(data);
        
        if (curPtr->prevPtr)
        {
            curPtr->prevPtr->nextPtr = newPtr;
        }
        else  // new node will be the first node now
        {
            firstPtr = newPtr;
        }
        newPtr->prevPtr = curPtr->prevPtr;
        newPtr->nextPtr = curPtr;
        curPtr->prevPtr = newPtr;
        return true;
    }
    else 
        return false;
}

template <typename NODETYPE>
bool List<NODETYPE>::insertBeforeCurPtrAndDecrement(const NODETYPE data) // maybe unnecessary
{
    if (insertBeforeCurPtr(data))
    {
        return setCurPtrToPrevNode();      // no need to check the return value
    }
    else
        return false;
}

template <typename NODETYPE>
bool List<NODETYPE>::setCurPtrToNull()
{
    curPtr=0;
    return true;
}

template <typename NODETYPE>
bool List<NODETYPE>::deleteCurPtr()     // always returns true         
{
    ListNode <NODETYPE> *tempPtr = curPtr->prevPtr;
    if (curPtr)
    {
        if (curPtr->prevPtr)
        {
            curPtr->prevPtr->nextPtr = curPtr->nextPtr;
        }
        else // curPtr is the first node
        {
            removeFromFront();
            curPtr = tempPtr;
            return true;
        }
        if (curPtr->nextPtr)
        {
            curPtr->nextPtr->prevPtr = curPtr->prevPtr;
        }
        else // curPtr is the last node
        {
            removeFromBack();
            curPtr = tempPtr;
            return true;
        }
        
        // curPtr is somewhere in the middle
        delete curPtr;
        curPtr = tempPtr;
        return true;
    }
    else 
        return true;    
}

#endif