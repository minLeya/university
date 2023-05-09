#include <vector>
#include <iostream>
#include <utility>

#include "SortingAlgorithms.h"

void printVector(const std::vector<int>& numbers)
{
	for (const auto& number : numbers)
	{
		std::cout << number << ' ';
	}
	std::cout << '\n';
}

void bubbleSort(std::vector<int> numbers)
{
	int numberOfComparisons{ 0 };
	int numberOfAssignments{ 0 };

	for (std::size_t i{ 0 }; i < numbers.size(); ++i)
	{
		for (std::size_t j{ 0 }; j < numbers.size() - (i + 1); ++j)
		{
			++numberOfComparisons;
			if (numbers[j] > numbers[j + 1])
			{
				std::swap(numbers[j], numbers[j + 1]);
				numberOfAssignments += 3;
			}
		}
	}

	std::cout << "\nsorted by bubble method:\n";
	printVector(numbers);
	std::cout << "number of comparisons: " << numberOfComparisons << '\n';
	std::cout << "number of assignments: " << numberOfAssignments << '\n';
}

void selectionSort(std::vector<int> numbers)
{
	int numberOfComparisons{ 0 };
	int numberOfAssignments{ 0 };

	for (std::size_t i{ 0 }; i < numbers.size() - 1; ++i)
	{
		std::size_t indexOfMinimum{ i };
		for (std::size_t j{ i + 1 }; j < numbers.size(); ++j)
		{
			++numberOfComparisons;
			if (numbers[j] < numbers[indexOfMinimum])
				indexOfMinimum = j;
		}

		++numberOfComparisons;
		if (numbers[indexOfMinimum] != numbers[i])
		{
			numberOfAssignments += 3;
			std::swap(numbers[indexOfMinimum], numbers[i]);
		}
	}

	std::cout << "\nsorted:\n";
	printVector(numbers);
	std::cout << "number of comparisons: " << numberOfComparisons << '\n';
	std::cout << "number of assignments: " << numberOfAssignments << '\n';
}

void insertionSort(std::vector<int> numbers)
{
	int numberOfComparisons{ 0 };
	int numberOfAssignments{ 0 };

	for (std::size_t i{ 1 }; i < numbers.size(); ++i)
	{
		++numberOfAssignments;
		int current{ numbers[i] };
		int j{ static_cast<int>(i - 1) };

		++numberOfComparisons;
		while (j >= 0 && numbers[j] > current)
		{
			++numberOfComparisons;
			numbers[j + 1] = numbers[j];
			++numberOfAssignments;
			--j;
		}

		++numberOfComparisons;
		if (numbers[j + 1] != current)
		{
			++numberOfAssignments;
			numbers[j + 1] = current;
		}
	}

	std::cout << "\nsorted:\n";
	printVector(numbers);
	std::cout << "number of comparisons: " << numberOfComparisons << '\n';
	std::cout << "number of assignments: " << numberOfAssignments << '\n';
}

void heapify(std::vector<int>& numbers, int size, int i, int& numberOfComparisons, int& numberOfAssignments)
{
	int largest{ i }; //корень
	int left{ 2 * i + 1 };
	int right{ 2 * i + 2 };
	//если левый дочерний элемент больше корня
	if (left < size && numbers[left] > numbers[largest])
	{
		largest = left;
		++numberOfComparisons;
	}
		
	//если правый дочерний эдемент больше 
	if (right < size && numbers[right] > numbers[largest])
	{
		largest = right;
		++numberOfComparisons;
	}
	//если самый большой элемент не корень
	if (largest != i)
	{
		std::swap(numbers[i], numbers[largest]);
		numberOfAssignments += 3;
		//Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		heapify(numbers, size, largest, numberOfComparisons, numberOfAssignments);
	}
}

void heapSort(std::vector<int> numbers)
{
	int numberOfComparisons{ 0 };
	int numberOfAssignments{ 0 };

	int size{static_cast<int>(numbers.size()) };//it was size_t
	// Построение кучи (перегруппируем массив)
	for (int i{ size / 2 - 1 }; i >= 0; --i)
		heapify(numbers, size, i, numberOfComparisons, numberOfAssignments);

	// Один за другим извлекаем элементы из кучи
	for (int i{ size - 1 }; i >= 0; --i)
	{
		if (numbers[0] != numbers[i])
		{
			// Перемещаем текущий корень в конец
			std::swap(numbers[0], numbers[i]);
			numberOfAssignments += 3;
		}
		// вызываем процедуру heapify на уменьшенной куче
		heapify(numbers, i, 0, numberOfComparisons, numberOfAssignments);
	}

	std::cout << "\nsorted:\n";
	printVector(numbers);
	std::cout << "number of comparisons: " << numberOfComparisons << '\n';
	std::cout << "number of assignments: " << numberOfAssignments << '\n';
}

//void shellSort(std::vector<int>numbers)
//{
//	int numberOfComparisons{ 0 };
//	int numberOfAssignments{ 0 };
//
//	int size{ static_cast<int>(numbers.size()) };
//
//	for (int gap{ size / 2 }; gap > 0; gap /= 2)
//	{
//		for (int i{ gap }; i < size; ++i)
//		{
//			++numberOfAssignments;
//			int temporary{ numbers[i] };
//
//			int j{ 0 };
//			++numberOfComparisons;
//			for (j = i; j >= gap && numbers[j - gap] > temporary; j -= gap)
//			{
//				++numberOfAssignments;
//				++numberOfComparisons;
//				numbers[j] = numbers[j - gap];
//			}
//			numbers[j] = temporary;
//			++numberOfAssignments;
//		}
//	}
//
//	std::cout << "\nsorted:\n";
//	printVector(numbers);
//	std::cout << "number of comparisons: " << numberOfComparisons << '\n';
//	std::cout << "number of assignments: " << numberOfAssignments << '\n';
//}

void shellSort(std::vector<int>numbers)
{
	int numberOfComparisons{ 0 };
	int numberOfAssignments{ 0 };

	int size{ static_cast<int>(numbers.size()) };

	for (int gap{ size / 2 }; gap > 0; gap /= 2)
	{
		for (int i{ gap }; i < size; ++i)
		{
			++numberOfAssignments;
			int temporary{ numbers[i] };
			int j{ i - gap };

			++numberOfComparisons;
			while (j >= 0 && temporary < numbers[j])
			{
				++numberOfComparisons;
				numbers[j + gap] = numbers[j];
				j = j - gap;
				++numberOfAssignments;
			}
			++numberOfAssignments;
			numbers[j + gap] = temporary;
		}
	}

	std::cout << "\nsorted:\n";
	printVector(numbers);
	std::cout << "number of comparisons: " << numberOfComparisons << '\n';
	std::cout << "number of assignments: " << numberOfAssignments << '\n';
}

//int partition(std::vector<int>numbers, int start, int end, int& numberOfComparisons, int& numberOfAssignments)
//{
//	//Выбираем крайний правый элемент в качестве опорного элемента массива
//	int pivot{ numbers[end] }; 
//	int index{ start };
//
//	for (int i{ start }; i < end; ++i)
//	{
//		if (numbers[i] <= pivot)
//		{
//			++numberOfComparisons;
//			std::swap(numbers[i], numbers[index]);
//			numberOfAssignments += 3;
//			++index;
//		}
//	}
//	std::swap(numbers[index], numbers[end]);
//	numberOfAssignments += 3;
//	return index;
//}
//
//void quickSort(std::vector<int>numbers, int start, int end, int& numberOfComparisons, int& numberOfAssignments)
//{
//
//	if (start >= end)
//	{
//		return;
//	}
//
//	int pivot{ partition(numbers, start, end, numberOfComparisons, numberOfAssignments) };
//	quickSort(numbers, start, pivot - 1, numberOfComparisons, numberOfAssignments);
//	quickSort(numbers, start, pivot + 1, numberOfComparisons, numberOfAssignments);
//
//}

//огромное спасибо, Расим, ты бог
void quickSort(std::vector<int>& numbers, int left, int right, int& numberOfComparisons, int& numberOfAssignments)
{
	int pivot{ numbers[(left + right) / 2] };

	int low{ left };
	int high{ right };
	while (low <= high)
	{
		++numberOfComparisons;
		while (numbers[low] < pivot)
		{
			++low;
			++numberOfComparisons;
		}

		++numberOfComparisons;
		while (numbers[high] > pivot)
		{
			--high;
			++numberOfComparisons;
		}

		if (low <= high)
		{
			++numberOfComparisons;
			if (numbers[low] != numbers[high])
			{
				std::swap(numbers[low], numbers[high]);
				numberOfAssignments += 3;
			}
			++low;
			--high;
		}
	}

	if (left < high)
		quickSort(numbers, left, high, numberOfComparisons, numberOfAssignments);
	if (low < right)
		quickSort(numbers, low, right, numberOfComparisons, numberOfAssignments);
}
