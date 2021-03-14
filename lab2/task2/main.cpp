#include <iostream>
#include <iterator>
#include <string>
#include "HtmlDecoder/HtmlDecoder.h"

std::string ReadAll(std::istream &inputStream)
{
	std::istream_iterator<char> streamIterator(inputStream);
	std::istream_iterator<char> end;
	std::string results(streamIterator, end);
	return results;
}

int main() {
	std::string html = ReadAll(std::cin);
	std::cout << HtmlDecode(html) << std::endl;
    return 0;
}
