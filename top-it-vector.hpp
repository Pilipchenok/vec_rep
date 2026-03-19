#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
#include <cassert>
#include <algorithm>
namespace topit
{
  template <class T> struct Vector
  {
    Vector();
    Vector(const Vector<T>&);
    ~Vector();
    Vector<T>& operator=(const Vector<T>&);
    T& operator[](size_t index) noexcept;
    const T& operator[](size_t index) const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    void pushBack(const T& k);
    void popBack();
    void pushFront(T val);
    void popFront();

    void swap(Vector<T>& rhs) noexcept;

    private:
      T *data_;
      size_t size_, capacity_;
      explicit Vector(size_t k);
  };
} // namespace topit

template <class T>
void topit::Vector<T>::pushFront(T val)
{
  Vector<T> cpy((*this).getSize() + 1);
  cpy[0] = val;
  for(size_t i = 1; i < cpy.getSize(); ++i)
  {
    cpy[i] = (*this)[i - 1];
  }
  swap(cpy);
}

template <class T>
void topit::Vector<T>::popFront()
{
  if((*this).getSize() > 0)
  {
    Vector<T> cpy((*this).getSize() - 1);
    for(size_t i = 1; i < (*this).getSize(); ++i)
    {
      cpy[i - 1] = (*this)[i];
    }
    swap(cpy);
  } else {
    return;
  }
}

template <class T>
void topit::Vector<T>::swap(Vector<T>& rhs) noexcept
{
  std::swap(rhs.data_, data_);
  std::swap(rhs.size_, size_);
  std::swap(rhs.capacity_, capacity_);
}

template <class T>
topit::Vector<T>::Vector(size_t k):
  data_(new T[k]),
  size_(k),
  capacity_(k)
{}

template <class T>
topit::Vector<T>& topit::Vector<T>::operator=(const Vector<T>& rhs)
{
  Vector<T> cpy(rhs);
  swap(cpy);
  return *this;
}

template <class T>
topit::Vector<T>::Vector(const Vector<T>& rhs): Vector(rhs.getSize())
{
  for(size_t i = 0; i < getSize(); ++i)
  {
    data_[i] = rhs[i];
  }
}

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
  return capacity_;
}

template <class T>
void topit::Vector<T>::pushBack(const T& k)
{
  if(size_ == capacity_)
  {
    T* data = new T[capacity_ + 10];
    capacity_ = capacity_ + 10;
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
  if((*this).getSize() > 0)
  {
    --size_;
  } else {
    return;
  }
  
}

template <class T>
topit::Vector<T>::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template <class T>
topit::Vector<T>::~Vector()
{
  delete[] data_;
}

template <class T>
T& topit::Vector<T>::operator[](size_t index) noexcept
{
  assert(index < getSize());
  return data_[index];
}

template <class T>
const T& topit::Vector<T>::operator[](size_t index) const noexcept
{
  assert(index < getSize());
  return data_[index];
}

#endif