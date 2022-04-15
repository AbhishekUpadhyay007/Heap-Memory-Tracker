/**************************************************************************************
 **     FILENAME           :    trackAlloc.cpp
 **
 **     DESCRIPTION        :    To track newly allocated memory records 
 **
 **
 ************************************************************************************/

/************************************************************************************
 *                               HEADER FILES
 ***********************************************************************************/

#ifndef _TRACK_ALLOC_
#define _TRACK_ALLOC_

#include <bits/stdc++.h>
#include "../model/Alloc.cpp"
#include "LinkedList.cpp"

using namespace std;

LinkedList<Alloc *> alloc_list; // Allocation list

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
/***********************************************************************************
 **     FUNCTION NAME    :   trackAlloc
 **
 **     DESCRIPTION      :   Keep the user updated towards the memory allocation
 **
 **     PARAMETERS       :   size_t size, void *ptr
 **
 **     RETURNS          :   nothing
 **********************************************************************************/
void trackAlloc(size_t size, void *ptr)
{
    std::time_t result = std::time(nullptr);

    cout << "INFO: new is called for " << size << " bytes of memory"
         << " at timestamp: " << std::asctime(std::localtime(&result));
}

/***********************************************************************************
 **     FUNCTION NAME    :   appendAllocNode
 **
 **     DESCRIPTION      :   Allocate the reference to the newly created memory node
 **                          and handle exceptions
 **
 **     PARAMETERS       :   size_t size, void *ptr
 **
 **     RETURNS          :   nothing
 **********************************************************************************/
int appendAllocNode(void *ptr, size_t size)
{
    try
    {
        Alloc *al = (Alloc *)malloc(sizeof(Alloc));
        if (al == NULL)
        {
            DEBUG_LOG(3, "Memory not allocated, bad alloc occurs");
            throw bad_alloc();
        }
        al->setMemPtr(ptr);
        al->totalByteSize += size;
        al->no_allocs++;
        al->setAllocSize(size);
        alloc_list.push(al);
    }
    catch (std::exception &e)
    {
        DEBUG_LOG(3, e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/***********************************************************************************
 **     FUNCTION NAME    :   displayAllocationDetails
 **
 **     DESCRIPTION      :   Creates a query interface for user for checking memory allocations records
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   nothing
 **********************************************************************************/
void displayAllocationDetails()
{
    char ch;
    string str;
    do
    {
        cout << endl
             << "******************* MENU FOR ALLOCATION DETAILS *****************" << endl;
        cout << "a.Allocation size(bytes)\nb.Total number of allocations\nc.Total allocation size(bytes)\nd.Show all(bytes)\n " << endl;
        cout << "\nEnter a choice: ";
        cin >> str;
        if (str.size() > 1)
        {
            ch = 'k';
        }
        else
        {
            ch = str[0];
        }
        switch (ch)
        {
        case 'a':
        case 'A':
            cout << endl;
            alloc_list.getTotalHeapAllocatedSize();
            break;

        case 'b':
        case 'B':
            cout << endl;
            cout << "Total number of allocations: " << Alloc::no_allocs << endl;
            break;

        case 'c':
        case 'C':
            cout << endl;
            cout << "Total allocation size(bytes): " << Alloc::totalByteSize << endl;
            break;
        case 'd':
        case 'D':
            cout << endl;
            alloc_list.getTotalHeapAllocatedSize();
            cout << endl;
            cout << "Total number of allocations: " << Alloc::no_allocs << endl;
            cout << endl;
            cout << "Total allocation size(bytes): " << Alloc::totalByteSize << endl;
            break;
        default:
            DEBUG_LOG(2, "Invalid input");
            break;
        }

        cout << "\nDo you want to continue:? (y/n)" << endl;
        cin >> ch;

    } while (ch == 'Y' || ch == 'y');
}

/***********************************************************************************
 **     FUNCTION NAME    :   deleteAllocList
 **
 **     DESCRIPTION      :   at the end of execution deletes the allocation list(used for keeping memory track)
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   nothing
 **********************************************************************************/
void deleteAllocList()
{
    alloc_list.clearList();
    cout << endl
         << "******************* ALLOCATION LIST IS EMPTIED ********************" << endl;
}

#endif
