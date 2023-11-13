#pragma once

namespace ohms {

enum class HelperMessage {
	None = 0,
	Start,
	Stop
};

enum class HelperReturnMessage {
	BtnToStop = 0,
	BtnToStart,
	BtnToWaitingForStop
};

class IHelper {
protected:
	IHelper() = default;
public:
	virtual ~IHelper() = default;

public:
	virtual void set(HelperMessage h) = 0;
	virtual void update() = 0;
};

}