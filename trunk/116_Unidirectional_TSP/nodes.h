
#ifndef NODES_H
#define NODES_H

#include "nodes.h"
#include <iostream>

class NumberNode; 

class ResultStack
{
public:
    ResultStack (){ptr=0;next=prev=0;cur=this;};
    ResultStack (NumberNode* NodePtr );
    ~ResultStack (){ptr=0; next=prev=0;};
    void push (NumberNode* NodePtr);
    NumberNode* pop (void);
    void flush (void);
    void flushAndSwap(ResultStack* currentBest , ResultStack* newBest);
    bool ResultStack::shouldBeReplaced (ResultStack* oldBest , ResultStack* newBest);
    void printStack(ResultStack* stack);

    

private:
    NumberNode * ptr;
    ResultStack * next;
    ResultStack * prev;
    ResultStack * cur;
};

class NumberNode
{
public:


    NumberNode (int rowN , int colN , NumberNode* h , int value , int rowS , int colS) ;
    
    void setUp(NumberNode * upP){up = upP;};
    void setRight(NumberNode *  rightP){right = rightP;};
    void setDown(NumberNode * downP){down = downP;};
    
    NumberNode* getUp(void){return up;};
    NumberNode* getRight(void){return right;};
    NumberNode* getDown(void){return down;};

    int getRowNumber() {return row;};
    int getColNumber() {return col;};
    int getVal()       {return val;};

    void addNode            ( NumberNode* item);
    void printHeaderList(void);
    void buildLinks (void);             // fills all of the remaining linked lists so the table is complete
    void calculateBestPath(void);
    void calculateForNode (NumberNode* ptr);
    void printBestPath(void);
    void destroy(void);

//    static int currentSum;
//    static int bestSum;

private:
    NumberNode * getRow(int rowNumber);
    NumberNode * getElement (int row, int col);
    int row, col , val , rowSize , colSize;
    NumberNode* up;
    NumberNode* right;
    NumberNode* down;
    NumberNode* next;
    NumberNode* head;

    static int currentSum ;
    static int bestSum;

    ResultStack  currentStack;
    ResultStack  bestStack;


};





class Workplace
{
public:
    Workplace ():head(0){};
    void start();
private:
    NumberNode* head;
    int rowSize, colSize;
};


#endif 