/**************************************************************************************
 **     FILENAME           :    track.cpp
 **
 **     DESCRIPTION        :    To track new and delete call 
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
#ifndef _TRACK_
#define _TRACK_

#include <iostream>
#include <memory>
#include "trackAlloc.cpp"
#include "trackDealloc.cpp"

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

static char choice;
 /***********************************************************************************
 **     FUNCTION NAME    :   heap_track_init
 **
 **     DESCRIPTION      :   Initializes the program and asks user to disable/enable
 **                          tracker
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   Nothing
 **********************************************************************************/
void heap_track_init(void)
{
    cout << endl
         << "******************* PROGRAM STARTED *********************" << endl
         << endl;
iferror:

    cout << "Do You want to Enable heap track ? (y/n): ";
    string str;
    cin >> str;

    if (str.size() > 1)
    {
        DEBUG_LOG(3, "Invalid choice");
        goto iferror;
    }
    if (str[0] == 'Y' || str[0] == 'y' || str[0] == 'N' || str[0] == 'n')
    {
        choice = str[0];
    }
    else
    {
        DEBUG_LOG(3, "Invalid choice");
        goto iferror;
    }
}
 /***********************************************************************************
 **     FUNCTION NAME    :   operator new
 **
 **     DESCRIPTION      :   Overrides new operator and call trackAlloc and 
 **                          appendAllocNode functions
 **
 **     PARAMETERS       :   size
 **
 **     RETURNS          :   Nothing
 **********************************************************************************/
void *operator new(size_t size)
{
    void *ptr;
    try
    {
        ptr = malloc(size);
        if (ptr == NULL)
        {
            throw bad_alloc();
        }

        if (choice == 'n' || choice == 'N')
        {
            return ptr;
        }

        trackAlloc(size, ptr);
        appendAllocNode(ptr, size);
    }
    catch (const std::exception &e)
    {
        DEBUG_LOG(4, e.what());
    }

    return ptr;
}
 /***********************************************************************************
 **     FUNCTION NAME    :   operator new[]
 **
 **     DESCRIPTION      :   Overrides new[] operator for array of objects and call
 **                          trackAlloc and appendAllocNode functions                         
 **
 **     PARAMETERS       :   size
 **
 **     RETURNS          :   Nothing
 **********************************************************************************/
void *operator new[](size_t size)
{
    void *ptr;
    try
    {
        ptr = malloc(size);
        if (ptr == NULL)
        {
            throw bad_alloc();
        }
        if (choice == 'n' || choice == 'N')
        {
            return ptr;
        }
        trackAlloc(size, ptr);
        appendAllocNode(ptr, size);
    }
    catch (const std::exception &e)
    {
        DEBUG_LOG(4, e.what());
    }
    return ptr;
}
 /***********************************************************************************
 **     FUNCTION NAME    :   operator delete
 **
 **     DESCRIPTION      :   Overrides delete operator and call trackDeAlloc and 
 **                          appendDeAllocNode functions
 **
 **     PARAMETERS       :   ptr,size
 **
 **     RETURNS          :   Nothing
 **********************************************************************************/
void operator delete(void *ptr, size_t size)
{
    if (choice == 'N' || choice == 'n')
    {
        free(ptr);
        return;
    }

    trackDeAlloc(ptr, size);
    appendDeAllocNode(ptr, size);
    free(ptr);
}
 /***********************************************************************************
 **     FUNCTION NAME    :   operator delete[]
 **
 **     DESCRIPTION      :   Overrides delete operator for array of objects and call
 **                          trackDeAlloc and appendDeAllocNode functions                          
 **
 **     PARAMETERS       :   ptr,size
 **
 **     RETURNS          :   Nothing
 **********************************************************************************/
void operator delete[](void *ptr, size_t size)
{
    cout << "Inside delete[]" << endl;
    // if (choice == 'N' || choice == 'n')
    // {
    //     free(ptr);
    //     return;
    // }

    // trackDeAlloc(ptr, size);
    // appendDeAllocNode(ptr, size);
    free(ptr);
}
 /***********************************************************************************
 **     FUNCTION NAME    :   GetTotalAllocation
 **
 **     DESCRIPTION      :   Prints  Total memory allocated in bytes                         
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   Nothing
 **********************************************************************************/
void GetTotalAllocation(void)
{
    cout << "a. Total memory allocated (bytes): " << Alloc::totalByteSize << endl;
}
 /***********************************************************************************
 **     FUNCTION NAME    :   GetTotalFreed
 **
 **     DESCRIPTION      :   Prints Total memory freed in bytes                        
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   Nothing
 **********************************************************************************/
void GetTotalFreed(void)
{
    cout << "b. Total memory freed (bytes): " << DeAlloc::totalDeAllocByteSize << endl;
}
 /***********************************************************************************
 **     FUNCTION NAME    :   GetMemoryInUse
 **
 **     DESCRIPTION      :   Prints  Memory currently in use in bytes                        
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   Nothing
 **********************************************************************************/
void GetMemoryInUse(void)
{
    cout << "c. Memory currently in use (bytes): " << (Alloc::totalByteSize - DeAlloc::totalDeAllocByteSize) << endl;
}

 /***********************************************************************************
 **     FUNCTION NAME    :   total_heap_usage_statistics
 **
 **     DESCRIPTION      :   Calls GetTotalAllocation(),GetTotalFreed(),GetMemoryInUse()                  
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   Nothing
 **********************************************************************************/
void total_heap_usage_statistics(void)
{
    cout << endl;
    DEBUG_LOG(1, "Interface to dump of total heap usage statistics");
    cout << endl;
    GetTotalAllocation();
    GetTotalFreed();
    GetMemoryInUse();
}
 /***********************************************************************************
 **     FUNCTION NAME    :   heap_track_stats
 **
 **     DESCRIPTION      :   Displays main menu if tracker is enabled                  
 **
 **     PARAMETERS       :   void
 **
 **     RETURNS          :   Nothing
 **********************************************************************************/
void heap_track_stats(void)
{
    if (choice == 'N' || choice == 'n')
    {
        DEBUG_LOG(1, "Heap tracker is disabled");
        cout << endl
             << "********************* PROGRAM ENDS ***********************" << endl;
        return;
    }
    char ch;
    string str;

    do
    {
        cout << endl
             << "********************* DISPLAY MENU STARTS **********************" << endl;
        cout << "\na. Display Allocation Details" << endl
             << "b. Display Deallocation Details" << endl
             << "c. Display heap usage statistics" << endl
             << endl;
        cout << "Enter choice: ";
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
            displayAllocationDetails();
            break;

        case 'b':
        case 'B':
            displayDeAllocationDetails();
            break;
        case 'c':
        case 'C':
            total_heap_usage_statistics();
            break;
        default:
            DEBUG_LOG(3, "Invalid choice");
            break;
        }
        cout << "\nDo you want to see menu again?(y/n)" << endl;
        cin >> str;
        if (str.size() > 1)
        {
            ch = 'k';
        }
        else
        {
            ch = str[0];
        }
    } while (ch == 'Y' || ch == 'y');
    cout << endl
         << "********************* DISPLAY MENU ENDS **********************" << endl;
    deleteAllocList();
    deleteDeallocList();
}

#endif
