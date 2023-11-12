
#include "Saver.h"

#include <queue>
#include <thread>
#include <atomic>
#include <mutex>

#include "../framework.h"

#include <stdlib.h>
#include <io.h>
#include <stdio.h>

namespace {

struct SAVERONETASK {
	cv::Mat mat;
	unsigned long long time;
	bool c3;

	SAVERONETASK(const cv::Mat& m, unsigned long long t, bool c);
};

SAVERONETASK::SAVERONETASK(const cv::Mat& m, unsigned long long t, bool c) :
	mat(m),
	time(t),
	c3(c) {}

} // namespace

namespace ohms {

Saver* Saver::m_instance = nullptr;

bool Saver::save(const cv::Mat& mat, unsigned long long time, bool C3, size_t id) {
	std::thread sub(Saver::output, mat, time, C3, id);
	sub.detach();
	return !sub.joinable();
}

void Saver::init() {
	assert(m_instance == nullptr);
	m_instance = new Saver;
}

Saver& Saver::instance() {
	assert(m_instance != nullptr);
	return *m_instance;
}

void Saver::drop() {
	assert(m_instance != nullptr);
	delete m_instance;
}

void Saver::output(cv::Mat mat, unsigned long long time, bool c3, size_t id) {
	if (c3)
		cv::cvtColor(mat, mat, cv::ColorConversionCodes::COLOR_BGRA2BGR, 3);

	std::string name("./");
	name.append(std::to_string(time));
	name.append("-");
	name.append(std::to_string(id));

	/*
	if (_access_s((name + ".png").c_str(), 0) == 0) {
		size_t rk = 1;
		name.append("_");
		for (; rk < 65536; ++rk) {
			if (_access_s((name + std::to_string(rk) + ".png").c_str(), 0) != 0) {
				break;
			}
		}
		if (rk == 65536) {
			MessageBoxW(NULL, L"Filename contract.", L"ERROR when SAVING IMAGE", MB_ICONERROR);
			return;
		}
		name.append(std::to_string(rk));
	}*/

	name.append(".png");

	if (!cv::imwrite(name, mat)) {
		MessageBoxW(NULL, L"OpenCV:\ncv::imwrite() failed!", L"ERROR when SAVING IMAGE", MB_ICONERROR);
	}
}

} // namespace ohms
