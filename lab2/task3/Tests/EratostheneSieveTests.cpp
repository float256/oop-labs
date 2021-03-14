#define CATCH_CONFIG_MAIN

#include "../../../libs/catch2/catch.hpp"
#include "../EratostheneSieve/EratostheneSieve.h"
#include <limits>

SCENARIO("EratostheneSieve")
{
	WHEN("Small upper bound")
	{
		int upperBound = 400;
		std::set<int> expectedPrimeNumbers = {
			2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
			41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
			89, 97, 101, 103, 107, 109, 113, 127, 131,
			137, 139, 149, 151, 157, 163, 167, 173, 179,
			181, 191, 193, 197, 199, 211, 223, 227, 229,
			233, 239, 241, 251, 257, 263, 269, 271, 277,
			281, 283, 293, 307, 311, 313, 317, 331, 337,
			347, 349, 353, 359, 367, 373, 379, 383, 389,
			397
		};
		THEN("")
		{
			CHECK(expectedPrimeNumbers == GeneratePrimeNumbersSet(upperBound));
		}
	}

	WHEN("Upper bound is smallest prime number")
	{
		int upperBound = 2;
		std::set<int> expectedOutput = { 2 };
		THEN("Only one prime number was found")
		{
			CHECK(expectedOutput == GeneratePrimeNumbersSet(upperBound));
		}
	}

	WHEN("Highest upper bound")
	{
		int upperBound = 100000000;
		int expectedSetSize = 5761455;
		THEN("Amount of prime numbers found is the same as expected.")
		{
			CHECK(expectedSetSize == GeneratePrimeNumbersSet(upperBound).size());
		}
	}

	WHEN("Upper bound is zero")
	{
		int upperBound = 0;
		std::set<int> expectedPrimeNumbers, actualPrimeNumbers;
		expectedPrimeNumbers = {};
		THEN("Prime numbers are not found.")
		{
			actualPrimeNumbers = GeneratePrimeNumbersSet(upperBound);
			CHECK(expectedPrimeNumbers.size() == actualPrimeNumbers.size());
			CHECK(expectedPrimeNumbers == actualPrimeNumbers);
		}
	}

	WHEN("Upper bound is newgative number")
	{
		int upperBound = -120;
		std::set<int> expectedPrimeNumbers, actualPrimeNumbers;
		expectedPrimeNumbers = {};
		THEN("Prime numbers are not found.")
		{
			actualPrimeNumbers = GeneratePrimeNumbersSet(upperBound);
			CHECK(expectedPrimeNumbers.size() == actualPrimeNumbers.size());
			CHECK(expectedPrimeNumbers == actualPrimeNumbers);
		}
	}
}