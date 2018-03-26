#include <vector>
#include <list>
#include <algorithm>
#include "high_resolution_timer.h"

namespace performance
{
	template<class T>
	struct test
	{
		double optimized_vector(const int n);
		double vector(const int n);
		double list(const int n);

		std::vector<T> vec;
		std::vector<T> opt_vec;
		std::list<T> ll;
	};

	template<class T>
	double test<T>::optimized_vector(const int n)
	{
		int rand_num, count = 0;
		auto it = opt_vec.begin();

		opt_vec.reserve(n);

		high_resolution_timer t = high_resolution_timer();

		//insert
		while (count < n)
		{
			rand_num = rand();

			T element;
			element.key = rand_num;

			it = std::lower_bound(opt_vec.begin(), opt_vec.end(), element);
			opt_vec.insert(it, element);

			++count;
		}

		//remove
		while (count > 0)
		{
			//using the form: rand()%(max-min + 1) + min;
			rand_num = rand() % count;
			opt_vec.erase(opt_vec.begin() + rand_num);

			--count;
		}

		double elapsed = t.elapsed();

		if (opt_vec.size() > 0)
			std::cout << "Optimized vector not empty\n";

		return elapsed;
	}

	template<class T>
	double test<T>::vector(const int n)
	{
		int rand_num, count = 0, i;
		auto it = vec.begin();

		high_resolution_timer t = high_resolution_timer();

		//insert
		while (count < n)
		{
			T element;
			element.key = rand();

			for (i = 0; i < count; ++i)
				if (element < vec[i])
					break;
			vec.insert(vec.begin() + i, element);

			++count;
		}

		//remove
		while (count > 0)
		{
			//using the form: rand()%(max-min + 1) + min;
			rand_num = rand() % count;
			vec.erase(vec.begin() + rand_num);

			--count;
		}

		double elapsed = t.elapsed();

		if (vec.size() > 0)
			std::cout << "Vector not empty\n";

		return elapsed;
	}

	template<class T>
	double test<T>::list(const int n)
	{
		int rand_num, count = 0;
		auto it = ll.begin();

		high_resolution_timer t = high_resolution_timer();

		//insert
		while (count < n)
		{
			T element;
			element.key = rand();

			for (it = ll.begin(); it != ll.end(); ++it)
				if (element < *it) break;

			ll.insert(it, element);

			++count;
		}

		//remove
		while (count > 0)
		{
			//using the form: rand()%(max-min + 1) + min;
			rand_num = rand() % count;

			it = ll.begin();
			advance(it, rand_num);
			ll.erase(it);

			--count;
		}

		double elapsed = t.elapsed();

		if (ll.size() > 0)
			std::cout << "List not empty\n";

		return elapsed;
	}
}
