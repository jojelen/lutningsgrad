#pragma once

#include <vector>
#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_set>

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
 *
 * Lets make it a scalar first.
 */
struct Node;

void backwardNoOp(Node* node);
void backwardAdd(Node* node);

struct Node {
    Node(int val, int grad, std::vector<std::shared_ptr<Node>> parents =
            {}) : val(val), grad(grad), parents(parents), backFunc(backwardNoOp) {}
    int val;
    int grad;
    std::vector<std::shared_ptr<Node>> parents;
    std::function<void(Node*)> backFunc;
};

class Tensor {
    public:
        Tensor(int val, std::vector<std::shared_ptr<Node>> parents = {});
        ~Tensor();

    Tensor operator +(Tensor& tensor);

    int getVal() const { return node_->val; }
    int getGrad() const { return node_->grad; }
    std::shared_ptr<Node> getNode() { return node_; }

    void backward();

    private:
        std::shared_ptr<Node> node_ = nullptr;
};


