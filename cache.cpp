#include "lru.h"
#include "cache_time.h"
#include "cache_exception.h"

constexpr int MAX_CACHE_SIZE{ 1000 };

// For example doing excpetion with LRU
template <typename Key, typename Value>
void get_or_exception(LRU<Key, Value> cache, const Key& key)
{
	try
	{
		std::cout << cache.getValue(key) << '\n';
	} 
	catch (CacheException<decltype(cache)> &exception)
	{
		std::cerr << "Exception caught: " << exception.stringWhat() << '\n';
	}
}

int main()
{
	LRU<int, int> lru{};
	lru.setValue({ 1, 3 });
	lru.setValue({ 2, 4 });
	lru.setValue({ 2, 6 });

	lru.setValue({ 2, 5 });

	std::cout << lru.timeQueue_ << std::endl;
	get_or_exception<int, int>(lru, 2);
	get_or_exception<int, int>(lru, 3);
	get_or_exception<int, int>(lru, 1);



	return 0;
}