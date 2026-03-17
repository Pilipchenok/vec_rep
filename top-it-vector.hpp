#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
namespace topit
{
  template <class T> struct Vector
  {
    Vector();
    Vector(const Vector<T>&) = delete;
    ~Vector();
    Vector<T>& operator=(const Vector<T>&) = delete;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    void pushBack(const T& k);
    void popBack();

    private:
      T *data_;
      size_t size_, capasity_;
  };
} // namespace topit


template <class T>
bool topit::Vector<T>::isEmpty() const noexcept
{
  return !size_;
}

template <class T>
size_t topit::Vector<T>::getSize() const noexcept
{
  return size_;
}

template <class T>
size_t topit::Vector<T>::getCapacity() const noexcept
{
  return capasity_;
}

template <class T>
void topit::Vector<T>::pushBack(const T& k)
{
  if(size_ == capasity_)
  {
    T* data = new T[capasity_ + 10];
    capasity_ = capasity_ + 10;
    for(size_t i = 0; i < size_; ++i)
    {
      data[i] = data_[i];
    }
    delete[] data_;
    data_ = data; 
  }
  data_[size_++] = k;
}

template <class T>
void topit::Vector<T>::popBack()
{
  --size_;
}

template <class T>
topit::Vector<T>::Vector():
  data_(nullptr),
  size_(0),
  capasity_(0)
{}

template <class T>
topit::Vector<T>::~Vector()
{
  delete[] data_;
}
#endif