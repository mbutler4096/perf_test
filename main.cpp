#pragma warning( disable : 4996 )

#include "performance.h"
#include <vector>
#include <iostream>
#include <stdint.h>


using namespace std;


struct data_4b
{
	int key;

	bool operator< (const data_4b& rhs)
	{
		return key < rhs.key;
	}
};

struct data_4k
{
	int key;
	int value[1024];

	bool operator< (const data_4k& rhs)
	{
		return key < rhs.key;
	}
};


int main()
{
	srand(time(0));

	cout << "4b elements:\n";
	cout << "Small set results:\n";
	vector<int> vec_small = { 100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };
	for (const auto& n : vec_small)
	{
		performance::test<data_4b> test;

		cout << test.vector(n) << "\n";
		cout << test.optimized_vector(n) << "\n";
		cout << test.list(n) << "\n";

		cout << n << " elements complete\n";
	}

	cout << "4K elements:\n";
	cout << "Small set results:\n";
	for (const auto& n : vec_small)
	{
		performance::test<data_4k> test;

		cout << test.vector(n) << "\n";
		cout << test.optimized_vector(n) << "\n";
		cout << test.list(n) << "\n";

		cout << n << " elements complete\n";
	}

 	return 0;
}
