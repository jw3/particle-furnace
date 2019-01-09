#pragma once

#include <list>

template<typename T>
struct Buffer
{
   Buffer(int capacity) : max(capacity) {}

   void receive(const T& t) {
      add(t);
   }

   template<class... A>
   int add(A&& ... args) {
      return add(Time.now(), std::forward<A>(args)...);
   }

   template<class... A>
   int add(time_t t, A&& ... args) {
      bool full = sz + 1 >= max;
      if(full) buff.pop_front(); else ++sz;
      buff.push_back(
            std::make_pair(
                  T(std::forward<A>(args)...), t
            )
      );
      return full ? -1 : buff.size();
   }

private:
   int sz;
   int max;
   std::list<std::pair<T, time_t>> buff;
};
