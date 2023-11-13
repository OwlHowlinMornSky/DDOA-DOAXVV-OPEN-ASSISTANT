#include "Helper.h"

#include "../Global.h"
#include <opencv2/opencv.hpp>

namespace ohms {

Helper::Helper() :
	m_cmd(HelperMessage::None),
	running(false) {}

Helper::~Helper() {}

void Helper::set(HelperMessage h) {
	m_cmd = h;
	return;
}

void ohms::Helper::update() {
	switch (m_cmd) {
	case HelperMessage::None:
		break;
	case HelperMessage::Start:
	{
		HWND dst = FindWindowW(L"DOAX VenusVacation", L"DOAX VenusVacation");
		if (dst == NULL) {
			printf_s("Cannot find DOAXVV window.\n");
			break;
		}
		if (!IsWindow(dst)) {
			printf_s("Target is not a widnow.\n");
			break;
		}
		if (IsIconic(dst)) {
			printf_s("Target is minimized.\n");
			break;
		}
		if (!ohms::global::capture->startCapture(dst)) {
			printf_s("Target cannot be captured.\n");
			break;
		}
		running = true;
		ohms::global::helperReturnMessage.push(HelperReturnMessage::BtnToStop);
		break;
	}
	case HelperMessage::Stop:
	{
		if (!running) {
			printf_s("It is not running.\n");
			break;
		}
		running = false;
		ohms::global::capture->stopCapture();
		cv::destroyAllWindows();
		ohms::global::helperReturnMessage.push(HelperReturnMessage::BtnToStart);
		break;
	}
	}
	m_cmd = HelperMessage::None;
	if (running) {
		if (ohms::global::capture->isRefreshed()) {
			auto mat = ohms::global::capture->getMat();
			if (mat != nullptr) {
				cv::imshow("show", *mat);
			}
		}
		ohms::global::capture->askForRefresh();
	}
	return;
}

}
