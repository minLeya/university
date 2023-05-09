#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

void printVector(const std::vector<int>& numbers);
void bubbleSort(std::vector<int> numbers);
void selectionSort(std::vector<int> numbers);
void insertionSort(std::vector<int> numbers);
void heapSort(std::vector<int> numbers);
void shellSort(std::vector<int>numbers);
void quickSort(std::vector<int>& numbers, int left, int right, int& numberOfComparisons, int& numberOfAssignments);
#endif // !SORTING_ALGORITHMS_H
