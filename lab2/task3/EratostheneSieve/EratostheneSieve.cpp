#include "EratostheneSieve.h"
#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<bool> sieve;
	std::set<int> allPrimeNumbers;

	if (upperBound < 2)
	{
		return allPrimeNumbers;
	}

	sieve.resize(upperBound, true);
	sieve[0] = false;
	std::accumulate(sieve.begin(), sieve.end(), 0, [upperBound, &sieve, &allPrimeNumbers](int index, bool isPrime) -> int {
		if (isPrime)
		{
			int primeNumber = index + 1;
			allPrimeNumbers.insert(primeNumber);
			for (size_t currNumber = primeNumber; currNumber <= upperBound; currNumber += primeNumber)
			{
				sieve[currNumber - 1] = false;
			}
			sieve[primeNumber - 1] = true;
		}
		return index + 1;
	});

	return allPrimeNumbers;
}