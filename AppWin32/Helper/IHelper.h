#pragma once

namespace ohms {

enum class HelperReturnMessage {
	None = 0,
	Stopped,
	BtnToStop,
	BtnToStart
};

class IHelper {
protected:
	IHelper() = default;
public:
	virtual ~IHelper() = default;

public:
	virtual bool start() = 0;
	virtual void askForStop() = 0;
	virtual bool isRunning() = 0;
};

}