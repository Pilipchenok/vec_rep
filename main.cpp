#include <ios>
#include <iostream>
#include <iomanip>
#include "top-it-vector.hpp"

bool testDefaultVector()
{
  topit::Vector<int> v;
  return v.isEmpty();
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

bool testElementConstAccess()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  const topit::Vector<int>& rv = v;
  return rv[0] == 1 && rv[1] == 2;
}

bool testElementCheckedAccess()
{
  topit::Vector<int> v;
  try
  {
    v.at(0);
    return false;
  }
  catch(std::out_of_range)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementInboundCheckedAccess()
{
  topit::Vector<int> v;
  v.pushBack(1);
  try
  {
    int& val = v.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementInboundCheckedConstAccess()
{
  topit::Vector<int> v;
  v.pushBack(1);
  const topit::Vector<int>& rv = v;
  try
  {
    const int& val = rv.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
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

bool testBaseInsert()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(3);
  
  try{
    v.insert(1, 2);
    return v[1] == 2;
  }
  catch(...)
  {
    return false;
  }
}

bool testOverflowInsert()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(3);
  try
  {
    v.insert(10, 2);
    return false;
  }
  catch(std::range_error)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool testBaseErase()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  try{
    v.erase(1);
    return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
  }
  catch(...)
  {
    return false;
  }
}

bool testNoValuesErase()
{
  topit::Vector<int> v;
  try
  {
    v.erase(0);
    return false;
  }
  catch(std::range_error)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool testOverflowErase()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try
  {
    v.erase(10);
    return false;
  }
  catch(std::range_error)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool testManyBaseInsert()
{
  topit::Vector<int> rhs;
  rhs.pushBack(1);
  rhs.pushBack(2);
  rhs.pushBack(3);
  rhs.pushBack(4);
  rhs.pushBack(5);
  rhs.pushBack(6);

  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  try{
    v.insert(1, rhs, 3, 4);
    return v[1] == 4 && v[2] == 5 && v.getSize() == 5;
  }
  catch(...)
  {
    return false;
  }
}

bool testManyIncorrectRhsInsert()
{
  topit::Vector<int> rhs;
  rhs.pushBack(1);
  rhs.pushBack(2);
  rhs.pushBack(3);
  rhs.pushBack(4);
  rhs.pushBack(5);
  rhs.pushBack(6);

  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try
  {
    v.insert(1, rhs, 4, 10);
    return false;
  }
  catch(std::range_error)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool testManyIncorrectVInsert()
{
  topit::Vector<int> rhs;
  rhs.pushBack(1);
  rhs.pushBack(2);
  rhs.pushBack(3);
  rhs.pushBack(4);
  rhs.pushBack(5);
  rhs.pushBack(6);

  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try
  {
    v.insert(100, rhs, 3, 4);
    return false;
  }
  catch(std::range_error)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool testManyIncorrectIndexesInsert()
{
  topit::Vector<int> rhs;
  rhs.pushBack(1);
  rhs.pushBack(2);
  rhs.pushBack(3);
  rhs.pushBack(4);
  rhs.pushBack(5);
  rhs.pushBack(6);

  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try
  {
    v.insert(1, rhs, 4, 3);
    return false;
  }
  catch(std::range_error)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
  return v[1] == 2 && v.getSize() == 3;
}

bool testBaseManyErase()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try{
    v.erase(1, 2);
    return v.getSize() == 1 && v[0] == 1;
  }
  catch(...)
  {
    return false;
  }
}

bool testOverflowIndexesManyErase()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try{
    v.erase(5, 10);
    return false;
  }
  catch(std::range_error)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool testUncorrectIndexesManyErase()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try{
    v.erase(2, 1);
    return false;
  }
  catch(std::range_error)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool testInitializerListConstructor()
{
  topit::Vector<int> v{1, 2};
  return v.getSize() == 2;
}

int main()
{
  topit::Vector<int> v, yav;
  v = v;
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
    {"Inbound access const elements", testElementConstAccess},
    {"Correct unworking at method", testElementCheckedAccess},
    {"Correct working at method", testElementInboundCheckedAccess},
    {"Correct working const at method", testElementInboundCheckedConstAccess},
    {"Sizes must be as elemets", testCopyConstructor},
    {"The copy operator is working", testAssignmentOperator},
    {"The copy operator is working without values", testAssignmentOperatorWithoutValues},
    {"Correct adding one element to the beginning", testPushFront},
    {"Correct adding many values to the beginning", testPushFrontManyValues},
    {"Correct deleting first value", testPopFront},
    {"Correct deleting no values from beginning", testPopFrontNoValue},
    {"Correct swapping vectors", testSwap},
    {"Correct inserting one value", testBaseInsert},
    {"Correct throwing invalid index in insert", testOverflowInsert},
    {"Correct erasing one value", testBaseErase},
    {"Correct erasing from empty vector", testNoValuesErase},
    {"Correct throwing invalid index in erasing", testOverflowErase},
    {"Correct inserting many values", testManyBaseInsert},
    {"Correct throwing incorrect index of inserting vector", testManyIncorrectRhsInsert},
    {"Correct throwing incorrect index of vector for insert", testManyIncorrectVInsert},
    {"Correct throwing invalid order of indexes in inserting vector", testManyIncorrectIndexesInsert},
    {"Correct erasing many elements", testBaseManyErase},
    {"Correct throwing overflow indexes of many erasing", testOverflowIndexesManyErase},
    {"Correct throwing uncorrect indexes of many erasing", testUncorrectIndexesManyErase},
    {"Vector with initializer list must be same size as init-list", testInitializerListConstructor}
  };

  bool all = true;
  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  for(size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << std::left << std::setw(61) << tests[i].first << ": " << res << "\n";
    all = all && res;
  }
  std::cout << "RESULT: " << all << "\n";
}
