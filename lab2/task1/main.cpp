#include "VectorProcessing/VectorProcessing.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::string inputLine;
	std::getline(std::cin, inputLine);

	std::vector<double> numbersVector;
	try
	{
		ReadVectorFromLine(inputLine, numbersVector);
	}
	catch (std::exception& exception)
	{
		std::cout << "Error while reading vector from input file.";
	}
	DivideElementsOnHalfMaxValue(numbersVector);
	PrintVector(std::cout, numbersVector);
	return 0;
}
