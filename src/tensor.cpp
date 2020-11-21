#include "tensor.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;

void backwardNoOp(Node *node) { cout << "Leaf: " << node << endl; }
void backwardAdd(Node *node) {
  cout << "backwardAdd for " << node << endl;
  for (auto &parent : node->parents)
    parent->grad += node->grad;
}

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
  vector<Node *> graph;
  unordered_set<Node *> visitedNodes;
  walk(graph, visitedNodes, node_.get());

  node_->grad = 1;
  reverse(graph.begin(), graph.end());
  for (auto &n : graph)
    n->backFunc(n);
}
