#ifndef _HEADER_
#define _HEADER_

#include <iostream>
void heap_track_init(void);
void heap_track_stats(void);
void *operator new(size_t);
void *operator new[](size_t);
void operator delete(void *, size_t);

#endif
