#include "mnist.hpp"

#include "misc.hpp"

#include <assert.h>
#include <iostream>
#include <iterator>

using namespace std;

MnistDataSet::MnistDataSet() { loadData(); }

void MnistDataSet::loadData() {

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
  */
  string trainLabelPath =
      string(BASE_DIR) + "/data/mnist/train-labels-idx1-ubyte";
  vector<char> labelsData;
  readFileToVec(trainLabelPath, labelsData);

  // Get the metadata.
  auto get32int = [this](const vector<char> &data, int idx) {
    int num = 0;
    for (size_t i = 0; i < 4; ++i)
      num += static_cast<uint8_t>(data[idx + i]) << (8 * (3 - i));
    return num;
  };
  trainSet_.size = get32int(labelsData, 4);

  assert(trainSet_.size == labelsData.size() - 8);

  for (size_t i = 0; i < trainSet_.size; ++i)
    trainSet_.labels.push_back(static_cast<int>(labelsData[8 + i]));

  /*
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
  string trainDataPath =
      string(BASE_DIR) + "/data/mnist/train-images-idx3-ubyte";
  readFileToVec(trainDataPath, trainSet_.data);

  trainSet_.rows = get32int(trainSet_.data, 8);
  trainSet_.cols = get32int(trainSet_.data, 12);
  trainSet_.elementSize = trainSet_.rows * trainSet_.cols;
  trainSet_.metaDataSize = 16;

  cout << "magic       = " << get32int(trainSet_.data, 0) << endl;
  cout << "num image   = " << trainSet_.size << endl;
  cout << "rows        = " << trainSet_.rows << endl;
  cout << "cols        = " << trainSet_.cols << endl;
  cout << "elementSize = " << trainSet_.elementSize << endl;
  cout << "data.size() = " << trainSet_.data.size() << endl;

  assert(trainSet_.elementSize * trainSet_.size ==
         trainSet_.data.size() - trainSet_.metaDataSize);
  assert(trainSet_.labels.size() == trainSet_.size);
}

void MnistDataSet::printNumber(size_t id) {
  cout << "MNIST image nr " << to_string(id) << ":\n";
  printImageVec(getTrainX(id), trainSet_.rows, trainSet_.cols);
  cout << "  label: " << trainSet_.labels[id] << endl;
}

size_t MnistDataSet::getTrainSetSize() const { return trainSet_.size; }

vector<char> MnistDataSet::getTrainX(size_t id) const {
  auto start = trainSet_.data.begin() + trainSet_.metaDataSize +
               id * trainSet_.elementSize;

  return vector<char>(start, start + trainSet_.elementSize);
}

int MnistDataSet::getTrainY(size_t id) const {
  assert(id > 0 && id < trainSet_.size);

  return trainSet_.labels[id];
}
