//
// Created by richard may clarkson on 11/12/2022.
//

#ifndef GLENGINE_BUF_H
#define GLENGINE_BUF_H

#include "global.h"

namespace piqu
{
  template<typename T>
  struct buf_t
  {
    u32 cap;
    u32 handle;
    u32 head;
    u32 size;
    T* ptr;

    buf_t(u32 cap, u32 size) : cap(cap), head(0), ptr(new T[size]), size(size)
    {
      glGenBuffers(1, &handle);
    }

    void reserve(u32 newSize)
    {
      bool resized = false;
      u32 prevSize = size;
      while (newSize > size)
      {
        size *= 2;
        resized = true;
      }
      if (resized)
      {
        T* newItems = new T[size];
        copy(ptr, ptr + prevSize, newItems);
        delete[] ptr;
        ptr = newItems;
      }
    }

    void put(const T& item)
    {
      reserve(head + 1);
      ptr[head] = item;
      head++;
    }

    void put(T* items, u32 amt)
    {
      reserve(head + amt);
      copy(items, items + amt, ptr + head);
      head += amt;
    }

    void put(const T* items, u32 amt)
    {
      reserve(head + amt);
      copy(items, items + amt, ptr + head);
      head += amt;
    }

    inline void upload()
    {
      use();
      glBufferData(cap, sizeof(T) * head, ptr, GL_DYNAMIC_DRAW);
    }

    inline void clear()
    {
      head = 0;
    }

    inline void use()
    {
      glBindBuffer(cap, handle);
    }
  };
}

#endif //GLENGINE_BUF_H
