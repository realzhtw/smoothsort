#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

#include "leonardo.h"

typedef unsigned long ulong;

template<class I>
void sift(I top, leo_iter<long> l)
{
  while (*l > 1) {
    long cur = *l;
    --l;
    I child = top + (cur - *l);
    if (*(top + 1) < *child) {
      child = top + 1;
      --l;
    }
    if (*child >= *top)
      break;
    std::swap(*top, *child);
    top = child;
  }
}

void normalize(ulong &p, leo_iter<long> &l)
{
  while ((p & 1) == 0)
    ++l, p >>= 1;
}

template<class I>
void trinkle(I top, ulong p, leo_iter<long> l)
{
  while (p > 0) {
    normalize(p, l);
    I ntop = top + *l;
    if (p == 1 || *top <= *ntop) {
      sift(top, l);
      break;
    }
    --p;
    if (*l == 1) {
      std::swap(*top, *ntop);
      top = ntop;
      continue;
    }
    leo_iter<long> lc = l;
    --lc;
    I child = top + (*l - *lc);
    if (*(top + 1) < *child) {
      child = top + 1;
      --lc;
    }
    if (*child < *ntop) {
      std::swap(*top, *child);
      sift(child, lc);
      break;
    }
    std::swap(*ntop, *top);
    top = ntop;
  }
}

template<class I>
void semitrinkle(I top, ulong p, leo_iter<long> l)
{
  I ntop = top + *l;
  if (p > 1 && *top > *ntop) {
    std::swap(*ntop, *top);
    trinkle(ntop, p >> 1, ++l);
  }
}

template<class I>
leo_iter<long> make_leo_heap(I start, I end, ulong &p)
{
  leo_iter<long> l(1, 3);
  for (I i = end - 2; i - start >= 0; --i) { 
    if ((p & 3) == 3) {
      sift(i + 1, l);
      p = (p >> 2) + 1;
      std::advance(l, 2);
     // ++++l;
    }
    else {
      leo_iter<long> tmp = l;
      --l;
      if (i - start < *tmp)
        trinkle(i + 1, p, tmp);
      else
        sift(i + 1, tmp);
      p <<= 1;
      while (*l > 1)
        --l, p <<= 1;
      ++p;
    }
  }
  trinkle(start, p, l);
  return l;
}

template<class I>
void smoothsort(I start, I end)
{
  if (end - start < 2) return;
  ulong p = 1;
  leo_iter<long> l = make_leo_heap(start, end, p);
  for (I i = start; i != end - 1; ++i) {
    if (*l == 1) {
      --p;
      normalize(p, l);
    }
    else {
      --p;
      --l;
      p = (p << 1) + 1;
      leo_iter<long> tmp = l;
      --l;
      semitrinkle(i + *l + 1, p, tmp);
      p = (p << 1) + 1;
      semitrinkle(i + 1, p, l);
    }
  }
}
