#include "Helper.h"

namespace ohms {

void Helper::subwork_fight() {
	r_logger->addString(L"开始任务: 挑战赛");
	const bool forNew = m_task_forNew;

	cv::Rect rect;
	cv::Point pt;

	size_t i = 0;

begin_point:
	try {
		++i;
		r_logger->addString(L" ");
		r_logger->addString(std::wstring(L"开始第 ") + std::to_wstring(i) + L" 次比赛");

		// 查找目标。
		r_logger->addString(forNew ? L"开始查找 新比赛" : L"开始查找 上一次比赛");
		rect = m_rect_fight;
		if (!step_waitFor(true, forNew ? m_newFight : m_lastFight, rect, seconds(15.0f)))
			subtask_error(forNew ? L"找不到 新比赛" : L"找不到 上一次比赛");
		r_logger->addString(forNew ? L"找到 新比赛" : L"找到 上一次比赛");

		// 点击比赛，直到进入编队画面（找到挑战按钮）。
		r_logger->addString(L"尝试进入 编队页面");
		if (!keepClickingUntil({ 900, rect.y }, m_rect_start, m_start, 10))
			subtask_error(L"无法进入 编队页面");
		r_logger->addString(L"已进入 编队页面");

		// 查找“挑战”按钮。
		rect = m_rect_start;
		step_waitFor(true, m_start, rect);
		r_logger->addString(L"点击 挑战 按钮");
		{
			size_t tc = 0;
			while (!m_askedForStop) {
				// 点击挑战，直到进入加载画面。
				pt = { rect.x + 50, rect.y + 20 };
				if (keepClickingUntil(pt, m_rect_loading, m_loading, 4, seconds(0.5f), 20))
					break;
				cv::Rect fp_rect = m_rect_fp;
				if (step_waitFor(true, m_fp, fp_rect, milliseconds(1000)))
					subtask_error(L"FP耗尽");
				if (++tc > 10)
					subtask_error(L"进入挑战超时");
			}
		}
		r_logger->addString(L"已进入 加载页面");

		// 等待结束。
		r_logger->addString(L"等待结算");
		rect = m_rect_result;
		if (!step_waitFor(true, m_result, rect, seconds(5 * 60.0f), 25))
			subtask_error(L"挑战超时");
		r_logger->addString(L"已进入 结算页面");

		// 点击，直到进入加载画面。
		r_logger->addString(L"正在退出 结算");
		pt = { rect.x + 100, rect.y };
		if (!keepClickingUntil(pt, m_rect_loading, m_loading, 60, seconds(0.1f), 20))
			subtask_error(L"退出结算超时");
		r_logger->addString(L"已退出 结算");

		// 等待到挑战赛标签页出现。
		r_logger->addString(L"正在退出 挑战");
		rect = m_rect_default; // 640 -> 960, 80 -> 270
		if (!step_waitFor(true, m_default, rect, seconds(60.0f)))
			subtask_error(L"退出挑战超时");
		r_logger->addString(L"已退出 挑战");

		goto begin_point;
	}
	catch (int err) {
		if (err == 0)
			r_logger->addString(L"停止任务: 挑战赛");
		else {
			r_logger->addString(L" ");
			r_logger->addString(L"任务异常: 挑战赛");
			MessageBoxW(NULL, L"任务异常", L"DOAXVV-helper: Task Error", MB_ICONERROR);
		}
	}
	catch (...) {
		r_logger->addString(L" ");
		r_logger->addString(L"任务异常: 挑战赛");
		MessageBoxW(NULL, L"任务异常", L"DOAXVV-helper: Task Error", MB_ICONERROR);
	}
	r_logger->addString(L"结束任务: 挑战赛");
	return;
}

}
