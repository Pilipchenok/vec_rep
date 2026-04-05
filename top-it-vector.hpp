#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
#include <cassert>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

namespace topit
{
  template <class T> struct Vector
  {
    Vector();
    Vector(const Vector<T>&);
    Vector(Vector<T>&&) noexcept;
    explicit Vector(std::initializer_list<T> il);
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
    void reserve(size_t cap);
    void shrinkToFit();
    void pushBack(const T& k);
    void popBack();
    void pushFront(T val);
    void popFront();
    void swap(Vector<T>& rhs) noexcept;

    //Переделать работу с памятью.
    //Убедиться в том, что вектору не требуется конструктор по умолчанию (!)
    void insert(size_t i, const T& val);
    void erase(size_t i);
    void insert(size_t i, const Vector<T>& rhs, size_t beg, size_t end);
    void erase(size_t beg, size_t end);
    void clear(T* data, size_t size);

    private:
      T *data_;
      size_t size_, capacity_;
      explicit Vector(size_t k);
      void pushBackImpl(const T&); //реализовать
      void reserve(size_t pos, size_t k); //реализовать
  };
} // namespace topit

template <class T>
topit::Vector<T>::Vector(std::initializer_list<T> il):
  Vector(il.size())
{
  try
  {
    for (auto&& v : il)
    {
      new (data_ + size_++) T(std::move(v));
    }
  }
  catch (...)
  {
    clear(data_, size_);
    throw;
  }
}

template <class T>
void topit::Vector<T>::reserve(size_t cap)
{
  if (capacity_ >= cap)
  {
    return;
  }
  T* d = static_cast<T*>(::operator new (sizeof(T) * cap));
  size_t i = 0;
  try{
    for(; i < getSize(); ++i)
    {
      new (d + i) T(std::move(data_[i]));
    }
  }catch(...)
  {
    for(size_t j = 0; j < i; ++j)
    {
      (d + i)->~T();
    }
    ::operator delete (d);
    throw;
  }
  ::operator delete(data_);
  data_ = d;
  capacity_ = cap;
}

template <class T>
void topit::Vector<T>::pushFront(T val)
{
  Vector<T> cpy(size_ + 1);
  try
  {
    new (cpy.data_) T(val);
    for(cpy.size_ = 1; cpy.size_ < size_ + 1; ++cpy.size_)
    {
      new(cpy.data_ + cpy.size_) T((*this)[cpy.size_ - 1]);
    }
  } catch(...)
  {
    clear(cpy.data_, cpy.size_);
    ::operator delete(cpy.data_);
    throw;
  }
  swap(cpy);
}

template <class T>
void topit::Vector<T>::popFront()
{
  if(size_ > 0)
  {
    Vector<T> cpy(size_ - 1);
    try{
      for(; cpy.size_ < size_ - 1; ++cpy.size_)
      {
        new (cpy.data_ + cpy.size_) T((*this)[cpy.size_ + 1]);
      }
    } catch(...)
    {
      clear(cpy.data_, cpy.size_);
      ::operator delete (cpy.data_);
      throw;
    }
    
    swap(cpy);
  } else {
    throw std::out_of_range("Vector is empty");
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
  data_(static_cast<T*>(::operator new (sizeof(T) * k))),
  size_(0),
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
  try{
    for(; size_ < rhs.getSize(); ++size_)
    {
      new (data_ + size_) T(rhs[size_]);
    }
  } catch(...)
  {
    clear(data_, size_);
    throw;
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
    T* d = static_cast<T*>(::operator new (sizeof(T) * (capacity_ + 10)));
    size_t i = 0;
    try{
      for(; i < getSize(); ++i)
      {
        new (d + i) T(std::move(data_[i]));
      }
    }catch(...){
      for(size_t j = 0; j < i; ++j)
      {
        (d + i)->~T();
      }
      ::operator delete (d);
      throw;
    }
    ::operator delete(data_);
    data_ = d;
    capacity_ += 10;
  }
  new (data_ + size_++) T(k);
}

template <class T>
void topit::Vector<T>::popBack()
{
  if(size_ > 0)
  {
    --size_;
  } else {
    throw std::out_of_range("Vector is empty");
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
  clear(data_, size_);
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

  try{
    for(; data.size_ < i; ++data.size_)
    {
      new (data.data_ + data.size_) T((*this)[data.size_]);
    }
    new (data.data_ + data.size_++) T(val);
    for(; data.size_ < size_ + 1; ++data.size_)
    {
      new (data.data_ + data.size_) T((*this)[data.size_ - 1]);
    }
  } catch(...) {
    clear(data.data_, data.size_);
    ::operator delete(data.data_);
    throw;
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
  try
  {
    for(; data.size_ < i; ++data.size_)
    {
      new (data.data_ + data.size_) T((*this)[data.size_]);
    }
    for(; data.size_ < size_ - 1; ++data.size_)
    {
      new (data.data_ + data.size_) T((*this)[data.size_ + 1]);
    }
  } catch(...)
  {
    clear(data.data_, data.size_);
    ::operator delete(data.data_);
    throw;
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

  try{
    for(; data.size_ < i; ++data.size_)
    {
      new (data.data_ + data.size_) T((*this)[data.size_]);
    }
    size_t rhsCount = beg;
    for(; data.size_ < i + countAdd; ++data.size_)
    {
      new (data.data_ + data.size_) T(rhs[rhsCount++]);
    }
    for(; data.size_ < size_ + countAdd; ++data.size_)
    {
      new (data.data_ + data.size_) T((*this)[data.size_ - countAdd]);
    }
  } catch (...)
  {
    clear(data.data_, data.size_);
    ::operator delete(data.data_);
    throw;
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
  try{
    for(; data.size_ < beg; ++data.size_)
    {
      new (data.data_ + data.size_) T((*this)[data.size_]);
    }
    for(; data.size_ < size_ - countEr; ++data.size_)
    {
      new (data.data_ + data.size_) T((*this)[data.size_ + countEr]);
    }
  } catch (...)
  {
    clear(data.data_, data.size_);
    ::operator delete(data.data_);
    throw;
  }
  swap(data);
}

template <class T>
void topit::Vector<T>::clear(T* data, size_t size)
{
  for(size_t i = 0; i < size; ++i)
  {
    (data + i) -> ~T();
  }
}

template <class T>
void topit::Vector<T>::pushBackImpl(const T& val)
{
  new (data_ + size_++) T(val);
}

template <class T>
void topit::Vector<T>::reserve(size_t pos, size_t k)
{
  if (pos > size_)
  {
    throw std::out_of_range("Invalid position");
  }
  Vector<T> cpy(size_ + k);
  try {
    for(; cpy.size_ < pos; ++cpy.size_)
    {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_]);
    }
    cpy.size_ += k;
    for(; cpy.size_ < size_ + k; ++cpy.size_)
    {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_ - k]);
    }
    swap(cpy);
  } catch (...) {
    if (cpy.size_ < pos)
    {
      for (size_t i = 0; i < cpy.size_; ++i)
      {
        (cpy.data_ + i)->~T();
      }
    }
    else
    {
      for (size_t i = 0; i < pos; ++i)
      {
        (cpy.data_ + i)->~T();
      }
      for (size_t i = pos + k; i < cpy.size_; ++i)
      {
        (cpy.data_ + i)->~T();
      }
    }
    ::operator delete(cpy.data_);
    throw;
  }
}

#endif