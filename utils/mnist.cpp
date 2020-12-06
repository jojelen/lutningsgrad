#include "mnist.hpp"

#include <assert.h>
#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

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
  static std::ifstream is(string(base_dir) +
                              "/data/mnist/train-images-idx3-ubyte",
                          ifstream::binary);
  if (!is.good())
    throw runtime_error("Couldn't open data set  " + string(base_dir));
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

