#pragma once

#include "API.h"
#include "Time.h"

namespace ohms {

/**
 * @brief 精确时钟。
*/
class CORE_API Clock final {
public:
	Clock();

	/**
	 * @brief 获取上次restart以来经过的时间
	 * @return 经过的时间
	*/
	Time getElapsedTime() const;
	/**
	 * @brief 重新开始计时（重设开始时间）
	 * @return 经过的时间
	*/
	Time restart();

protected:
	Time m_startTime; // 开始时间
};

} // namespace ohms
