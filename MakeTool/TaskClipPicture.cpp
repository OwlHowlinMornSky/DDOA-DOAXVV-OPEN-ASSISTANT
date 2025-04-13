#include "TaskClipPicture.h"

#include <opencv2/opencv.hpp>

#include <fstream>
#include <filesystem>

namespace {

constexpr char RectedWndName[] = "Original";
constexpr char ClippedWndName[] = "Result";

cv::Mat original;
cv::Mat rected;
cv::Mat clipped;
cv::Mat clippedShow;

cv::Rect finalrect;
std::filesystem::path filepath;

std::vector<cv::Point> g_points;

void OnMouseEvent_Processed(int msg, int x, int y, int flag, void* userdata) {
	switch (msg) {
	case cv::EVENT_RBUTTONUP:
	{
		auto t = time(0);

		std::string tt = "[clip-" + std::to_string(t) + "]";
		std::string filename = filepath.stem().concat(tt).string();

		//std::string finalpath = (filepath.parent_path() / filename).string();
		std::string finalpath = filename;

		cv::imwrite(finalpath + ".png", clipped);

		std::ofstream ofs;
		ofs.open(finalpath + ".ini", std::ios::out);

		if (!ofs.is_open()) {
			std::cout << "Failed to write rect." << std::endl;
			return;
		}

		ofs << 1 << std::endl;
		ofs << std::format("{0:<20s} 0  {1:5d}  {2:3d} {3:3d} {4:3d} {5:3d} {6:2d}", filename, 6554, finalrect.x, finalrect.y, finalrect.width, finalrect.height, g_points.size());

		for (auto& p : g_points) {
			ofs << std::format(" {0:3d} {1:3d}", p.x, p.y);
		}
		ofs << std::endl;

		//ofs << filename << ' ' << 1 << ' ' << 65535 << ' ';
		//ofs << finalrect.x << ' ' << finalrect.y << ' ' << finalrect.width << ' ' << finalrect.height << std::endl;

		ofs.close();

		cv::destroyWindow(ClippedWndName);
		break;
	}
	case cv::EVENT_LBUTTONUP:
	{
		g_points.emplace_back(x, y);
		break;
	}
	}
}

void OnMouseEvent_show(int msg, int x, int y, int flag, void* userdata) {
	static cv::Point p0;
	static bool pressed = false;
	switch (msg) {
	case cv::EVENT_LBUTTONDOWN:
		p0 = { x, y };
		std::cout << "Press at " << x << ' ' << y << std::endl;
		pressed = true;
		break;
	case cv::EVENT_MOUSEMOVE:
		if (pressed) {
			int left = std::min(x, p0.x);
			int right = std::max(x, p0.x);
			int top = std::min(y, p0.y);
			int bottom = std::max(y, p0.y);
			cv::Rect r(cv::Point(left, top), cv::Point(right, bottom));

			original.copyTo(rected);
			cv::rectangle(rected, r, cv::Scalar(0, 0, 255), 2, 8, 0);

			cv::imshow(RectedWndName, rected);
		}
		break;
	case cv::EVENT_LBUTTONUP:
		std::cout << "Released at " << x << ' ' << y << std::endl;
		if (pressed) {
			int left = std::min(x, p0.x);
			int right = std::max(x, p0.x);
			int top = std::min(y, p0.y);
			int bottom = std::max(y, p0.y);

			cv::Rect r(cv::Point(left, top), cv::Point(right, bottom));
			if (r.area() != 0) {
				finalrect = r;

				original.copyTo(rected);
				cv::rectangle(rected, r, cv::Scalar(0, 0, 255), 2, 8, 0);

				cv::imshow(RectedWndName, rected);

				clipped = original(r);

				g_points.clear();
				cv::namedWindow(ClippedWndName);
				cv::setMouseCallback(ClippedWndName, OnMouseEvent_Processed);
				cv::imshow(ClippedWndName, clipped);
			}
		}
		pressed = false;
		break;
	}
	return;
}

void TaskMain(std::vector<std::string>& filenames) {
	if (filenames.size() == 1) {
		filepath = filenames[0];
		cv::Mat m = cv::imread(filenames[0]);

		if (m.channels() == 4)
			cv::cvtColor(m, original, cv::ColorConversionCodes::COLOR_BGRA2BGR, 3);
		else
			m.copyTo(original);

		if (original.size().width != 960 || original.size().height != 540) { // 确保大小满足要求
			cv::resize(
				original, original,
				cv::Size(960, 540),
				0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR
			); // 双线性缩放
		}

		if (original.empty()) {
			std::cout << "Read picture failed : \'" << filenames[0] << "\'." << std::endl;
			return;
		}

		cv::namedWindow(RectedWndName);
		cv::setMouseCallback(RectedWndName, OnMouseEvent_show);
		cv::imshow(RectedWndName, original);
		cv::waitKey();
	}
	return;
}

}

void TaskOver();

void TaskClipPicture(std::vector<std::string>& filenames) {
	try {
		TaskMain(filenames);
	}
	catch (...) {
		;
	}
	TaskOver();
	return;
}
