#ifndef _ALLOC_
#define _ALLOC_

#include <iostream>
/**********************************************************************************
 **     CLASS NAME       :   Alloc
 **
 **     DESCRIPTION      :   The class has following data: void *mem_ptr, size_t size, 
                             static size_t totalDeAllocByteSize, static int no_deAllocs
 **********************************************************************************/
class Alloc
{
private:
    void *mem_ptr;
    size_t size;
public:
    static size_t totalByteSize;
    static int no_allocs;

    //Paramaterized constructor
    Alloc(void *ptr)
    {
        totalByteSize += sizeof(Alloc);
        mem_ptr = ptr;
        no_allocs++;
    }
    //Returns memory reference
    void *getMemPointer()
    {
        return mem_ptr;
    }
    //Set the memory reference
    void setMemPtr(void *ptr)
    {
        this->mem_ptr = ptr;
    }
    //Set the allocation size
    void setAllocSize(size_t size)
    {
        // std::cout << size << std::endl;
        this->size = size;
    }
    //Returns the allocated size
    size_t getAllocSize()
    {
        return size;
    }
};

//Setting default values of static variables
size_t Alloc::totalByteSize = 0;
int Alloc::no_allocs = 0;

#endif