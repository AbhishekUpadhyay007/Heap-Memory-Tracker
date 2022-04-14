/**************************************************************************************
 **     FILENAME           :    trackDealloc.cpp
 **
 **     DESCRIPTION        :    To track newly deallocated memory records 
 **
 **     REVISION HISTORY   :
 **
 **     DATE                NAME              REFERENCE               REASON
 **     --------------------------------------------------------------------
 **    11 April 2022       Group-2      Sprint-2          Sprint-2 Submission
 **
 **     Copyright Ã‚Â© 2022 Capgemini Group  All Rights Reserved
 **
 ************************************************************************************/

/************************************************************************************
 *                               HEADER FILES
 ***********************************************************************************/
#ifndef _TRACK_DEALLOC_
#define _TRACK_DEALLOC_

#include <bits/stdc++.h>
#include "../model/Dealloc.cpp"
#include "LinkedList.cpp"

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

LinkedList<DeAlloc *> DeAlloc_list; // Deallocation list


/***********************************************************************************
 **     FUNCTION NAME    :   trackDeAlloc
 **
 **     DESCRIPTION      :   Keep the user updated towards the memory deallocation
 **
 **     PARAMETERS       :   size_t size, void *ptr
 **
 **     RETURNS          :   nothing
 **********************************************************************************/
void trackDeAlloc(void *ptr, size_t size)
{
    std::time_t result = std::time(nullptr);
    cout << "INFO: delete is called for " << size << " bytes of memory "
         << "at timestamp: " << std::asctime(std::localtime(&result));
}

/***********************************************************************************
 **     FUNCTION NAME    :   appendDeAllocNode
 **
 **     DESCRIPTION      :   Keeps the reference to the deleted memory by accessing the size
 **
 **     PARAMETERS       :   size_t size, void *ptr
 **
 **     RETURNS          :   nothing
 **********************************************************************************/

int appendDeAllocNode(void *ptr, size_t size)
{

    try
    {
        DeAlloc *dealloc = (DeAlloc *)malloc(sizeof(DeAlloc));
        if (dealloc == NULL)
        {
            DEBUG_LOG(3, "Memory not allocated, bad alloc occurs");
            throw bad_alloc();
        }
        dealloc->setMemPtr(ptr);
        dealloc->totalDeAllocByteSize += size;
        dealloc->no_deAllocs++;
        dealloc->setDeAllocSize(size);
        DeAlloc_list.push(dealloc);
    }

    catch (bad_alloc &e)
    {
        DEBUG_LOG(4, e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/***********************************************************************************
 **     FUNCTION NAME    :   displayDeAllocationDetails
 **
 **     DESCRIPTION      :   Creates a query interface for user for checking memory deallocations records
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   nothing
 **********************************************************************************/
void displayDeAllocationDetails()
{
    char ch;
    string str;
    do
    {
        cout << "\n******************* MENU FOR DEALLOCATION DETAILS *****************" << endl;
        cout << "a.Deallocation size(bytes)\nb.Total number of deallocations\nc.Total deallocation size(bytes)\nd.Show all(bytes)\n " << endl;
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
            DeAlloc_list.getTotalHeapAllocatedSize();
            break;

        case 'b':
        case 'B':
            cout << endl;
            cout << "Total Number of deallocations: " << DeAlloc::no_deAllocs << endl;
            break;

        case 'c':
        case 'C':
            cout << endl;
            cout << "Total deallocation size(bytes): " << DeAlloc::totalDeAllocByteSize << endl;
            break;
        case 'd':
        case 'D':
            cout << endl;
            DeAlloc_list.getTotalHeapAllocatedSize();
            cout << "\nTotal Number of deallocations: " << DeAlloc::no_deAllocs << endl;
            cout << "\nTotal deallocation size(bytes): " << DeAlloc::totalDeAllocByteSize << endl;
            break;
        default:
            DEBUG_LOG(2, "Invalid input");
            break;
        }
        cout << "\nDo you want to continue?(y/n)" << endl;
        cin >> ch;
        // getchar();

    } while (ch == 'Y' || ch == 'y');
}

/***********************************************************************************
 **     FUNCTION NAME    :   deleteDeallocList
 **
 **     DESCRIPTION      :   at the end of execution deletes the allocation list(used for keeping memory track)
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   nothing
 **********************************************************************************/
void deleteDeallocList()
{
    cout << endl
         << "******************* DEALLOCATION LIST IS EMPTIED ********************" << endl;
    DeAlloc_list.clearList();
}

#endif
