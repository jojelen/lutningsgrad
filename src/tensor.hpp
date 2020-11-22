#pragma once

#include <vector>
#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_set>

struct Node {
    Node(int val, int grad, std::vector<std::shared_ptr<Node>> parents = {});
    int val;
    int grad;
    std::vector<std::shared_ptr<Node>> parents;
    std::function<void(Node*)> backFunc;
};

// TODO: Tensor is a scalar right now. Generalize.
class Tensor {
    public:
        Tensor(int val, std::vector<std::shared_ptr<Node>> parents = {});
        ~Tensor();

    Tensor operator +(Tensor& tensor);
    Tensor operator +(int num);
    Tensor operator *(Tensor& tensor);
    Tensor operator *(int num);

    int getVal() const { return node_->val; }
    int getGrad() const { return node_->grad; }
    std::shared_ptr<Node> getNode() { return node_; }

    void backward();

    private:
        std::shared_ptr<Node> node_ = nullptr;
};


Tensor operator +(int num, Tensor &tensor);
Tensor operator *(int num, Tensor &tensor);
