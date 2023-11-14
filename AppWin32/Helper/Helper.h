#pragma once

#include "IHelper.h"
#include <mutex>
#include <atomic>

namespace ohms {

class Helper final :
	public IHelper {
public:
	Helper();
	virtual ~Helper() override;

public:
	virtual bool start() override;
	virtual void askForStop() override;
	virtual bool isRunning() override;

protected:
	void work();

	void subwork_fight();

protected:
	std::atomic_bool m_running;
	std::atomic_bool m_askedForStop;
};

}
