#pragma once

namespace ohms {

class IHelper {
protected:
	IHelper() = default;
public:
	virtual ~IHelper() = default;

public:
	virtual void start() = 0;
	virtual void stop() = 0;

	virtual int update() = 0;
};

}