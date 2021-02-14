#include <iostream>
#include <fstream>

bool isPositiveNumber(char *str) {
    bool isNumber = true;
    int currIdx = 0;

    while ((str[currIdx] != '\0') && (isNumber)){
        isNumber = (std::isdigit(str[currIdx]));
        currIdx++;
    }
    
    return isNumber;
}

bool isCorrectInputFile(const std::ifstream &inputFile, std::string &message) {
    if (inputFile.eof()) {
        message = "Выход за пределы входного файла";
        return false;
    } else if (!inputFile.good()) {
        message = "Ошибка при чтении входного файла";
        return false;
    } else {
        message = "";
        return true;
    }
}

int main(int argc, char** argv) {
    if ((argc != 5) || !isPositiveNumber(argv[3]) || !isPositiveNumber(argv[4])) {
        std::cout << "Некорректные входные параметры" << std::endl;
        return 1;
    }

    char* inputFileName = argv[1];
    char* outputFileName = argv[2];
    int startPosition = std::atoi(argv[3]);
    int fragmentSize = std::atoi(argv[4]);
    std::string errorMessage;

    if ((startPosition == 0) || (fragmentSize == 0)) {
        std::cout << "Некорретные входные параметры" << std::endl;
        return 1;
    }

    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream outputFile(outputFileName, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cout << "Входной файл недоступен" << std::endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        std::cout << " Не удалось открыть или создать выходной файл" << std::endl;
        return 1;
    }
    
    inputFile.seekg(startPosition - 1, std::ios_base::beg);
    if (!isCorrectInputFile(inputFile, errorMessage))
    {
        std::cout << errorMessage << std::endl;
        return 1;
    }
    
    char* buffer = new char[fragmentSize];
    inputFile.read(buffer, fragmentSize);
    if(!isCorrectInputFile(inputFile, errorMessage)) {
        std::cout << errorMessage << std::endl;
        return 1;
    }

    outputFile.write(buffer, fragmentSize);

    inputFile.close();
    outputFile.close();
    delete[] buffer;

    std::cout << "Запись части файла прошла успешно" << std::endl;
    return 0;
}
