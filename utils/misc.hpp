#pragma once

#include <vector>
#include <string>

void readFileToVec(const std::string& filePath, std::vector<char> &vec);

void printImageVec(const std::vector<char>& vec, int rows, int cols);
