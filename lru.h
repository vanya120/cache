#ifndef LRU_H
#define LRU_H

#include <unordered_map>
#include <vector>
#include <queue>

#include "cache_base.h"
#include "cache_time.h"
#include "cache_exception.h"

template <typename Key>
using cache_queue = std::priority_queue< std::pair<Time, Key>,
	std::vector< std::pair<Time, Key> >, CompareTime<Key> >;

template <typename Key, typename Value>
class LRU : public Cache<Key, Value>
{
	std::unordered_map<Key, Value> cacheTable_{};

	// temp public for outputing
public:
	cache_queue<Key> timeQueue_{};

public:
	const Value& getValue(const Key& key) const override;
	void setValue(std::pair<Key, Value> p) override;
	void throwValue() override;
};

template <typename Key, typename Value>
const Value& LRU<Key, Value>::getValue(const Key& key) const
{
	auto it = cacheTable_.find(key);
	if (it == cacheTable_.end())
		throw CacheException<LRU<Key, Value>>("Key isn't in cache");

	return it->second;
}

template <typename Key, typename Value>
void LRU<Key, Value>::setValue(std::pair<Key, Value> p)
{
	if (this->size_ == MAX_CACHE_SIZE)
		throwValue();

	cacheTable_.insert(p);
	timeQueue_.push({ Time(), p.first });
}

template <typename Key, typename Value>
void LRU<Key, Value>::throwValue()
{
	auto trash = timeQueue_.top();
	timeQueue_.pop();
	cacheTable_.erase(cacheTable_.find(trash.second));
}

//outout for debugging
template <typename Key>
std::ostream& operator << (std::ostream& stream, cache_queue<Key>& q) 
{
	while (!q.empty()) 
	{
		auto& top = q.top();
		stream << top.second << ' ';
		q.pop();
	}
	return stream;
}

//special Ctor for cheking of LRU<int, int>
template<>
CacheException<LRU<int, int>>::CacheException(const std::string& what)
	: runtime_error(""), what_(what), info_("LRU") {}


#endif // LRU_H