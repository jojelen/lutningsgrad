#pragma once

#include <vector>
#include <cstdint>

/*
 * Tensor w1({200, 100});
 * Tensor w2({100, 10});
 *
 * Tensor b1({200});
 * Tensor b2({100});
 *
 * Tensor x = randTensor({200});
 * Tensor y = (x * w1 + b1) * w2 + b2;
 *
 *
 * The tensor product should be different for different dimensions.
 * i.e.
 * both 1D: scalar
 * 1D + 2D: Matrix
 * >= 2D: Hmm not sure, lets not implement it yet.
 */


class Tensor {
    public:
        Tensor();
        ~Tensor();

    Tensor operator +(const Tensor& tensor);
    Tensor operator -(const Tensor& tensor);
    Tensor operator *(const Tensor& tensor);
    Tensor operator /(const Tensor& tensor);

    private:
        std::vector<size_t> shape;
        std::vector<uint8_t> data;
};
