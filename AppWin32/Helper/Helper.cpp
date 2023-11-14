#include "Helper.h"

#include "../Global.h"
#include <opencv2/opencv.hpp>

#include <thread>
#include <iostream>

namespace ohms {

Helper::Helper() :
	m_askedForStop(false),
	m_running(false) {}

Helper::~Helper() {}

bool Helper::start() {
	if (m_running) {
		std::cout << "It is now running!" << std::endl;
		return false;
	}
	m_askedForStop = false;
	std::thread sub(&Helper::work, this);
	sub.detach();
	return !sub.joinable();
}

void Helper::askForStop() {
	m_askedForStop = true;
	return;
}

bool Helper::isRunning() {
	return m_running;
}

void Helper::work() {
	m_running = true;
	ohms::global::pushHRM(HelperReturnMessage::BtnToStop);

	// Run subworks.
	subwork_fight();

	m_running = false;
	ohms::global::pushHRM(HelperReturnMessage::Stopped);
	ohms::global::pushHRM(HelperReturnMessage::BtnToStart);
	return;
}

void Helper::subwork_fight() {
	MSG msg;
	while (!m_askedForStop) {
		if (PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else {
			if (ohms::global::capture->isRefreshed()) {
				auto mat = ohms::global::capture->getMat();
				if (mat != nullptr) {
					cv::imshow("show", *mat);
				}
			}
			ohms::global::capture->askForRefresh();
			Sleep(30);
		}
	}
	cv::destroyAllWindows();
}

}
