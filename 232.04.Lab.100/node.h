/***********************************************************************
 * Header:
 *    NODE
 * Summary:
 *    One node in a linked list (and the functions to support them).
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        Node         : A class representing a Node
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    Isabel Aranguren
 *    Vicente Castillo
 *    Troy Davidson
 ************************************************************************/

#pragma once

#include <cassert>     // for ASSERT
#include <iostream>    // for NULL

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <class T>
class Node
{
public:

   //
   // Construct
   //

   Node()
   {
       pPrev = nullptr;
       pNext = nullptr;
   }
   Node(const T& data) : data(data), pPrev(nullptr), pNext(nullptr) {}

   Node(      T && data)
   {
       this->data = std::move(data);
       pPrev = nullptr;
       pNext = nullptr;
   }

   //
   // Member variables
   //

   T data;                 // user data
   Node <T> * pNext;       // pointer to next node
   Node <T> * pPrev;       // pointer to previous node
};

/***********************************************
 * COPY
 * Copy the list from the pSource and return
 * the new list
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline Node <T> * copy(const Node <T> * pSource)
{
    if (pSource)
    {
        Node <T>* pDestination = new Node<T>(pSource->data);
        const Node <T>* pSrc = pSource;
        Node <T>* pDes = pDestination;

        for (; pSrc; pSrc = pSrc->pNext)
        {
            pDes = insert(pDes, pSrc->data, true);
        }
        return pDestination;
    }
    else
    {
        return NULL;
    }
}

/***********************************************
 * Assign
 * Copy the values from pSource into pDestination
 * reusing the nodes already created in pDestination if possible.
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline void assign(Node <T> * & pDestination, const Node <T> * pSource)
{
    const Node <T>* pSrc = pSource;
    Node <T>* pDes = pDestination;
    while (pSrc != NULL && pDes != NULL)
    {
        pDes->data = pSrc->data;
        pDes = pDes->pNext;
        pSrc = pSrc->pNext;
    }

    if (pSrc != NULL)
    {
        while (pSrc != NULL)
        {
            pDes = insert(pDes, pSrc->data, true);
            if (pDestination == NULL)
            {
                pDestination = pDes;
            }
            pSrc = pSrc->pNext;
        }
    }


    if (pSource != NULL && pDestination != NULL)
    {
        bool setToNull = false;
        if (pDes->pPrev != NULL)
        {
            pDes->pPrev->pNext = NULL;

        }
        else
        {
            setToNull = true;
        }
        delete pDes;

        if (setToNull)
        {
            pDestination = NULL;
        }
    }
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(Node <T>* &pLHS, Node <T>* &pRHS)
{
    Node <T>* temp = pLHS;
    pLHS = pRHS;
    pRHS = temp;

}

/***********************************************
 * REMOVE
 * Remove the node pSource in the linked list
 *   INPUT  : the node to be removed
 *   OUTPUT : the pointer to the parent node
 *   COST   : O(1)
 **********************************************/
template <class T>
inline Node <T> * remove(const Node <T> * pRemove)
{
    if (pRemove == nullptr)
    {
        return NULL;
    }

    if (pRemove->pPrev)
    {
        pRemove->pPrev->pNext = pRemove->pNext;
    }
    if (pRemove->pNext)
    {
        pRemove->pNext->pPrev = pRemove->pPrev;
    }

    Node<T>* pReturn;
    if (pRemove->pPrev)
    {
        pReturn = pRemove->pPrev;
    }
    else
    {
        pReturn = pRemove->pNext;
    }
    delete pRemove;
    return pReturn;
}

/**********************************************
 * INSERT
 * Insert a new node the the value in "t" into a linked
 * list immediately before the current position.
 *   INPUT   : t - the value to be used for the new node
 *             pCurrent - a pointer to the node before which
 *                we will be inserting the new node
 *             after - whether we will be inserting after
 *   OUTPUT  : return the newly inserted item
 *   COST    : O(1)
 **********************************************/
template <class T>
inline Node <T> * insert(Node <T> * pCurrent,
                  const T & t,
                  bool after = false)
{
    Node <T> * pNew = new Node<T>(t);

    if(pCurrent != NULL && after == false)
    {
        pNew->pNext = pCurrent;
        pNew->pPrev = pCurrent->pPrev;
        pCurrent -> pPrev = pNew;
        if(pNew->pPrev)
        {
            pNew->pPrev->pNext = pNew;
        }
    }
    if(pCurrent != NULL && after == true)
    {
        pNew->pPrev = pCurrent;
        pNew->pNext = pCurrent->pNext;
        pCurrent->pNext = pNew;
        if (pNew->pNext)
        {
            pNew->pNext->pPrev = pNew;
        }
    }

   return pNew;
}

/******************************************************
 * FIND
 * Find a given node in an unsorted linked list.  Return
 * a pointer to the node if it is found, NULL otherwise.
 *  INPUT   : a pointer to the head of the linked list
 *            the value to be found
 *  OUTPUT  : a pointer to the node if it is found
 *  COST    : O(n)
 ********************************************************/
template <class T>
inline size_t size(const Node <T> * pHead)
{
    if (pHead == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + size(pHead->pNext);
    }
}

/***********************************************
 * DISPLAY
 * Display all the items in the linked list from here on back
 *    INPUT  : the output stream
 *             pointer to the linked list
 *    OUTPUT : the data from the linked list on the screen
 *    COST   : O(n)
 **********************************************/
template <class T>
inline std::ostream & operator << (std::ostream & out, const Node <T> * pHead)
{
    for (; pHead != NULL; pHead = pHead->pNext)
        std::cout << pHead->data << " ";
    std::cout << std::endl;
   return out;
}

/*****************************************************
 * CLEAR
 * Free all the data currently in the linked list
 *   INPUT   : pointer to the head of the linked list
 *   OUTPUT  : pHead set to NULL
 *   COST    : O(n)
 ****************************************************/
template <class T>
inline void clear(Node <T> * & pHead)
{
    while (pHead != NULL)
    {
        Node<T>* pDelete = pHead;
        pHead = pHead->pNext;
        delete pDelete;
    }
}



