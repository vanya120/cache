#ifndef CACHE_TIME_H
#define CACHE_TIME_H

#include <iostream>
#include <chrono>

struct Time
{
	std::chrono::steady_clock::time_point value = std::chrono::steady_clock::now();
};

bool operator< (const Time& lhs, const Time& rhs)
{
	auto duration = rhs.value - lhs.value;
	auto nsTime = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
	return nsTime > 0;
}


template <typename Key>
class CompareTime
{
public:
	bool operator() (const std::pair<Time, Key>& lhs, const std::pair<Time, Key>& rhs)
	{
		return lhs.first < rhs.first;
	}
};

#endif // CACHE_TIME_H