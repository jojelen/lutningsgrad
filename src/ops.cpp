#include "ops.hpp"

#include <assert.h>
#include <iostream>

using namespace std;

void backwardNoOp(Node *node) {
  cout << "Leaf: " << node << ", val=" << node->val << endl;
}

void backwardAdd(Node *node) {
  assert(node->parents.size() == 2);

  for (auto &parent : node->parents)
    parent->grad += node->grad;
}

void backwardMult(Node *node) {
  assert(node->parents.size() == 2);

  node->parents[0]->grad += node->parents[1]->val * node->grad;
  node->parents[1]->grad += node->parents[0]->val * node->grad;
}
