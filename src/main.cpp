#include "tensor.hpp"

#include <assert.h>
#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

/*
TRAINING SET LABEL FILE (train-labels-idx1-ubyte):
[offset] [type]          [value]          [description]
0000     32 bit integer  0x00000801(2049) magic number (MSB first)
0004     32 bit integer  60000            number of items
0008     unsigned byte   ??               label
0009     unsigned byte   ??               label
........
xxxx     unsigned byte   ??               label

The labels values are 0 to 9.
TRAINING SET IMAGE FILE (train-images-idx3-ubyte):
[offset] [type]          [value]          [description]
0000     32 bit integer  0x00000803(2051) magic number
0004     32 bit integer  60000            number of images
0008     32 bit integer  28               number of rows
0012     32 bit integer  28               number of columns
0016     unsigned byte   ??               pixel
0017     unsigned byte   ??               pixel
........
xxxx     unsigned byte   ??               pixel

Pixels are organized row-wise. Pixel values are 0 to 255. 0 means background
(white), 255 means foreground (black).
*/

void printMnist(int id) {
  static bool notInitialized = true;
  static std::ifstream is("../data/train-images.idx3-ubyte", ifstream::binary);
  static vector<char> numbers;
  static int rows;
  static int cols;
  assert(is);
  if (notInitialized) {
    // get length of file:
    is.seekg(0, is.end);
    size_t length = is.tellg();
    is.seekg(0, is.beg);

    numbers.resize(length);

    std::cout << "Reading " << length << " characters... ";
    is.read(numbers.data(), length);
    if (is)
      cout << "all characters read successfully.\n";
    else
      cout << "error: only " << is.gcount() << " could be read.\n";
    is.close();

    // Get the metadata.
    auto get32int = [](int idx) {
      int num = 0;
      for (size_t i = 0; i < 4; ++i)
        num += static_cast<uint8_t>(numbers[idx + i]) << (8 * (3 - i));
      return num;
    };
    rows = get32int(8);
    cols = get32int(12);
    cout << "magic     = " << get32int(0) << std::endl;
    cout << "num image = " << get32int(4) << std::endl;
    cout << "rows      = " << rows << std::endl;
    cout << "cols      = " << cols << std::endl;

    notInitialized = false;
  }

  cout << "MNIST image nr " << to_string(id) << ":\n";
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      size_t pixelId =
          static_cast<size_t>(16 + rows * cols * id + i * cols + j);
      assert(pixelId < numbers.size() - 1);
      float shade = static_cast<uint8_t>(numbers[pixelId]) / 255.0;
      int pixel = 232 + (255 - 232) * shade;
      cout << "\u001b[38;5;" + to_string(pixel) + "m\u2588\u001b[0m";
    }
    cout << endl;
  }
}

void printTensor(const Tensor &t) {
  cout << "val = " << t.getVal() << ", grad = " << t.getGrad() << endl;
}

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
  for (int i = 0; i < 1; ++i)
    printMnist(i);
}
