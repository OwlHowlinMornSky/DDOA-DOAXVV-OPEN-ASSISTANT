#pragma once

#include <string>

namespace ohms {

class ILogger {
public:
	virtual void addString(std::wstring_view str) = 0;
	virtual void clear() = 0;
};

} // namespace ohms
