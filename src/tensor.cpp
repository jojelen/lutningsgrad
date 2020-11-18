#include "tensor.hpp"

#include <stdexcept>

using namespace std;

Tensor::Tensor() {}

Tensor::~Tensor() {}

Tensor Tensor::operator+(const Tensor &tensor) {
  if (this->shape.size() == tensor.shape.size())
    throw runtime_error("Correct size!");

  throw runtime_error("Incorrect size!");
}
