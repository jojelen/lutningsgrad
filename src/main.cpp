#include "tensor.hpp"

#include <assert.h>
#include <iostream>

using namespace std;

void printTensor(const Tensor &t) {
  cout << "val = " << t.getVal() << ", grad = " << t.getGrad() << endl;
}

int main(int argc, const char **argv) {
  Tensor t1(45);
  Tensor t2(21);

  Tensor t3 = t1 + t2;

  t3.backward();

  printTensor(t1);
  printTensor(t2);
  printTensor(t3);

  Tensor t4(3);

  Tensor t5 = t4 + t4;

  t5.backward();

  printTensor(t4);
  printTensor(t5);
}
