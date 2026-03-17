#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
namespace topit
{
  template <class T> struct Vector
  {
    Vector();
    ~Vector();

    bool isEmpty() const noexcept;

    private:
      T *data_;
      size_t sizse_, capasity_;
  };
} // namespace topit
#endif