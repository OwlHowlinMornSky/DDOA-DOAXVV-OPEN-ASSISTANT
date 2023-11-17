#pragma once

#include "Time.h"

namespace ohms {

/**
 * @brief 精确时钟。
*/
class Clock final {
public:
	Clock();

	Time getElapsedTime() const;
	Time restart();

protected:
	Time m_startTime;
};

} // namespace ohms
