#include "misc.hpp"

#include <assert.h>
#include <bitset>
#include <fstream>
#include <iostream>

using namespace std;

void readFileToVec(const string &filePath, vector<char> &vec) {
  ifstream is(filePath, ifstream::binary);
  if (!is.good())
    throw runtime_error("Couldn't open file: " + string(filePath));

  // get length of file:
  is.seekg(0, is.end);
  size_t length = is.tellg();
  is.seekg(0, is.beg);

  vec.clear();
  vec.resize(length);

  cout << "Reading " << length << " characters... ";
  is.read(vec.data(), length);
  if (is)
    cout << "all characters read successfully.\n";
  else
    cout << "error: only " << is.gcount() << " could be read.\n";
  is.close();
}

void printImageVec(const std::vector<char> &vec, int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      size_t pixelId = static_cast<size_t>(i * cols + j);

      assert(pixelId < vec.size());

      // The vec's content is displayed in grey scale.
      float shade = static_cast<uint8_t>(vec[pixelId]) / 255.0;
      int pixel = 232 + (255 - 232) * shade;
      cout << "\u001b[38;5;" + to_string(pixel) + "m\u2588\u001b[0m";
    }
    cout << endl;
  }
}
