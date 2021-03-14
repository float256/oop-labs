#include "VectorProcessing.h"
#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>

void ReadVectorFromLine(const std::string& line, std::vector<double>& outputVector)
{
	std::stringstream stream(line);
	std::string currString;
	while (std::getline(stream, currString, ' '))
	{
		if (!currString.empty())
		{
			double currNumber = std::stod(currString);
			outputVector.push_back(currNumber);
		}
	}
}

void DivideElementsOnHalfMaxValue(std::vector<double>& inputVector)
{
	if (!inputVector.empty())
	{
		double maxValue = *std::max_element(inputVector.begin(), inputVector.end());
		for (auto& currElement : inputVector)
		{
			currElement /= (maxValue / 2);
		}
	}
}

void PrintVector(std::ostream& outputStream, const std::vector<double>& vectorForPrinting)
{
	for (auto& currElement : vectorForPrinting)
	{
		outputStream << currElement << " ";
	}
	outputStream << std::endl;
}
