#pragma once

#include <string>

namespace ohms {

/**
 * @brief logger接口
*/
class ILogger {
public:
	/**
	 * @brief 添加一行
	 * @param str 字符串
	*/
	virtual void addString(std::wstring_view str) = 0;
	/**
	 * @brief 清空
	*/
	virtual void clear() = 0;
};

} // namespace ohms
