#include "mnist.hpp"

using namespace std;

int main(int argc, const char **argv) {
  MnistDataSet &mnist = MnistDataSet::instance();

  for (int i = 0; i < 15; ++i)
    mnist.printNumber(i);
}
