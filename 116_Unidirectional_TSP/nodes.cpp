
#include "nodes.h"

using namespace std;

int NumberNode::currentSum  = 0 ; 
int NumberNode::bestSum     = 0x7FFFFFF;

NumberNode::NumberNode (int rowN , int colS , NumberNode* h , int value , int rowSiz , int colSiz):row(rowN) , col(colS) , val(value) , rowSize(rowSiz) , colSize(colSiz)
{

    h?head=h:head=this;
    next = up = down = right = 0;
    //bestSum = 0x7FFFFFF;        // the largest 32 bit positive integer value
    //currentSum = 0;


};

void NumberNode::addNode            ( NumberNode* item)    // adds item to the end of the linked list whose number node is "head"

{
    NumberNode* cur = head;
    if (cur)
    {
        if (item->col == 0)
        {
            while (cur->next)
                cur = cur->next;
            cur->next = item;
            item->next = 0;     //just to be safe
        }
        else
        {
            cur = getRow( (item->row) );
            while (cur->right)
                cur=cur->right;
            cur->right = item;
            item->right = 0;     //just to be safe
        }
    }
    else // should not be the case 
    {
        return;
    }
}

NumberNode * NumberNode::getRow(int rowNumber)
{
    NumberNode* cur = head;
    for (int i = 0 ; i<rowNumber ; i++)
    {
        if (cur->next)
        {
            cur=cur->next;
        }
        else 
        {
            cout << "\ninconsistency in getRow returning NULL pointer\n";
            return 0;
        }
    }
    return cur;
}

NumberNode * NumberNode::getElement (int row, int col)
{
    NumberNode * cur = getRow(row);
    for (int i = 0; i<col ;i++)
    {
        if (cur->right)
        {
            cur = cur->right;
        }
        else 
        {
            cout << "\ninconsistency in getRow returning NULL pointer\n";
            return 0;
        }
    }
    return cur;
}

void NumberNode::buildLinks(void)
{
    NumberNode* cur = head;
    NumberNode* target ;

    for (int i = 0; i<rowSize ; i++)
    {
        for (int j =0 ; j<colSize ; j++)
        {
            cur = getElement(i,j);
            if (cur->right)
            {
                target =  getElement( ((i+rowSize)-1) % rowSize , (j+1) );
                cur->up = target;
                //cout << "\nUP tying  (" << cur->row+1 << "," << cur->col+1 << ") to" << " (" << target->row+1 << "," << target->col+1 << ")";
                target =  getElement( ((i+rowSize)+1) % rowSize , (j+1) );
                cur->down = target;
                //cout << "\nDWN tying (" << cur->row+1 << "," << cur->col+1 << ") to" << " (" << target->row+1 << "," << target->col+1 << ")";
            }
        }
    }

}


void NumberNode::calculateBestPath(void)
{

    NumberNode* temp = head;
    
    while (temp->next)
    {
        calculateForNode(temp);
        temp = temp->next;
    }
    calculateForNode(temp);
}

void NumberNode::calculateForNode (NumberNode* ptr)    // calculates the best route weight beginning from a node
// unfortunately this function does not help to find the "lexicographically smallest", this was a desing disregard from the 
// beginning. but for sure it gives the result with the smallest sum!
// down in this function there is a comment about where and how a possible solution could be
{
    currentStack.push(ptr);
    currentSum += ptr->val;

    if (currentSum > bestSum)  
    {
        currentStack.pop();
        currentSum -= ptr->val;
        return;
    }
    else 
    {
        if (ptr->right == 0)
        {
            if (currentSum == bestSum)
            {
                if ( currentStack.shouldBeReplaced(&bestStack , &currentStack) ) 
                {
                    currentStack.flushAndSwap( &bestStack , &currentStack);
                    bestSum = currentSum;
                    currentStack.pop();
                    currentSum -= ptr->val;
                    return;
                }
                else // if newly found stack is lexicographically larger than current best stack do not replace
                {
                    currentStack.pop();
                    currentSum -= ptr->val;
                    return;
                }
            }
            else // we have found a path that is "lighter" then previously found path, replace!
            {
                currentStack.flushAndSwap( &bestStack , &currentStack);
                bestSum = currentSum;
                currentStack.pop();
                currentSum -= ptr->val;
                return;
            }
        }
        else
        {
            calculateForNode(ptr->right);
            calculateForNode(ptr->up);
            calculateForNode(ptr->down);
            currentStack.pop();
            currentSum -= ptr->val;
            return;
        }
    }
}


void NumberNode::printHeaderList(void)
{
    NumberNode* curRow = head;
    NumberNode* curCol ;

    while (curRow->next)
    {
        curCol = curRow;
        while (curCol->right)
        {
            cout << curCol->val << "\t ";
            curCol = curCol->right;
        }
        cout << curCol->val << "\t ";
        cout << "\n";
        curRow = curRow->next;
    }
    curCol = curRow;
    while (curCol->right)
    {
        cout << curCol->val << "\t ";
        curCol = curCol->right;
    }
    cout << curCol->val << "\t ";
    cout << "\n";


}
void NumberNode::printBestPath(void)
{
    bestStack.printStack(&bestStack);
}

void NumberNode::destroy(void)
{
    NumberNode * tempCol1 ;
    NumberNode * tempCol2 ;

    for (int i=0 ; i < rowSize ; i++)
    {
        tempCol1 = getRow(i);
        if (tempCol1->right)
            tempCol1 = tempCol1->right;     //skip first element they will be freed below
        while (tempCol1->right)
        {
            tempCol2 = tempCol1->right;
            delete tempCol1;
            tempCol1 = tempCol2;
        }
        if (tempCol1->right)
            delete tempCol1;
    }

    if (head->next)
    {
        tempCol1 = head->next;  // head will be deleted by Workplace
        while (tempCol1->next)
        {
            tempCol2 = tempCol1->next;
            delete tempCol1;
            tempCol1 = tempCol2;
        }
        delete tempCol1;
    }
    currentStack.flush();
    bestStack.flush();
}


ResultStack::ResultStack (NumberNode* NodePtr )
{
    ptr = NodePtr;
    next=prev=cur=0;
}

void ResultStack::push(NumberNode * NodePtr)
{
    ResultStack * newNode = new ResultStack(NodePtr);
    cur->next = newNode;
    newNode->prev = cur;
    cur = newNode;
}

NumberNode* ResultStack::pop (void)
{
    ResultStack * topOfStack = cur;
    NumberNode* retval = topOfStack->ptr;
    if (topOfStack->ptr)    // dont pop on empty stack
    {
        cur = cur->prev;
        cur->next = 0;
        delete topOfStack;
        return retval;
    }
    return 0;
}
void ResultStack::flush()
{
    while (pop());
}

void ResultStack::printStack(ResultStack* stack)
{
    ResultStack* temp = stack;
    int result=0;
    cout<< "\nBest path is :\n\n";
    
    temp = temp->next;    // first element is the placeholder
    while (temp->next)
    {
        cout << "(" << temp->ptr->getRowNumber() + 1 <<"," << temp->ptr->getColNumber() + 1 << ") -> ";
        result += temp->ptr->getVal();
        temp = temp->next;
    }
    cout << "(" << temp->ptr->getRowNumber() + 1 <<"," << temp->ptr->getColNumber() + 1 << ")";
    result += temp->ptr->getVal();
    cout << "\ntotal value :" << result;
}

void ResultStack::flushAndSwap (ResultStack* oldBest , ResultStack* newBest)
{
    ResultStack* temp = newBest;
    oldBest->flush();                   //flush the old stack
    temp = temp->next;                  //first element is placeholder
    while (temp->next)                  //go through the new stack
    {
        oldBest->push(temp->ptr);       //push every element as the new best stack
        temp = temp->next;
    }
    oldBest->push(temp->ptr);           //push the last element, newBest stack should remain as it is 
}

bool ResultStack::shouldBeReplaced (ResultStack* oldBest , ResultStack* newBest)   // this function should be called only if sum of two stacks are the same
// returns false if oldBest stack is lexicographically smaller then newly found best stack, returns true otherwise
{
    ResultStack* temp1 = oldBest;
    ResultStack* temp2 = newBest;

    temp1 = temp1->next;
    temp2 = temp2->next;
    while(temp1->next && temp2->next)
    {
        if (temp1->ptr->getRowNumber() < temp2->ptr->getRowNumber() )
            return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    if (temp1->ptr->getRowNumber() < temp2->ptr->getRowNumber() )
        return false;
    else 
        return true;
}



void Workplace::start()
{
    int val;


    cout << "enter the row size \n" ;
    cin >> rowSize;
    
    cout << "enter the coloumn size \n" ;
    cin >> colSize;
    
    if (rowSize<1 || rowSize>10)
    {
        cout << "invalid row size \n" ;
        return;
    }
    else if (colSize<1 || colSize>100)
    {
        cout << "invalid coloumn size \n" ;
        return;
    }
    else 
    {
        // form the NumberNode linked list 

        cout << "begin typing row 1\n";
        cout << "\ncoloumn 1\n";
        cin >> val;
        head = new NumberNode( 0 , 0 , 0 , val , rowSize, colSize);         // set head of the queue, ignore exceptions

        for (int i = 0 ; i<rowSize ; i++)
        {
            if (i!=0)
                cout << "begin typing row " << (i+1) << ":\n";
            for (int j = 0; j<colSize; j++)
            {
                if (!(i==0 && j==0))                // head of the queue has already been created
                {
                    cout << "\ncoloumn " << (j+1) <<"\n";
                    cin >> val;
                    head->addNode(new NumberNode(i,j,head,val , rowSize , colSize));
                }
            }
        }
        cout << "\n The matrix looks like this\n";
        head->printHeaderList();
        head->buildLinks();
        head->calculateBestPath();
        head->printBestPath();
        head->destroy();
        delete head;
        cout << "\nGood Bye!";


    }

}