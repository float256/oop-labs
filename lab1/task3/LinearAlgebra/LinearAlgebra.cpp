#include "LinearAlgebra.h"
#include <cmath>
#include <limits>
#include <stdexcept>

// Private functions

void fillMinorMatrix(const double (&inputMatrix)[3][3],
	double (&minorMatrix)[2][2],
	int excludedRowIdx, int excludedColIdx)
{
	int rowIdxInAlgebraicComplementMatrix = 0;
	for (int rowIdxInInputMatrix = 0; rowIdxInInputMatrix < 3;
		 rowIdxInInputMatrix++)
	{
		if (rowIdxInInputMatrix == excludedRowIdx)
		{
			continue;
		}

		int colIdxInAlgebraicComplementMatrix = 0;
		for (int colIdxInInputMatrix = 0; colIdxInInputMatrix < 3;
			 colIdxInInputMatrix++)
		{
			if (colIdxInInputMatrix == excludedColIdx)
			{
				continue;
			}
			else
			{
				minorMatrix[rowIdxInAlgebraicComplementMatrix]
								   [colIdxInAlgebraicComplementMatrix]
					= inputMatrix[rowIdxInInputMatrix]
								 [colIdxInInputMatrix];
				colIdxInAlgebraicComplementMatrix++;
			}
		}
        rowIdxInAlgebraicComplementMatrix++;
	}
}

bool IsZero(double number)
{
	double epsilon = std::numeric_limits<double>::epsilon();
	return std::abs(number) <= epsilon;
}

// Public functions

double computeDeterminant(const double (&matrix)[2][2])
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

double computeDeterminant(const double (&matrix)[3][3])
{
	double determinant = 0;
	for (int currColIdx = 0; currColIdx < 3; currColIdx++)
	{
		double minorMatrix[2][2];
		fillMinorMatrix(matrix, minorMatrix, 0, currColIdx);
		determinant += matrix[0][currColIdx] * pow(-1, currColIdx) * computeDeterminant(minorMatrix);
	}
	return determinant;
}

void computeInvertMatrix(const double (&inputMatrix)[3][3],
	double (&invertMatrix)[3][3])
{
	double matrixDeterminant = computeDeterminant(inputMatrix);
	if (IsZero(matrixDeterminant))
	{
		throw std::invalid_argument("Input matrix is singular");
	}

	double minorMatrix[2][2];
	for (int currRowIdx = 0; currRowIdx < 3; currRowIdx++)
	{
		for (int currColIdx = 0; currColIdx < 3; currColIdx++)
		{
			fillMinorMatrix(inputMatrix, minorMatrix, currRowIdx,
				currColIdx);
			double algebraicComplement = pow(-1, currRowIdx + currColIdx) * computeDeterminant(minorMatrix);
			invertMatrix[currColIdx][currRowIdx] = 1 / matrixDeterminant * algebraicComplement;
		}
	}
}
