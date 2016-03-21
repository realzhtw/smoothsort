#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

#include "smoothsort.h"

using namespace std;

int main()
{
  vector<int> m;
  copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(m));
  smoothsort(m.begin(), m.end());
  //sort(m.begin(), m.end());
  copy(m.begin(), m.end(), ostream_iterator<int>(cout, "\n"));
  return 0;
}
