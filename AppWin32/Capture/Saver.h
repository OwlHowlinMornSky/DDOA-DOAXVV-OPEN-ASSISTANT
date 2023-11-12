#pragma once

#include <opencv2/opencv.hpp>

namespace ohms {

class Saver final {
protected:
	Saver() = default;
public:
	~Saver() = default;

public:
	bool save(const cv::Mat& mat, unsigned long long time, bool c3, size_t id);

public:
	static void init();
	static Saver& instance();
	static void drop();

protected:
	static void output(cv::Mat mat, unsigned long long time, bool C3, size_t id);

protected:
	static Saver* m_instance;
};

}
