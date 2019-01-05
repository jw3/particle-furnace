#pragma once

#include <list>

template<typename T>
struct Buffer
{
   Buffer(int capacity) : max(capacity) {}

   void receive(const T& t) {
      add(t);
   }

   int add(const T& t) {
      bool full = sz + 1 >= max;
      if(full) buff.pop_front(); else ++sz;
      buff.push_back(t);
      return full ? -1 : buff.size();
   }

private:
   int sz;
   int max;
   std::list<T> buff;
};
