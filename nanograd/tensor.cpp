#include "tensor.hpp"
#include "ops.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;

Node::Node(int val, int grad, std::vector<std::shared_ptr<Node>> parents)
    : val(val), grad(grad), parents(parents), backFunc(backwardNoOp) {}

Tensor::Tensor(int val, vector<shared_ptr<Node>> parents) {
  node_ = make_shared<Node>(val, 0, parents);
}

Tensor::~Tensor() {}

Tensor Tensor::operator+(Tensor &tensor) {
  Tensor out(this->getVal() + tensor.getVal(),
             vector<shared_ptr<Node>>{this->getNode(), tensor.getNode()});

  out.getNode()->backFunc = backwardAdd;
  return out;
}

Tensor Tensor::operator+(int num) {
  Tensor tensor(num);

  return *this + tensor;
}

Tensor Tensor::operator*(Tensor &tensor) {
  Tensor out(this->getVal() * tensor.getVal(),
             vector<shared_ptr<Node>>{this->getNode(), tensor.getNode()});

  out.getNode()->backFunc = backwardMult;
  return out;
}

Tensor Tensor::operator*(int num) {
  Tensor tensor(num);

  return *this * tensor;
}

Tensor operator+(int num, Tensor &tensor) { return tensor + num; }
Tensor operator*(int num, Tensor &tensor) { return tensor * num; }

// Fills graph with all the connected nodes.
void walk(vector<Node *> &graph, unordered_set<Node *> &visitedNodes,
          Node *node) {
  auto it = visitedNodes.find(node);
  if (it == visitedNodes.end()) {
    cout << "Visiting node = " << node << endl;
    visitedNodes.emplace(node);
    for (const auto &n : node->parents)
      walk(graph, visitedNodes, n.get());
    graph.push_back(node);
  }
}

void Tensor::backward() {
  // Retrieve all nodes that lead up to current Tensor.
  vector<Node *> graph;
  unordered_set<Node *> visitedNodes;
  walk(graph, visitedNodes, node_.get());

  // Reverse it for backpropagation of gradient.
  reverse(graph.begin(), graph.end());

  node_->grad = 1;
  for (auto &n : graph)
    n->backFunc(n);
}
