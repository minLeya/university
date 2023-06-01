#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <vector>

void printAvailableOperations();

void printResultTable(const std::vector<int>& values, int numberOfValues, int numberOfVariables);
void printSingleVariableResults(const std::vector<int>& values, int numberOfValues);
void printMultipleVariableResults(const std::vector<int>& values, int numberOfValues);

void printSecondForm(const std::vector<int>& values, int numberOfValues, int numberOfVariables);
void printSecondFormForSingleVariable(const std::vector<int>& values, int numberOfValues);
void printSecondFormForMultipleVariables(const std::vector<int>& values, int numberOfValues);

#endif