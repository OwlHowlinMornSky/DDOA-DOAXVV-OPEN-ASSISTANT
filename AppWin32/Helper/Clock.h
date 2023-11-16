#pragma once

#include "Time.h"

namespace ohms {

class Clock final {
public:
	Clock();

	Time getElapsedTime() const;
	Time restart();

protected:
	Time m_startTime;
};

}
