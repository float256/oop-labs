#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

typedef struct
{
	int RowIdx;
	int ColIdx;
} CellCoordinate;

enum class CellInfo
{
	Empty,
	Filled,
	Wall,
	Start
};
const size_t FIELD_SIZE = 100;

bool IsValidForFillingCell(int rowIdx, int colIdx, const CellInfo (&field)[FIELD_SIZE][FIELD_SIZE])
{
	return (colIdx >= 0) && (colIdx < FIELD_SIZE) && (rowIdx >= 0) && (rowIdx < FIELD_SIZE)
		&& (field[rowIdx][colIdx] == CellInfo::Empty);
}

void FillField(CellInfo (&field)[FIELD_SIZE][FIELD_SIZE], const CellCoordinate& startCellCoordinates)
{
	std::queue<CellCoordinate> consideredPointsCoordinates;
	consideredPointsCoordinates.push(startCellCoordinates);
	while (!consideredPointsCoordinates.empty())
	{
		CellCoordinate currCellCoordinate = consideredPointsCoordinates.front();
		consideredPointsCoordinates.pop();
		int currRowIdx = currCellCoordinate.RowIdx;
		int currColIdx = currCellCoordinate.ColIdx;

		if (IsValidForFillingCell(currRowIdx, currColIdx + 1, field))
		{
			field[currRowIdx][currColIdx + 1] = CellInfo::Filled;
			consideredPointsCoordinates.push({ .RowIdx = currRowIdx,
				.ColIdx = currColIdx + 1 });
		}
		if (IsValidForFillingCell(currRowIdx, currColIdx - 1, field))
		{
			field[currRowIdx][currColIdx - 1] = CellInfo::Filled;
			consideredPointsCoordinates.push({ .RowIdx = currRowIdx,
				.ColIdx = currColIdx - 1 });
		}
		if (IsValidForFillingCell(currRowIdx + 1, currColIdx, field))
		{
			field[currRowIdx + 1][currColIdx] = CellInfo::Filled;
			consideredPointsCoordinates.push({ .RowIdx = currRowIdx + 1,
				.ColIdx = currColIdx });
		}
		if (IsValidForFillingCell(currRowIdx - 1, currColIdx, field))
		{
			field[currRowIdx - 1][currColIdx] = CellInfo::Filled;
			consideredPointsCoordinates.push({ .RowIdx = currRowIdx - 1,
				.ColIdx = currColIdx });
		}
	}
}

void FillField(CellInfo (&field)[FIELD_SIZE][FIELD_SIZE], const std::vector<CellCoordinate>& startCellCoordinates)
{
	for (auto& cell : startCellCoordinates)
	{
		FillField(field, cell);
	}
}

void CreateFieldFromFile(std::istream& inputStream, CellInfo (&field)[FIELD_SIZE][FIELD_SIZE], std::vector<CellCoordinate>& startCellCoordinates)
{
	int currRowIdx = 0;

	std::string currLine;
	startCellCoordinates.clear();
	while (std::getline(inputStream, currLine) && (currRowIdx < FIELD_SIZE))
	{
		for (int currCellIdx = 0; currCellIdx < std::min(currLine.length(), FIELD_SIZE); currCellIdx++)
		{
			char currSymbol = currLine[currCellIdx];
			CellInfo currCellState;

			if (currSymbol == ' ')
			{
				currCellState = CellInfo::Empty;
			}
			else if (currSymbol == '.')
			{
				currCellState = CellInfo::Filled;
			}
			else if (currSymbol == '#')
			{
				currCellState = CellInfo::Wall;
			}
			else if (currSymbol == 'O')
			{
				currCellState = CellInfo::Start;
				startCellCoordinates.push_back({ .RowIdx = currRowIdx,
					.ColIdx = currCellIdx });
			}
			else
			{
				throw std::invalid_argument("Invalid character found in input file.");
			}

			field[currRowIdx][currCellIdx] = currCellState;
		}

		currRowIdx++;
	}
}

void WriteFieldInFile(std::ostream& outputStream, const CellInfo (&field)[FIELD_SIZE][FIELD_SIZE])
{
	for (size_t currRowIdx = 0; currRowIdx < FIELD_SIZE; currRowIdx++)
	{
		for (size_t currCellIdx = 0; currCellIdx < FIELD_SIZE; currCellIdx++)
		{
			if (field[currRowIdx][currCellIdx] == CellInfo::Empty)
			{
				outputStream << ' ';
			}
			else if (field[currRowIdx][currCellIdx] == CellInfo::Filled)
			{
				outputStream << '.';
			}
			else if (field[currRowIdx][currCellIdx] == CellInfo::Wall)
			{
				outputStream << '#';
			}
			else if (field[currRowIdx][currCellIdx] == CellInfo::Start)
			{
				outputStream << 'O';
			}
		}
		outputStream << std::endl;
	}
}

int main(int argc, char** argv)
{
	if (argc != 3)
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

	std::ofstream outputFile(argv[2]);
	if (!outputFile.is_open())
	{
		std::cout << "Could not create output file." << std::endl;
		return 1;
	}

	try
	{
		CellInfo field[FIELD_SIZE][FIELD_SIZE] = { CellInfo::Empty };
		std::vector<CellCoordinate> startCellCoordinates;

		CreateFieldFromFile(inputFile, field, startCellCoordinates);
		FillField(field, startCellCoordinates);
		WriteFieldInFile(outputFile, field);
	}
	catch (std::exception& exception)
	{
		std::cout << "Error: " << exception.what() << std::endl;
		return 1;
	}

	return 0;
}
