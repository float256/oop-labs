//
// Created by user on 13.03.2021.
//

#ifndef TASK1_VECTORPROCESSING_H
#define TASK1_VECTORPROCESSING_H

#include <string>
#include <vector>

void ReadVectorFromLine(const std::string& line, std::vector<double>& outputVector);
void DivideElementsOnHalfMaxValue(std::vector<double>& inputVector);
void PrintVector(std::ostream& outputStream, const std::vector<double>& vectorForPrinting);

#endif //TASK1_VECTORPROCESSING_H
