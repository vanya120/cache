#ifndef CACHE_BASE_H
#define CACHE_BASE_H

#include <iostream>

template <typename Key, typename Value>
class Cache
{
protected:
	const int size_;

public:
	Cache() : size_(0) {}

	virtual const Value& getValue(const Key& key) const = 0;
	virtual void setValue(std::pair<Key, Value> p) = 0;
	virtual void throwValue() = 0;

	//virtual ~Cache();
};


#endif // CACHE_BASE_H
