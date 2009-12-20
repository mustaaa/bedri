
#ifndef LISTNODE_H
#define LISTNODE_H

//this is the forward decleration of manager class List, to enable the declare it as friend
template< typename NODETYPE > class List ;

template< typename NODETYPE > 
class ListNode
{
    friend class List< NODETYPE >;
public :
    ListNode (const NODETYPE &); // constructor
    NODETYPE getData() const;    // promise not to change the list
private:
    NODETYPE data;
    ListNode < NODETYPE > * nextPtr ;
    ListNode < NODETYPE > * prevPtr ;
   

};

//constructor 
template < typename NODETYPE >
ListNode < NODETYPE >::ListNode(const NODETYPE &info)
    :data (info) , nextPtr (0) , prevPtr(0)
{
}

template < typename NODETYPE >
NODETYPE ListNode< NODETYPE >::getData() const
{
    return data;
}

#endif