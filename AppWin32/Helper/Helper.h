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
	/**
	 * @brief 运行在子线程的任务。
	*/
	void work();

	/**
	 * @brief 子任务：作战。
	*/
	void subwork_fight();

protected:
	std::atomic_bool m_running;
	std::atomic_bool m_askedForStop;
};

}
