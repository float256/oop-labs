#include <iostream>
#include <string>
#include <map>
#include <limits>

const char ALL_DIGITS_IN_ORDER[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'};

const int MAX_RADIX = 36;

char DigitToChar (int digit, bool &wasError) {
    wasError = (digit < 0) || (digit >= MAX_RADIX);
    if (wasError)
    {
        return '\0';
    }
    return ALL_DIGITS_IN_ORDER[digit];
}

int DigitToInt (char digit, bool &wasError) {
    wasError = false;
    for (size_t i = 0; i < MAX_RADIX; i++)
    {
        if (ALL_DIGITS_IN_ORDER[i] == digit)
        {
            return i;
        }
    }
    wasError = true;
    return -1;
}

bool IsOverflow(int initialNumber, int addedToEndDigit, int radix) {
    int maxInt = std::numeric_limits<int>::max();
    return (abs(initialNumber) >= (maxInt / radix)) && (addedToEndDigit > (maxInt % radix));
}

bool IsDecimal(const std::string &numberInString) {
    bool isTransmittedNumberDecimal = true;
    for (char currSymbol : numberInString)
    {
        isTransmittedNumberDecimal = std::isdigit(currSymbol);
        if (!isTransmittedNumberDecimal)
        {
            break;            
        }
    }
    
    return isTransmittedNumberDecimal;
}

bool IsCorrectRadix(int radix) {
    return (radix > 1) && (radix <= MAX_RADIX);
}

int StringToInt(const std::string &str, int radix, bool &wasError) {
    int convertedNumber = 0;
    int startPosition = 0;
    if ((str[0] == '-') || (str[0] == '+')) {
        startPosition++;
    }

    for (size_t i = startPosition; i < str.length(); i++)
    {
        int currDigit = DigitToInt(str[i], wasError);
        wasError = wasError || (currDigit > radix);
        if (wasError) {
            return 0;
        }

        wasError = IsOverflow(convertedNumber, currDigit, radix);
        if (wasError)
        {
            return 0;
        }
        
        convertedNumber = convertedNumber * radix + currDigit;
    }
    if (str[0] == '-')
    {
        convertedNumber *= -1;   
    }
    return convertedNumber;
}

std::string IntToString(int number, int radix, bool &wasError) {
    wasError = !IsCorrectRadix(radix);
    if (wasError) {
        return "";
    }
    
    if (number == 0) {
        return "0";
    }

    std::string convertedNumber = "";
    bool isNegative = (number < 0);

    number = abs(number);
    while (number > 0)
    {
        int currDigitInSelectedRadix = number % radix;
        number = number / radix;
        convertedNumber = DigitToChar(currDigitInSelectedRadix, wasError) + convertedNumber;
    }
    
    if (isNegative)
    {
        convertedNumber = "-" + convertedNumber;
    }
    return convertedNumber;
}

int main(int argc, char** argv) {
    if ((argc != 4))
    {
        std::cout << "Incorrect number of arguments." << std::endl;
        return 1;
    }
    if(!IsDecimal(argv[1]) || !IsDecimal(argv[2])) {
        std::cout << "Incorrect arguments." << std::endl;
        return 1;
    }

    bool wasError = false;
    int sourceNotation = StringToInt(argv[1], 10, wasError);
    wasError = (wasError || !IsCorrectRadix(sourceNotation));
    if (wasError) {
        std::cout << "Incorrect source notation." << std::endl;
        return 1;
    }
    int destinationNotation = StringToInt(argv[2], 10, wasError);
    wasError = (wasError || !IsCorrectRadix(destinationNotation));
    if (wasError) {
        std::cout << "Incorrect destination notation." << std::endl;
        return 1;
    }
    int numberForConverting = StringToInt(argv[3], sourceNotation, wasError);
    if (wasError) {
        std::cout << "Error while parsing a number." << std::endl;
        return 1;
    }

    std::string numberInDestinationNotation = IntToString(numberForConverting, destinationNotation, wasError);
    if (wasError) {
        std::cout << "Error while converting number in destination notation" << std::endl;
        return 1;
    }
    std::cout << numberInDestinationNotation << std::endl;
    return 0;
}
