#define CATCH_CONFIG_MAIN

#include "../VectorProcessing/VectorProcessing.h"
#include "catch.hpp"
#include <limits>

TEST_CASE("Reading vector from line is correct", "[ReadVectorFromLine]")
{
	std::vector<double> expectedOutputVector, actualOutputVector;
	std::string inputLine;

	SECTION("Empty input line")
	{
		inputLine = "";
		ReadVectorFromLine(inputLine, actualOutputVector);
		expectedOutputVector.clear();

		REQUIRE(expectedOutputVector.size() == actualOutputVector.size());
		REQUIRE_THAT( expectedOutputVector, Catch::Approx(actualOutputVector));
	}

	SECTION("Not empty input line with small amount of numbers")
	{
		inputLine = "  1 2.18237     3.42 3.768 5.7 85.12342               3.4";
		ReadVectorFromLine(inputLine, actualOutputVector);
		expectedOutputVector = { 1, 2.18237, 3.42, 3.768, 5.7, 85.12342, 3.4 };

		REQUIRE(expectedOutputVector.size() == actualOutputVector.size());
		REQUIRE_THAT( expectedOutputVector, Catch::Approx(actualOutputVector));
	}

	SECTION("Very small numbers")
	{
		inputLine = "1.123313e-200 0.32e-123 3.487592e-198 0 3.14159e-244 ";
		ReadVectorFromLine(inputLine, actualOutputVector);
		expectedOutputVector = { 1.123313e-200, 0.32e-123, 3.487592e-198, 0, 3.14159e-244};

		REQUIRE(expectedOutputVector.size() == actualOutputVector.size());
		REQUIRE_THAT( expectedOutputVector, Catch::Approx(actualOutputVector));
	}

	SECTION("Very big numbers")
	{
		inputLine = "1.113e221 0.32e123 3.487592e138 1e200 3.14159e244 ";
		ReadVectorFromLine(inputLine, actualOutputVector);
		expectedOutputVector = { 1.113e221, 0.32e123, 3.487592e138, 1e200, 3.14159e244};

		REQUIRE(expectedOutputVector.size() == actualOutputVector.size());
		REQUIRE_THAT( expectedOutputVector, Catch::Approx(actualOutputVector));
	}

	SECTION("Incorrect input line")
	{
		inputLine = " 1 2 QWERTY ";
		REQUIRE_THROWS(ReadVectorFromLine(inputLine, actualOutputVector));
	}
}