#include <iostream>
#include <stdlib.h>
#include <proc/sysinfo.h>
#include <string.h>
#include <deque>
#include <queue>
#include <unistd.h>

#include <cstdio>
#include <ctime>


using namespace std;
/*
* Author: David Hamner
*	Based on ballooner by Robert Metzger (metzgerr@web.de)
*   https://github.com/rmetzger/dynamic-ballooner
* The purpose of this tool is to allocate n GB of main memory
* on a linux machine. 
*/

using namespace std;

struct mem 
{
  int mb_cached;
  int mb_buffers;
  int mb_free;
};

mem m_info;

// a chunk of allocated memory
struct chunk
{
  void* ptr;
  int size;
};

void update_m_info() 
{
  meminfo();
  m_info.mb_cached = kb_main_cached/1024;
  m_info.mb_buffers = kb_main_buffers/1024;
  m_info.mb_free = kb_main_free/1024;
}


int main(int argc, char* argv[])
{
  std::clock_t start;
  double duration;
  start = std::clock();
  char key;

  // info from /proc/meminfo
  m_info.mb_cached = 0;
  m_info.mb_buffers = 0;
  m_info.mb_free = 0;
  // the amount of mem the user wants for the cache.
  int desiredCacheSize = -1;

  deque<chunk>*  allocated_memory = new deque<chunk>;

  if(argc <= 1) 
  {
    cout << "Usage: memorytrap <desiredSizeGigabyte>\n";
  } 
  else 
  {
    desiredCacheSize = strtol(argv[1], NULL, 10) * 1024;
    if(desiredCacheSize <= 0) 
    {
      cout << "Values equal or lower to zero are not supported";
      return 1;
    }
      update_m_info();
      // we need to allocate memory
      int alloc_mb = desiredCacheSize; // edit this param for finer alloc granularity
      long amount = (long)alloc_mb*1024*1024;
      cout << "Allocating " << alloc_mb << " MB \n";
      void * buffer =  malloc ( amount );
      memset(buffer, 1, amount);
      chunk newAll;
      newAll.ptr = buffer;
      newAll.size = alloc_mb;
      allocated_memory->push_front(newAll);
      update_m_info();
      duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
      cout << "Done\nTime: " << duration << "\nPress 'Enter' to release memory: ";
      cin.get(key);
      //cin >> key;
  }
}
