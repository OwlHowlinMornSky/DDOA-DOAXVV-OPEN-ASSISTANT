#pragma once

#include "IEye.h"

using namespace System;

namespace HelperKernel {

public ref class MatchCore {
public:
	MatchCore();
	virtual ~MatchCore();

protected:
	bool Match(IEye^ eye, float threshold);

	bool IsFloatingArea();

	Drawing::Rectangle GetSearchRect();
	Drawing::Rectangle GetPreviousMatchedRect();

protected:
	bool m_isFloatingArea; // 是否浮动范围查找。
	Drawing::Rectangle m_searchRect; // 查找之范围。
	Drawing::Rectangle m_prevMatchedRect; // 上次成功匹配之范围。
	cv::Mat* m_target; // 用于匹配之图案。
	cv::Mat* m_mask;   // 用于匹配之遮罩。
};

}
