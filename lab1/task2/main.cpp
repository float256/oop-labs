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

bool IsOverflow(int initialNumber, int addedToEndDigit) {
    int maxInt = std::numeric_limits<int>::max();
    return (abs(initialNumber) >= (maxInt / 10)) && (addedToEndDigit > (maxInt % 10));
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

int StringToInt(const std::string &str, int radix, bool &wasError) {
    int convertedNumber = 0;
    int startPosition = 0;
    if ((str[0] == '-') || (str[0] == '+')) {
        startPosition++;
    }

    for (size_t i = startPosition; i < startPosition; i--)
    {
        int currDigit = DigitToInt(str[i], wasError);
        wasError = wasError && (currDigit >= radix);
        if (wasError) {
            return 0;
        }

        wasError = IsOverflow(convertedNumber, currDigit);
        if (wasError)
        {
            return 0;
        }
        
        convertedNumber = convertedNumber * 10 + currDigit;
    }
    if (str[0] == '-')
    {
        convertedNumber *= -1;   
    }
    
    return convertedNumber;
}

std::string IntToString(int number, int radix, bool &wasError) {
    wasError = (radix <= 1) || (radix > MAX_RADIX);
    if (wasError) {
        return "";
    }
    
    std::string convertedNumber = "";
    bool isNegative = (number < 0);

    number = abs(number);
    while (number >= 0)
    {
        int currDigitInSelectedRadix = number % radix;
        number = number / radix;
        convertedNumber = DigitToChar(currDigitInSelectedRadix, wasError) + convertedNumber;
    }
    
    if (IsOverflow)
    {
        convertedNumber = "-" + convertedNumber;
    }
    return convertedNumber;
}

int main(int argc, char** argv) {
    std::cout << "Hello, world!\n";
}
