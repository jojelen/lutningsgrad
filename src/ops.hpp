#pragma once

#include "tensor.hpp"

void backwardNoOp(Node* node);
void backwardAdd(Node* node);
void backwardMult(Node* node);

