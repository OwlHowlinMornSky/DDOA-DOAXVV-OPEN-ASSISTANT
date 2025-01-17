#pragma once

using namespace System;

namespace HelperKernel {

public interface class IHand {
public:
	bool IsOperating();
	
	void MoveCursorTo(Drawing::Point target);
	void MoveMouseWheel(bool isDown, unsigned int cnt);
	Drawing::Point GetCursorPosition();

	void ClickAt(Drawing::Point target);

	bool SetUserCursorInterceptionEnabled(bool enabled);
	bool GetUserCursorInterceptionEnabled();

	//void PressKey();
};

}
