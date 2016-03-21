#include <stdbool.h>
#include <stdio.h>

typedef int elem;
typedef unsigned long ulong;

typedef struct {
  long cur, prev;
} lpair;

void up(lpair *L)
{
  elem tmp = L->cur;
  L->cur = L->cur + L->prev + 1;
  L->prev = tmp;
}

void down(lpair *L)
{
  elem tmp = L->prev;
  L->prev = L->cur - L->prev - 1;
  L->cur = tmp;
}

void normalize(ulong *p, lpair *L)
{
  while ((*p & 1) == 0)
    up(L), *p >>= 1;
}

void swap(elem *x, elem *y)
{
  elem tmp = *x;
  *x = *y;
  *y = tmp;
}

void sift(elem *top, lpair L)
{
  while (L.cur > 1) {
    elem *child = top - (L.cur - L.prev);
    down(&L);
    if (*child < *(top - 1)) {
      child = top - 1;
      down(&L);
    }
    if (*child <= *top)
      break;
    swap(top, child);
    top = child;
  }
}

void trinkle(elem *top, ulong p, lpair L)
{
  while (p > 0) {
    normalize(&p, &L);
    elem *ntop = top - L.cur;
    if (p == 1 || *ntop < *top) {
      sift(top, L);
      break;
    }
    --p;
    if (L.cur == 1) {
      swap(ntop, top);
      top = ntop;
    }
    else {
      elem *child = ntop + L.prev;
      lpair Lc = L;
      down(&Lc);
      if (*child < *(top - 1)) {
        child = top - 1;
        down(&Lc);
      }
      if (*ntop > *child) {
        swap(ntop, top);
        top = ntop;
      }
      else {
        swap(child, top);
        sift(child, Lc);
        break;
      }
    }
  }
}

void semitrinkle(elem *top, ulong p, lpair L)
{
  elem *ntop = top - L.cur;
  if (p > 1 && *ntop > *top) {
    swap(ntop, top);
    trinkle(ntop, p - 1, L);
  }
}

void smoothsort(elem *m, long n)
{
  long i;
  ulong p = 1;
  lpair L;
  L.cur = 1;
  L.prev = 1;
  for (i = 1; i < n; ++i) { 
    if ((p & 3) == 3) {
      sift(m + i - 1, L);
      p = (p >> 2) + 1;
      up(&L), up(&L);
    }
    else {
      if (i + L.prev < n)
        sift(m + i - 1, L);
      else
        trinkle(m + i - 1, p, L);
      down(&L), p <<= 1;
      while (L.cur > 1)
        down(&L), p <<= 1;
      ++p;
    }
  }
  trinkle(m + n - 1, p, L);
  while (i > 1) {
    --i;
    if (L.cur == 1) {
      --p;
      normalize(&p, &L);
    }
    else {
      --p;
      down(&L), p = (p << 1) + 1;
      semitrinkle(m + (i - L.prev) - 1, p, L);
      down(&L), p = (p << 1) + 1;
      semitrinkle(m + i - 1, p, L);
    }
  }
}

int main()
{
  long n;
  scanf("%ld", &n);
  int m[n];
  long i;
  for (i = 0; i != n; ++i)
    scanf("%d", m + i);
  smoothsort(m, n);
  printf("%ld\n", n);
  for (i = 0; i < n; ++i)
    printf("%d\n", m[i]);
  return 0;
}
