/**************************************************************************************
 **     FILENAME           :    LinkedList.cpp
 **
 **     DESCRIPTION        :    ADT structure for keeping record for memory allocations/deallocations 
 **
 **
 ************************************************************************************/
#ifndef _LinkedList_2_
#define _LinkedList_2_

#include <iostream>
// Header File including all string functions
#include <string>
#include "../model/Alloc.cpp"
#include "../model/Dealloc.cpp"

using namespace std;

 /***********************************************************************************
 **     MACRO NAME       :   DEBUG_LOG
 **
 **     DESCRIPTION      :   displays debug log messages  with 4 levels
 **
 **     PARAMETERS       :   LOG_VAL, MSG
 **********************************************************************************/
#define DEBUG_LOG(LOG_VAL, MSG)             \
    if (LOG_VAL == 1)                       \
    {                                       \
        cout << "INFO: " << MSG << endl;    \
    }                                       \
    if (LOG_VAL == 2)                       \
    {                                       \
        cout << "WARNING: " << MSG << endl; \
    }                                       \
    if (LOG_VAL == 3)                       \
    {                                       \
        cout << "FATAL: " << MSG << endl;   \
    }                                       \
    if (LOG_VAL == 4)                       \
    {                                       \
        cout << "DEBUG: " << MSG << endl;   \
    }

// Class
// To represent LinkedList using template by class
// taking class in template
template <class T>
class LinkedList
{
    // Public access modifier
public:
    // Empty constructor
    LinkedList();

    // To add element to LinkedList which can be any type
    // using LinkedList push() operation
    int push(T k);

    // To remove head element from LinkedList
    // using pop() operation
    void pop();
    void printList();

    // To print head element in LinkedList
    // using peek() method
    T headElement();

    // To get the size of linkedlist
    int getSize();

    // To check whether LinkedList is full
    // using isFull() method
    bool isFull();

    // To check whether LinkedList is empty
    // using isEmpty() method
    bool isEmpty();

    //Generic function for to get total heap 
    //allocation/deallocation size
    int getTotalHeapAllocatedSize();

    //Generic function for to clear list
    void clearList();

    T allocs_ptr;
    size_t t_alloc_size;

private:
    // Taking data member head
    LinkedList *head = NULL;
    LinkedList *curr = NULL;
    LinkedList *next = NULL;
    int size = 0;
    // Initialising LinkedList(array) of given size
};


/***********************************************************************************
 **     FUNCTION NAME    :   getSize
 **
 **     DESCRIPTION      :   generic function to return size of Linked list
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   size
 **********************************************************************************/
template <class T>
int LinkedList<T>::getSize()
{
    return size;
}

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;
}

// Method 7
// To add element element k to LinkedList

/***********************************************************************************
 **     FUNCTION NAME    :   getTotalHeapAllocatedSize
 **
 **     DESCRIPTION      :   generic function for Alloc * to get total heap allocation size
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   EXIT_SUCESS/EXIT_FAILURE
 **********************************************************************************/
template <>
int LinkedList<Alloc *>::getTotalHeapAllocatedSize()
{
    if (isEmpty())
    {
        DEBUG_LOG(2, "Allocation list in empty");
    }
    else
    {
        LinkedList *temp = head;
        while (temp != NULL)
        {
            cout << "INFO: [Allocation at address] " << temp->allocs_ptr->getMemPointer()
                 << " is done of size " << temp->allocs_ptr->getAllocSize() << " bytes." << endl;
            temp = temp->next;
        }
    }
    return EXIT_SUCCESS;
}

/***********************************************************************************
 **     FUNCTION NAME    :   getTotalHeapAllocatedSize
 **
 **     DESCRIPTION      :   generic function for DeAlloc * to get total heap deallocation size
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   EXIT_SUCESS/EXIT_FAILURE
 **********************************************************************************/
template <>
int LinkedList<DeAlloc *>::getTotalHeapAllocatedSize()
{
    if (isEmpty())
    {
        DEBUG_LOG(2, "Deallocation list in empty");
    }
    else
    {
        LinkedList *temp = head;
        while (temp != NULL)
        {
            cout << "INFO: [Deallocation at address] " << temp->allocs_ptr->getMemPointer()
                 << " is done of size " << temp->allocs_ptr->getDeAllocSize() << " bytes." << endl;
            temp = temp->next;
        }
    }
    return EXIT_SUCCESS;
}

/***********************************************************************************
 **     FUNCTION NAME    :   clearList
 **
 **     DESCRIPTION      :   generic function to clear the list
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   none
 **********************************************************************************/

template <class T>
void LinkedList<T>::clearList()
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        LinkedList *current = head;
        LinkedList *next = NULL;

        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
            size--;
        }

        head = NULL;
    }
}

/***********************************************************************************
 **     FUNCTION NAME    :   push
 **
 **     DESCRIPTION      :   generic function to push the data in linked list
 **
 **     PARAMETERS       :   (T k)
 **
 **     RETURNS          :   EXIT_FAILURE/EXIT_SUCESS
 **********************************************************************************/
template <class T>
int LinkedList<T>::push(T k)
{
    // Now, adding element to LinkedList
    if (head == NULL)
    {
        try
        {
            head = (LinkedList *)malloc(sizeof(LinkedList));
            if (head == NULL)
            {
                throw bad_alloc();
            }
            head->allocs_ptr = k;
            curr = head;
            size++;
        }
        catch (const std::bad_alloc &e)
        {
            DEBUG_LOG(3, e.what());
            return EXIT_FAILURE;
        }
    }
    else
    {
        try
        {
            curr->next = (LinkedList *)malloc(sizeof(LinkedList));
            if (curr == NULL)
            {
                throw bad_alloc();
            }
            curr = curr->next;
            curr->allocs_ptr = k;
            curr->next = NULL;
            size++;
        }
        catch (const std::exception &e)
        {
            DEBUG_LOG(3, e.what());
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

// Method 8
// To check if the LinkedList is empty
/***********************************************************************************
 **     FUNCTION NAME    :   isEmpty
 **
 **     DESCRIPTION      :   generic function to check if list is empty
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   0/1
 **********************************************************************************/
template <class T>
bool LinkedList<T>::isEmpty()
{
    if (head == NULL)
        return 1;
    else
        return 0;
}

/***********************************************************************************
 **     FUNCTION NAME    :   isEmpty
 **
 **     DESCRIPTION      :   generic function to print list
 **
 **     PARAMETERS       :   size_t size, void *ptr
 **
 **     RETURNS          :   0/1
 **********************************************************************************/
template <class T>
void LinkedList<T>::printList()
{
    if (isEmpty())
    {
        DEBUG_LOG(1, "Allocation list is empty!");
    }
    else
    {
        LinkedList *temp = head;
        while (temp != NULL)
        {
            cout << temp->allocs_ptr << endl;
            temp = temp->next;
        }
    }
}

#endif
