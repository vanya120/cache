#ifndef CACHE_EXCEPTION_H
#define CACHE_EXCEPTION_H

#include <sstream>
#include <string>

template <typename CacheType>
class CacheException : public std::runtime_error
{
private:
	const std::string what_{};
	const std::string info_{};

public:
	CacheException(const std::string& what) : what_(what) {}

	std::string stringWhat() noexcept
	{
		std::ostringstream out_str;
		out_str << info_ << " : " << what_;
		std::string ans = out_str.str();
		return ans;
	}
};

#endif // CACHE_EXCEPTION_H