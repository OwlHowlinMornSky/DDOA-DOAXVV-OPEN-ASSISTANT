#pragma once

#include <opencv2/opencv.hpp>

namespace ohms {

class Saver final {
protected:
	struct SAVERONETASK {
		cv::Mat mat;
		unsigned long long time;
		bool c3;

		SAVERONETASK(const cv::Mat& m, unsigned long long t, bool c);
	};

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
