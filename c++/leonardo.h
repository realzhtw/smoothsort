#include <iterator>

template<typename T>
class leo_iter {
  T cur, next;
public:
  typedef T value_type;
  typedef long difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T *pointer;
  typedef T &reference;

  leo_iter(const T &cur, const T &next): cur(cur), next(next) {}
  long operator*() const { return cur; }
  leo_iter<T> &operator++() { next += cur; cur = next - cur; ++next; return *this; }
  leo_iter<T> &operator--() { cur = next - cur; next -= cur; --cur; return *this; }
};

template<typename T>
leo_iter<T> leo_begin(const T &cur, const T &next)
{
  return leo_iter<T>(cur, next);
}
