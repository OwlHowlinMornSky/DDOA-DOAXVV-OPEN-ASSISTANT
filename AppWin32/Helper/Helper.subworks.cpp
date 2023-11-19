#include "Helper.h"

namespace ohms {

bool Helper::subwork_challenge() {
	r_logger->addString(L"任务开始: 挑战赛");
	const bool forNew = task_ChaGame_ForNew; // 保存设置

	cv::Rect rect;
	cv::Point pt;

	size_t i = 0; // 次数

begin_point:
	try {
		++i;
		r_logger->addString(L" ");
		r_logger->addString(std::wstring(L"开始第 ") + std::to_wstring(i) + L" 次比赛");

		// 查找目标。
		if (!step_waitFor(forNew ? mat_ChaGameNew : mat_ChaGameLast, rect_ChaGame, rect, seconds(15.0f)))
			step_subtaskError(forNew ? L"找不到新比赛" : L"找不到上一次比赛");

		// 点击比赛，直到进入编队画面（找到挑战按钮）。
		r_logger->addString(forNew ? L"进入新比赛" : L"进入上一次比赛");
		if (!step_keepClickingUntil({ 900, rect.y }, mat_StartGame, rect_StartGame))
			step_subtaskError(L"无法进入比赛");

		// 查找“挑战”按钮。
		step_waitFor(mat_StartGame, rect_StartGame, rect);
		r_logger->addString(L"开始挑战");
		{
			size_t tc = 0;
			while (!m_askedForStop) {
				// 点击挑战，直到进入加载画面。
				pt = { rect.x + 50, rect.y + 20 };
				if (step_keepClickingUntil(pt, mat_Loading, rect_Loading, seconds(4.0f), seconds(0.5f), 20.0f))
					break;
				if (step_waitFor(mat_LowFP, rect_LowFP, rect, seconds(1.0f)))
					step_subtaskError(L"FP耗尽");
				if (++tc > 10)
					step_subtaskError(L"无法开始挑战");
			}
		}

		// 等待结束。
		r_logger->addString(L"等待结算");
		if (!step_waitFor(mat_Result, rect_Result, rect, seconds(5 * 60.0f), 25.0f))
			step_subtaskError(L"挑战超时");

		// 点击，直到进入加载画面。
		r_logger->addString(L"挑战结束");
		pt = { rect.x + 100, rect.y };
		if (!step_keepClickingUntil(pt, mat_Loading, rect_Loading, seconds(60.0f), seconds(0.2f), 20.0f))
			step_subtaskError(L"无法退出挑战");

		// 等待到挑战赛标签页出现。
		r_logger->addString(L"正在退出比赛");
		if (!step_waitFor(mat_ChaTabBar, rect_ChaTabBar, rect, seconds(60.0f)))
			step_subtaskError(L"无法退出比赛");
		r_logger->addString(L"比赛结束");

		goto begin_point;
	}
	catch (int err) {
		if (err == 0) { // 返回false表示主动停止
			r_logger->addString(L"任务中止: 挑战赛");
			return false;
		}
		else { // 不是0就是真错误
			r_logger->addString(L" ");
			r_logger->addString(L"任务异常: 挑战赛");
			MessageBoxW(NULL, L"任务异常", L"任务出错", MB_ICONERROR);
		}
	}
	catch (...) {
		r_logger->addString(L" ");
		r_logger->addString(L"任务异常: 挑战赛");
		MessageBoxW(NULL, L"任务异常", L"任务出错", MB_ICONERROR);
	}
	r_logger->addString(L"任务结束: 挑战赛");
	return true;
}

}
