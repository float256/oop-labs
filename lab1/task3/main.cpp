#include "LinearAlgebra/LinearAlgebra.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

bool isOnlySpaces(const std::string& inputString)
{
	bool isOnlySpacesInInputString = true;
	for (auto& currChar : inputString)
	{
		isOnlySpacesInInputString = (isOnlySpacesInInputString && std::isspace(currChar));
		if (!isOnlySpacesInInputString)
		{
			break;
		}
	}
	return isOnlySpacesInInputString;
}

void readMatrixFromFile(std::istream& inputStream, double (&matrix)[3][3])
{
	for (size_t currRowIdx = 0; currRowIdx < 3; currRowIdx++)
	{
		for (size_t currColIdx = 0; currColIdx < 3; currColIdx++)
		{
			double currNumber;
			inputStream >> currNumber;

			if (inputStream.fail())
			{
				throw std::invalid_argument("Incorrect matrix data in file");
			}

			matrix[currRowIdx][currColIdx] = currNumber;
		}

		std::string remainderStr;
		std::getline(inputStream, remainderStr);
		if (!isOnlySpaces(remainderStr))
		{
			throw std::invalid_argument("Extra characters at the end of the line.");
		}
	}
}

void writeMatrixInStream(std::ostream& outputStream, double (&matrix)[3][3])
{
	for (size_t currRowIdx = 0; currRowIdx < 3; currRowIdx++)
	{
		for (size_t currColIdx = 0; currColIdx < 3; currColIdx++)
		{
			outputStream << std::fixed << std::setprecision(3) << matrix[currRowIdx][currColIdx] << " ";
		}
		outputStream << std::endl;
	}
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Incorrect number of arguments." << std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		std::cout << "Could not open input file." << std::endl;
		return 1;
	}

	try
	{
		double matrix[3][3];
		double invertedMatrix[3][3];

		readMatrixFromFile(inputFile, matrix);
		computeInvertMatrix(matrix, invertedMatrix);
		writeMatrixInStream(std::cout, invertedMatrix);
	}
	catch (std::exception& exception)
	{
		std::cout << "Error: " << exception.what() << std::endl;
		return 1;
	}

	return 0;
}
