#include <ios>
#include <iostream>
#include <iomanip>
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
  try{
    v.popBack();
    return v.getSize() == 0;
  } catch(...)
  {
    return false;
  }
}

bool testElementAccess()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  return v[0] == 1 && v[1] == 2;
}

bool testCopyConstructor()
{
  topit::Vector<int> v;
  v.pushBack(1);
  topit::Vector<int> yav = v;
  bool isAllEqual = v.getSize() == yav.getSize();
  for(size_t i = 0; isAllEqual && i < v.getSize(); ++i)
  {
    isAllEqual = isAllEqual && (v[i] == yav[i]);
  }
  return isAllEqual;
}

bool testAssignmentOperator()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  topit::Vector<int> yav;
  yav = v;
  bool isAllEqual = v.getSize() == yav.getSize();
  for(size_t i = 0; isAllEqual && i < v.getSize(); ++i)
  {
    isAllEqual = isAllEqual && (v[i] == yav[i]);
  }
  return isAllEqual;
}

bool testAssignmentOperatorWithoutValues()
{
  topit::Vector<int> v;
  topit::Vector<int> yav;
  yav = v;
  return v.getSize() == yav.getSize();
}

bool testPushFront()
{
  topit::Vector<int> v;
  v.pushFront(3);
  return v[0] == 3;
}

bool testPushFrontManyValues()
{
  topit::Vector<int> v;
  v.pushFront(3);
  v.pushFront(2);
  v.pushFront(1);
  return v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testPopFront()
{
  topit::Vector<int> v;
  v.pushFront(1);
  v.popFront();
  return v.getSize() == 0;
}

bool testPopFrontNoValue()
{
  topit::Vector<int> v;
  try{
    v.popFront();
    return v.getSize() == 0;
  } catch(...)
  {
    return false;
  }
}

bool testSwap()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  topit::Vector<int> yav;
  v.swap(yav);
  bool isAllEqual = (v.getSize() == 0 && yav.getSize() == 3);
  for(size_t i = 0; isAllEqual && i < yav.getSize(); ++i)
  {
    isAllEqual = isAllEqual && (yav[i] == i + 1);
  }
  return isAllEqual;
}

int main()
{
  using test_t = bool(*)();
  using pair_t = std::pair< const char*, test_t>;
  pair_t tests[] = {
    {"Default vector is empty", testDefaultVector},
    {"Vector with amy value is not empty", testVectorWithValue},
    {"Correct size of vector", testGetSizeWithValues},
    {"Correct size of empty vector", testGetSizeWithoutValues},
    {"Correct capacity of vector", testGetCapacityWithValues},
    {"Correct capacity of empty vector", testGetCapacityWithoutValues},
    {"Correct adding one element to the ending", testPushBack},
    {"Correct deleting last value", testPopBackValue},
    {"Correct deleting no values from ending", testPopBackNoValue},
    {"Inbound access elements", testElementAccess}, 
    {"Sizes must be as elemets", testCopyConstructor},
    {"The copy operator is working", testAssignmentOperator},
    {"The copy operator is working without values", testAssignmentOperatorWithoutValues},
    {"Correct adding one element to the beginning", testPushFront},
    {"Correct adding many values to the beginning", testPushFrontManyValues},
    {"Correct deleting first value", testPopFront},
    {"Correct deleting no values from beginning", testPopFrontNoValue},
    {"Correct swapping vectors", testSwap}
  };

  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  for(size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    //std::cout << tests[i].first << ": " << res << "\n";
    std::cout << std::left << std::setw(43) << tests[i].first << ": " << res << "\n";
  }
}
