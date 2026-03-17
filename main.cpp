#include <ios>
#include <iostream>
#include "top-it-vector.hpp"

bool testDefaultVector()
{
  topit::Vector<int> v;
  bool c = v.isEmpty();
  return !c;
}

bool testVectorWithValue()
{
  topit::Vector<int> v;
  v.pushBack(1);
  return !v.isEmpty();
}

bool testGetSizeWithValues()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  return v.getSize() == 3;
}

bool testGetSizeWithoutValues()
{
  topit::Vector<int> v;
  return v.getSize() == 0;
}

bool testGetCapacityWithValues()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  return v.getCapacity() == 10;
}

bool testGetCapacityWithoutValues()
{
  topit::Vector<int> v;
  return v.getCapacity() == 0;
}

bool testPushBack()
{
  topit::Vector<int> v;
  v.pushBack(1);
  return v[0] == 1;
}

bool testPopBackValue()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.popBack();
  return v.getSize() == 0;
}

bool testPopBackNoValue()
{
  topit::Vector<int> v;
  v.popBack();
  return v.getSize() == 0;
}

int main()
{
  using test_t = bool(*)();
  using pair_t = std::pair< const char*, test_t>;
  pair_t tests[] = {
    {"Default vector is empty", testDefaultVector},
    {"Vector with amy value is not empty", testVectorWithValue},
  };

  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  for(size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
  }
}
