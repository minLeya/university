#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "Firm.h"
#include "FileIO.h"

bool FileIO::writeFirmFromFile(Firm& firm)
{
	namespace fs = std::filesystem;
	std::ifstream inputFile{ "input.txt" };
	if (!inputFile.is_open())
	{
		std::cout << "\ncouldn't open file\n";
		return false;
	}
	if (fs::file_size("input.txt") == 0)
	{
		std::cout << "\nfile is empty!\n";
		return false;
	}

	std::string line{};
	std::getline(inputFile, line);
	firm.setName(line);
	while (std::getline(inputFile, line))
	{
		std::string providerName{ line };
		firm.addProvider(providerName);
		std::getline(inputFile, line);
		std::size_t endOfProductInfo{ line.find(';') };
		std::size_t currentPosition{ 0 };
		while (true)
		{
			std::size_t endOfProductName{ line.find(',') };
			std::string productName{ line.substr(currentPosition, endOfProductName) };
			std::size_t endOfProductQuantity{ line.find(';') };
			int productQuantity{ std::stoi(line.substr(endOfProductName + 1, endOfProductQuantity)) };
			if (line.find(';') == std::string::npos)
			{
				break;
			}
			line = line.substr(line.find(';') + 1);
			firm.addProduct(providerName, productName, productQuantity);
		}
	}
	return true;
}

void FileIO::writeFirmToFile(Firm& firm)
{
	std::ofstream outputFile{ "output.txt" };
	outputFile << "Firm:" << firm.getName() << '\n';
	
	for (int i{ 0 }; i <= firm.getTop(); ++i)
	{
		Provider currentProvider{ firm.getProvider(i) };
		outputFile << "Provider:" << currentProvider.getName() << '\n';
		Product* currentProduct{ currentProvider.getProductHead() };
		outputFile << "Products:";
		while (currentProduct != nullptr)
		{
			outputFile << currentProduct->getName() << ',' <<
				currentProduct->getQuantity() << ';';

			currentProduct = currentProduct->getNext();
		}
		outputFile << '\n';
	}
}