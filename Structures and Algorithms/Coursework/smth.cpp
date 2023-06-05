// загрузка в файл
void FileIO::writeFirmToFile(Firm& firm)
{
	std::ofstream outputFile{ "f.txt" };
	outputFile << firm.getName() << '\n';

	for (int i{ 0 }; i <= firm.getTop(); ++i)
	{
		Provider currentProvider{ firm.getProvider(i) };
		outputFile << currentProvider.getName() << '\n';
		Product* currentProduct{ currentProvider.getProductHead() };
		
		//вывод товаров поставщика
		while (currentProduct != nullptr)
		{
			outputFile << currentProduct->getName() << ',' << currentProduct->getQuantity();

			if (currentProduct->getNext() != nullptr)
				outputFile << ';';
			else
				outputFile << '\n';

			currentProduct = currentProduct->getNext();
		}

	}
}
