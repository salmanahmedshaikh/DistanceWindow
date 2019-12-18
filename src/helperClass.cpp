#include "helperClass.h"
#include <chrono>


helperClass::helperClass()
{
    //ctor
}

helperClass::~helperClass()
{
    //dtor
}

uint64_t helperClass::timeSinceEpochMillisec()
{
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

uint64_t helperClass::timeSinceEpochMicrosec()
{
  using namespace std::chrono;
  return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}
