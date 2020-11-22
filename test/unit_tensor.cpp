#include "tensor.hpp"

#include <assert.h>
#include <iostream>

using namespace std;

void runTests() {
  Tensor t1(45);
  Tensor t2(21);
  Tensor t3 = t1 + t2;
  assert(t3.getVal() == 66);

  t3.backward();

  assert(t1.getGrad() == 1);
  assert(t2.getGrad() == 1);
  assert(t3.getGrad() == 1);

  Tensor t4(3);
  Tensor t5 = t4 + t4;
  assert(t5.getVal() == 6);

  t5.backward();

  assert(t4.getGrad() == 2);

  Tensor t6(2);
  Tensor t7(42);
  Tensor t8 = t7 * t6;
  assert(t8.getVal() == 84);

  t8.backward();

  assert(t6.getGrad() == 42);
  assert(t7.getGrad() == 2);

  Tensor t9(3);
  Tensor t10 = 4 + t9;
  assert(t10.getVal() == 7);
  Tensor t11 = t9 + 5;
  assert(t11.getVal() == 8);
  Tensor t12 = t9 * t11;
  assert(t12.getVal() == 24);

  t12.backward();
  assert(t9.getGrad() == 11);
  assert(t11.getGrad() == 3);

  cout << "Tests: Passed\n";
}

int main(int argc, const char **argv) {
  runTests();
}
