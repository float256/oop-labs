#include <iostream>
#include <set>
#include "EratostheneSieve/EratostheneSieve.h"

void Print(std::ostream& outputStream, const std::set<int> &vectorForPrinting)
{
	for (auto currNumber: vectorForPrinting)
	{
		outputStream << currNumber << ' ';
	}
	outputStream << std::endl;
}

int main()
{
	int upperBound;
	std::cin >> upperBound;
	if (!std::cin.fail())
	{
		Print(std::cout, GeneratePrimeNumbersSet(upperBound));
		return 0;
	}
	else
	{
		std::cout << "Incorrect input.";
		return 1;
	}
}
