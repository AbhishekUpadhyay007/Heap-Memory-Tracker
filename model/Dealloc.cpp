#ifndef _DEALLOC_
#define _DEALLOC_

#include <iostream>

/**********************************************************************************
 **     CLASS NAME       :   DeAlloc
 **
 **     DESCRIPTION      :   The class has following data: void *mem_ptr, size_t size,
                             static size_t totalDeAllocByteSize, static int no_deAllocs
 **********************************************************************************/

class DeAlloc
{
private:
    void *mem_ptr;
    size_t size;

public:
    static size_t totalDeAllocByteSize;
    static int no_deAllocs;

    //Paramaterized constructor
    DeAlloc(void *ptr)
    {
        totalDeAllocByteSize += sizeof(DeAlloc);
        mem_ptr = ptr;
        no_deAllocs++;
    }

    //Returns the meory reference
    void *getMemPointer()
    {
        return mem_ptr;
    }
    //Set the memory reference
    void setMemPtr(void *ptr)
    {
        this->mem_ptr = ptr;
    }
    //Set the deallocation size
    void setDeAllocSize(size_t size)
    {
        this->size = size;
    }
    // Returns deallocation size
    size_t getDeAllocSize()
    {
        return size;
    }
};

// Setting default values of static variables
size_t DeAlloc::totalDeAllocByteSize = 0;
int DeAlloc::no_deAllocs = 0;

#endif