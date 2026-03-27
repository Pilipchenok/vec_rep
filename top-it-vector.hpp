#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
#include <cassert>
#include <algorithm>
#include <stdexcept>
namespace topit
{
  template <class T> struct Vector
  {
    Vector();
    Vector(const Vector<T>&);
    Vector(Vector<T>&&) noexcept;
    ~Vector();
    Vector<T>& operator=(const Vector<T>&);
    Vector<T>& operator=(Vector<T>&&) noexcept;
    T& operator[](size_t index) noexcept;
    const T& operator[](size_t index) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    void pushBack(const T& k);
    void popBack();
    void pushFront(T val);
    void popFront();
    void swap(Vector<T>& rhs) noexcept;

    //Строгая гарантия + тесты
    //По желанию: реализовать итераторы для вектора, Придумать еще 3 insert и erase, но с итераторами, протестировать
    void insert(size_t i, const T& val);
    void erase(size_t i);
    void insert(size_t i, const Vector<T>& rhs, size_t beg, size_t end);
    void erase(size_t beg, size_t end);

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
topit::Vector<T>::Vector(Vector<T>&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
  rhs.size_ = 0;
  rhs.capacity_ = 0;
}

template <class T>
topit::Vector<T>& topit::Vector<T>::operator=(Vector<T>&& rhs) noexcept
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector<T> cpy(std::move(rhs));
  swap(cpy);
  return *this;
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
  const Vector<T>* cthis = this;
  const T& ret = (*cthis)[index];
  return const_cast<T&>(ret);
}

template <class T>
const T& topit::Vector<T>::operator[](size_t index) const noexcept
{
  assert(index < getSize());
  return data_[index];
}

template <class T>
T& topit::Vector<T>::at(size_t id)
{
  const Vector<T>* cthis = this;
  const T& ret = cthis->at(id);
  return const_cast<T&>(ret);
}

template <class T>
const T& topit::Vector<T>::at(size_t id) const
{
  if(id < getSize())
  {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}

template <class T>
void topit::Vector<T>::insert(size_t i, const T& val)
{
  if (i > size_)
  {
    throw std::range_error("Invalid arguments");
  }
  Vector<T> data(size_ + 1);

  for(size_t j = 0; j < i; ++j)
  {
    data[j] = (*this)[j];
  }
  data[i] = val;
  for(size_t j = i + 1; j < size_; ++j)
  {
    data[j] = (*this)[j - 1];
  }
  swap(data);
}

template <class T>
void topit::Vector<T>::erase(size_t i)
{
  if (size_ == 0 || i > size_ - 1)
  {
    throw std::range_error("Invalid arguments");
  }

  Vector<T> data(size_ - 1);
  for(size_t j = 0; j < i; ++j)
  {
    data[j] = (*this)[j];
  }
  for(size_t j = i + 1; j < size_; ++j)
  {
    data[j - 1] = (*this)[j];
  }

  swap(data);
}

template <class T>
void topit::Vector<T>::insert(size_t i, const Vector<T>& rhs, size_t beg, size_t end)
{
  if (end >= rhs.getSize() || i > size_ || end < beg)
  {
    throw std::range_error("Invalid arguments");
  }
  size_t countAdd;
  countAdd = end - beg + 1;
  Vector<T> data(size_ + countAdd);

  for(size_t j = 0; j < i; ++j)
  {
    data[j] = (*this)[j];
  }
  size_t rhsCount = beg;
  for(size_t j = i; j < i + countAdd; ++j)
  {
    data[j] = rhs[rhsCount];
    ++rhsCount;
  }
  for(size_t j = i + countAdd; j < size_; ++j)
  {
    data[j] = (*this)[j - countAdd];
  }
  swap(data);
}

template <class T>
void topit::Vector<T>::erase(size_t beg, size_t end)
{
  if (end < beg || end > size_ - 1)
  {
    throw std::range_error("Invalid arguments");
  }
  size_t countEr = end - beg + 1;
  Vector<T> data(size_ - countEr);
  for(size_t j = 0; j < beg; ++j)
  {
    data[j] = (*this)[j];
  }
  for(size_t j = beg + countEr; j < size_; ++j)
  {
    data[j - countEr] = (*this)[j];
  }
  swap(data);
}

#endif