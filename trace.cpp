#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <memory>

#include <unordered_map> 
#include <dlfcn.h> //dladdr
#include <cxxabi.h>
#include <x86intrin.h>
 

namespace perftracer {

struct profile_data
{
  unsigned long long start;
  unsigned long long sum;
  unsigned int nested_level;
  void* func;
};
std::unordered_map<void*,profile_data> *profile_data_collector; 

void
__attribute__ ((constructor))
perftrace_start(void)
{
  fprintf(stderr, "===> Performance tracing Enabled!\n");

  // We need to have unordered_map dynamically allocated as static unordered_map would
  // be destroyed before trace_end function is called
  profile_data_collector = new std::unordered_map<void*,profile_data>;  
}
 
void
__attribute__ ((destructor))
perftrace_stop(void)
{
  //TODO: Detect TSC clock based on /proc/cpuinfo
  const unsigned long long TSC = 2000000000; //TSC 2.0GHz
  //TODO: print elements in sorted order

  fprintf(stderr, "Inclusive flat profile:\n");
  // Process all collected data 
  for(auto& profile_data_element : *profile_data_collector) {
    Dl_info info;
    if( dladdr(profile_data_element.second.func, &info) != 0) {
      int status = 0;
      char* outbuffer = abi::__cxa_demangle( info.dli_sname,
                                             NULL,
                                             NULL,
                                             &status); 		
      switch(status) {
        case -1:
          fprintf(stderr, "===> Error demangling %s\n (Memory allocation error)",info.dli_sname);
          break;
        case -2:  // C (not demangled function names) function will get here
                  // we just make a copy of recorded name
        {
          outbuffer = reinterpret_cast<char*>(malloc(std::strlen(info.dli_sname)+1));
          std::strcpy(outbuffer,info.dli_sname);
        }
        case 0:
        {
          float execution_time = (profile_data_element.second.sum*1000)/static_cast<float>(TSC);
          fprintf(stderr, "   %fms %s\n",execution_time,outbuffer);
          free(outbuffer);
        }
        break;
        default:
          fprintf(stderr, "===> Error demangling %s\n ",info.dli_sname);
          break;
      }  
    } else {
        fprintf(stderr, "===> Error resolving address: %p\n", profile_data_element.second.func);
    }
  }
  delete profile_data_collector;
  profile_data_collector = nullptr;
}
};

#ifdef __cplusplus
extern "C" {
#endif
void
__cyg_profile_func_enter (void *func,  void *caller)
{


  // TODO: what about recursive call to given function????
  std::unordered_map<void*,perftracer::profile_data>::iterator it;
  it = perftracer::profile_data_collector->find(func);
  // If there is an entry for given function then use it
  // if not then add a new one
  if( it == perftracer::profile_data_collector->end()) {
    perftracer::profile_data_collector->insert(std::pair<void*,perftracer::profile_data>(func,{__rdtsc(),0,1,func})); 
  } else {
    // For nested calls we do nothing
    if((*it).second.nested_level == 0) {
      (*it).second.start = __rdtsc();
      (*it).second.nested_level = 1;
    } else {
      ++(*it).second.nested_level;
    }
  }
}
 
void
__cyg_profile_func_exit (void *func, void *caller)
{
  Dl_info info;
  std::unordered_map<void*,perftracer::profile_data>::iterator it;
  it = perftracer::profile_data_collector->find(func);
  // There has to be entry already. If not then it is a perftracer bug!
  assert(it != perftracer::profile_data_collector->end());
  // Entry routine should 

  if((*it).second.nested_level == 1) {
    (*it).second.sum += __rdtsc() - (*it).second.start;
  } 
  --(*it).second.nested_level;
}
#ifdef __cplusplus
};
#endif
