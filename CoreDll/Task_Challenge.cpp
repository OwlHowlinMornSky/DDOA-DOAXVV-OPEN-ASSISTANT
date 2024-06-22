/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
*
*     Copyright 2023-2024  Tyler Parret True
*
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
*
* @Authors
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
#include "Task_Challenge.h"
#include "CoreLog.h"
#include "TaskExceptionCode.h"
#include "Task_Navigate.h"

namespace ohms {

Task_Challenge::Task_Challenge() :
	r_helper(nullptr),
	r_handler(nullptr),
	m_set(Settings::Challenge::DEFAULT) {}

Task_Challenge::~Task_Challenge() {}

bool Task_Challenge::Run(Helper& h) {
	r_handler = WndHandler::Instance();
	r_helper = &h;

	bool taskReturnCode = true; // 若返回false表示终止后续任务。
	try {
		CoreLog() << "Task.Challenge: Start." << std::endl;
		h.GuiLogF(ReturnMsgEnum::ChaStart);

		SetHandler();
		LoadTemplates();

		switch (Settings::Challenge::DEFAULT.PlayMatch) {
		case 1:
			target = PlayMatch::New;
			break;
		case 2:
			target = PlayMatch::Activity;
			break;
		default:
			target = PlayMatch::Previous;
			break;
		}

		playCnt = 0; // 次数
		playAwardCnt = 0; // 奖励挑战赛次数

		m_loopSt = LoopStatus::Begin;
		FirstNavigate();
		while (true) {
			switch (m_loopSt) {
			default:
			case LoopStatus::Begin:
				CoreLog() << "Task.Challenge: Loop Begin." << std::endl;
				m_loopSt = LoopStatus::Navigate;
				break;
			case LoopStatus::Navigate:
				InitNavigate();
				break;
			case LoopStatus::Enter:
				EnterConfirmPage();
				m_loopSt = LoopStatus::Start;
				break;
			case LoopStatus::Start:
				StartMatch();
				m_loopSt = LoopStatus::Wait;
				break;
			case LoopStatus::Wait:
				WaitingForEnd();
				m_loopSt = LoopStatus::Check;
				break;
			case LoopStatus::Check:
				// 检查是否有奖励挑战赛。
				if (m_set.CheckAddition)
					CheckForAwrad();
				m_loopSt = LoopStatus::End;
				break;
			case LoopStatus::End:
				CoreLog() << "Task.Challenge: Loop End." << std::endl;
				TaskSleep(1.0_sec);
				m_loopSt = LoopStatus::Begin;
				break;
			}
		/*MatchComfirm:
			StartMatch();
		MatchEnd:
			WaitingForEnd();*/
		}
	}
	catch (int err) {
		switch (err) {
		case TaskExceptionCode::UserStop:
			h.GuiLogF(ReturnMsgEnum::TaskStop);
			taskReturnCode = false;
			break;
		case TaskExceptionCode::TaskComplete:
			h.GuiLogF(ReturnMsgEnum::TaskComplete);
			break;
		case TaskExceptionCode::KnownErrorButNotCritical:
			break;
		case TaskExceptionCode::KnownErrorCritical:
			taskReturnCode = false;
			break;
		default:
			h.GuiLogF(ReturnMsgEnum::TaskException);
			taskReturnCode = false;
		}
	}
	catch (...) {
		h.GuiLogF(ReturnMsgEnum::TaskException);
		taskReturnCode = false;
	}
	CoreLog() << "Task.Challenge: Exit." << std::endl;
	h.GuiLogF(ReturnMsgEnum::ChaExit);
	return taskReturnCode;
}

bool Task_Challenge::SetHandler() const {
	switch (r_handler->SetForGame()) {
	case WndHandler::SetReturnValue::WndNotFound:
		CoreLog() << "Task.Challenge: Game Window Not Found." << std::endl;
		r_helper->TaskError(ReturnMsgEnum::TaskErrNoWnd);
		break;
	case WndHandler::SetReturnValue::CaptureFailed:
		CoreLog() << "Task.Challenge: Game Window Cannot Capture." << std::endl;
		r_helper->TaskError(ReturnMsgEnum::TaskErrNoCap);
		break;
	}
	CoreLog() << "Task.Challenge: Window Handler Setted." << std::endl;
	return false;
}

bool Task_Challenge::LoadTemplates() {
	CoreLog() << "Task.Challenge: Begin Load Templates." << std::endl;
	temp_chaBar = r_helper->CreateTemplate("default");
	temp_lastFight = r_helper->CreateTemplate("lastFight");
	temp_newFight = r_helper->CreateTemplate("newFight");
	temp_startGame = r_helper->CreateTemplate("start");
	temp_loading = r_helper->CreateTemplate("loading");
	temp_lowFp = r_helper->CreateTemplate("fp");
	temp_gameResult = r_helper->CreateTemplate("result");
	temp_awardCha = r_helper->CreateTemplate("add");
	m_camFp = r_helper->CreateTemplate("UseFp");
	m_camFpNo = r_helper->CreateTemplate("cha/shotFpNo");
	m_camFpComf[0] = r_helper->CreateTemplate("UseFpComf0");
	m_camFpComf[1] = r_helper->CreateTemplate("UseFpComf1");
	m_camFpDrink = r_helper->CreateTemplate("cha/drink");
	m_camFpDrinkComf = r_helper->CreateTemplate("cha/drinkComf");

	m_act100pre[0] = r_helper->CreateTemplate("cha/act/l0");
	m_act100pre[1] = r_helper->CreateTemplate("cha/act/l1");
	m_act100pre[2] = r_helper->CreateTemplate("cha/act/l2");
	m_act100pre[3] = r_helper->CreateTemplate("cha/act/l3");
	m_act100pre[4] = r_helper->CreateTemplate("cha/act/l4");

	m_actSlevel[0] = r_helper->CreateTemplate("cha/act/r0");
	m_actSlevel[1] = r_helper->CreateTemplate("cha/act/r1");
	m_actSlevel[2] = r_helper->CreateTemplate("cha/act/r2");
	m_actSlevel[3] = r_helper->CreateTemplate("cha/act/r3");
	m_actSlevel[4] = r_helper->CreateTemplate("cha/act/r4");


	CoreLog() << "Task.Challenge: Finish Load Templates." << std::endl;
	return false;
}

void Task_Challenge::FirstNavigate() {
	bool res = Task_Navigate::Instance()->NavigateTo(NavigateEnum::Challenge);
	bool needManual = false;
	switch (Settings::Challenge::DEFAULT.PlayMatch) {
	case 1: // 新比赛
		//if (-1 == r_handler->WaitFor(*temp_newFight, milliseconds(1000)))
		//	needManual = true;
		break;
	case 2: // 活动关卡
	{
		if (!res) {
			needManual = true;
			break;
		}
		if (-1 == r_handler->WaitFor(*temp_chaBar, milliseconds(1000))) {
			needManual = true;
			break;
		}
		// 到“活动页”
		r_handler->ClickAt(temp_chaBar->GetSpecialPointInResult(3));

		TaskSleep(seconds(1.0f));

		// 滚动到最底部
		r_handler->MoveMouseTo({ 920, 530 });
		TaskSleep(seconds(0.5f));
		r_handler->WheelDown(20);

		TaskSleep(seconds(1.0f));

		cv::Mat mat;
		bool got;
		int up, rank;
		// 寻找目标等级
		got = r_handler->GetOneFrame(mat);
		if (!got) {
			needManual = true;
			break;
		}
		up = -1;
		rank = -1;
		for (int i = 4; i >= 0; --i) {
			if (m_act100pre[i]->Match(mat)) {
				int abspos = i - Settings::Challenge::DEFAULT.SelectedActivityLevel + 1;
				if (abspos < 0) {
					up = -abspos;
					rank = 0;
				}
				else {
					up = 0;
					rank = abspos;
				}
				break;
			}
		}
		if (up < 0 || rank < 0 || rank > 4) {
			needManual = true;
			break;
		}
		if (up > 0) {
			r_handler->WheelUp(up);
		}
		TaskSleep(seconds(0.5f));
		r_handler->ClickAt(m_act100pre[rank]->GetSpecialPointInSearch(0));

		TaskSleep(seconds(1.0f));
		// 已经进入目标等级

		// 滚动到最底部
		r_handler->MoveMouseTo({ 920, 530 });
		TaskSleep(seconds(0.5f));
		r_handler->WheelDown(20);

		TaskSleep(seconds(0.5f));

		// 寻找目标关卡
		got = r_handler->GetOneFrame(mat);
		if (!got) {
			needManual = true;
			break;
		}
		up = -1;
		rank = -1;
		for (int i = 4; i >= 0; --i) {
			if (m_actSlevel[i]->Match(mat)) {
				int abspos = i - Settings::Challenge::DEFAULT.SelectedActivityMatch + 1;
				if (abspos < 0) {
					up = -abspos;
					rank = 0;
				}
				else {
					up = 0;
					rank = abspos;
				}
				break;
			}
		}
		if (up < 0 || rank < 0 || rank > 4) {
			needManual = true;
			break;
		}
		if (up > 0) {
			r_handler->WheelUp(up);
		}
		TaskSleep(seconds(0.5f));
		r_handler->ClickAt(m_actSlevel[rank]->GetSpecialPointInSearch(0));
		TaskSleep(seconds(1.0f));
		break;
	}
	default: // 当前/上次
		switch (Task_Navigate::Instance()->TryToDeterminePage()) {
		case NavigateEnum::MatchConfirm:
		case NavigateEnum::MatchResult:
			break;
		default:
			if (-1 == r_handler->WaitFor(*temp_lastFight, milliseconds(1000)))
				needManual = true;
			break;
		}
		break;
	}
	if (needManual) {
		if (Settings::Challenge::DEFAULT.AskForManual) {
			r_handler->Reset();
			r_helper->TaskWaitForResume(ReturnMsgEnum::ManualNavigateToChallengePage);
			r_handler->SetForGame();
		}
		else {
			CoreLog() << "Task.Challenge: First Navigate Failed." << std::endl;
			throw TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
		}
	}
	m_loopSt = LoopStatus::Begin;
}

bool Task_Challenge::InitNavigate() {
	// 检查导航位置
	switch (Task_Navigate::Instance()->TryToDeterminePage()) {
	case NavigateEnum::Challenge:
		CoreLog() << "Task.Challenge: Navigate Detected: Challenge." << std::endl;
		TaskSleep(2.0_sec);
		if (-1 == r_handler->WaitFor(*temp_chaBar)) {
			CoreLog() << "Task.Challenge: Navigate Failed: No ChaBar." << std::endl;
			throw TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
		}
		r_handler->ClickAt(temp_chaBar->GetSpecialPointInResult(0));
		TaskSleep(500_msec);
		break;
	case NavigateEnum::MatchConfirm:
		CoreLog() << "Task.Challenge: Navigate Detected: Match Confirm." << std::endl;
		//goto MatchComfirm;
		m_loopSt = LoopStatus::Start;
		return false;
	case NavigateEnum::MatchResult:
		CoreLog() << "Task.Challenge: Navigate Detected: Match Result." << std::endl;
		//goto MatchEnd;
		m_loopSt = LoopStatus::Wait;
		return false;
	default:
		CoreLog() << "Task.Challenge: Navigate Detected: Others." << std::endl;
		if (!Task_Navigate::Instance()->NavigateTo(NavigateEnum::Challenge)) {
			CoreLog() << "Task.Challenge: Navigate Failed." << std::endl;
			throw TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
		}
		TaskSleep(2.0_sec);
		if (-1 == r_handler->WaitFor(*temp_chaBar)) {
			CoreLog() << "Task.Challenge: Navigate Failed: No ChaBar." << std::endl;
			throw TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
		}
		r_handler->ClickAt(temp_chaBar->GetSpecialPointInResult(0));
		TaskSleep(500_msec);
		break;
	}
	CoreLog() << "Task.Challenge: Navigate Over." << std::endl;
	m_loopSt = LoopStatus::Enter;
	return false;
}

void Task_Challenge::EnterConfirmPage() {
	cv::Point pt;
	CoreLog() << "Task.Challenge: Search for Target Match Enter Button." << std::endl;
	// 查找目标比赛按钮。
	switch (target) {
	case PlayMatch::Previous:
		if (-1 == r_handler->WaitFor(*temp_lastFight))
			r_helper->TaskError(ReturnMsgEnum::TaskErrChaNoPri);
		CoreLog() << "Task.Challenge: Enter Game <Previous>." << std::endl;
		pt = { 900, temp_lastFight->GetLastMatchRect().y };
		break;
	case PlayMatch::New:
		if (-1 == r_handler->WaitFor(*temp_newFight))
			r_helper->TaskError(ReturnMsgEnum::TaskErrChaNoNew);
		CoreLog() << "Task.Challenge: Enter Game <New>." << std::endl;
		pt = { 900, temp_newFight->GetLastMatchRect().y };
		break;
	case PlayMatch::Activity:
		if (-1 == r_handler->WaitFor(*temp_lastFight))
			r_helper->TaskError(ReturnMsgEnum::TaskErrChaNoPri);
		CoreLog() << "Task.Challenge: Enter Game <Previous>." << std::endl;
		pt = { 900, temp_lastFight->GetLastMatchRect().y };
		break;
	case PlayMatch::Award:
		if (-1 == r_handler->WaitFor(*temp_newFight))
			r_helper->TaskError(ReturnMsgEnum::TaskErrChaNoNew);
		CoreLog() << "Task.Challenge: Enter Game <Award>." << std::endl;
		pt = { 900, temp_newFight->GetLastMatchRect().y };
		break;
	}

	// 点击比赛，直到进入编队画面（找到挑战按钮）。
	if (!r_handler->KeepClickingUntil(pt, *temp_startGame))
		r_helper->TaskError(ReturnMsgEnum::TaskErrChaNoEnter);
}

void Task_Challenge::StartMatch() {
	cv::Point pt;
	CoreLog() << "Task.Challenge: Search for Match Start Button." << std::endl;
	// 查找“挑战”按钮。
	bool triedFp = false;
	r_handler->WaitFor(*temp_startGame);
	CoreLog() << "Task.Challenge: Play Game." << std::endl;
	for (int i = 0, n = 10; i < n; ++i) {
		CoreLog() << "Task.Challenge: Start Match Loop: " << i << "." << std::endl;
		pt = temp_startGame->GetSpecialPointInResult(0);
		r_handler->ClickAt(pt);
		switch (r_handler->WaitForMultiple({ temp_loading.get(), temp_lowFp.get() }, 2.0_sec)) {
		default:
		case -1:
			CoreLog() << "Task.Challenge: Start Match Loop: Not Found." << std::endl;
			if (i == n - 1) {
				CoreLog() << "Task.Challenge: Failed to Start Match." << std::endl;
				r_helper->TaskError(ReturnMsgEnum::TaskErrChaNoStart);
			}
			break;
		case 0:
			i = n;
			CoreLog() << "Task.Challenge: Start Match Loop: OK." << std::endl;
			break;
		case 1:
			if (triedFp) {
				CoreLog() << "Task.Challenge: Task Over: Fp Handle Failed." << std::endl;
				throw TaskExceptionCode::TaskComplete;
			}
			CoreLog() << "Task.Challenge: Start Match Loop: Low FP." << std::endl;
			HandleLowFp();
			triedFp = true;
			break;
		}
	}
	CoreLog() << "Task.Challenge: Match Started." << std::endl;
}

bool Task_Challenge::HandleLowFp() {
	cv::Point pt;
	if (!m_set.AutoUseCamFP && !m_set.AutoUseDrink) { // 使用cam补充fp
		CoreLog() << "Task.Challenge: Task Over: Setted No Use FP." << std::endl;
		throw TaskExceptionCode::TaskComplete;
	}
	switch (r_handler->WaitForMultiple({ m_camFp.get(), m_camFpNo.get() }, 2.0_sec)) {
	case 0:
		CoreLog() << "Task.Challenge: Try to Use FP: Available." << std::endl;
		pt = m_camFp->GetSpecialPointInResult(0);

		r_handler->ClickAt(pt);
		TaskSleep(1.0_sec);

		if (-1 == r_handler->WaitFor(*(m_camFpComf[0]))) {
			CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No 1st." << std::endl;
			throw TaskExceptionCode::TaskComplete;
		}
		pt = m_camFpComf[0]->GetSpecialPointInResult(0);
		if (!r_handler->KeepClickingUntil(pt, *(m_camFpComf[1]), 10.0_sec, 2.0_sec)) {
			CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No 2st." << std::endl;
			throw TaskExceptionCode::TaskComplete;
		}
		pt = m_camFpComf[1]->GetSpecialPointInResult(0);

		r_handler->ClickAt(pt);
		TaskSleep(1.0_sec);
		if (-1 == r_handler->WaitFor(*temp_startGame)) {
			CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No Close." << std::endl;
			throw TaskExceptionCode::TaskComplete;
		}
		CoreLog() << "Task.Challenge: Try to Use FP: OK." << std::endl;
		break;
	default:
		CoreLog() << "Task.Challenge: No FP." << std::endl;
		if (!m_set.AutoUseDrink || r_handler->WaitFor(*m_camFpDrink, 2.0_sec) == -1) {
			CoreLog() << "Task.Challenge: Task Over: No Use Drink." << std::endl;
			throw TaskExceptionCode::TaskComplete;
		}
		r_handler->ClickAt(m_camFpDrink->GetSpecialPointInResult(0));
		TaskSleep(500_msec);
		r_handler->ClickAt(m_camFpDrink->GetSpecialPointInResult(1));
		TaskSleep(500_msec);
		if (r_handler->WaitFor(*m_camFpDrinkComf, 2.0_sec) == -1) {
			CoreLog() << "Task.Challenge: Task Over: Drink No Ok." << std::endl;
			throw TaskExceptionCode::TaskComplete;
		}
		if (!r_handler->KeepClickingUntil(m_camFpDrinkComf->GetSpecialPointInResult(0), *temp_startGame)) {
			CoreLog() << "Task.Challenge: Task Over: Try to Use Drink: No Close." << std::endl;
			throw TaskExceptionCode::TaskComplete;
		}
		CoreLog() << "Task.Challenge: Try to Use Drink: OK." << std::endl;
		break;
	}
	return false;
}

void Task_Challenge::WaitingForEnd() {
	cv::Point pt;

	if (target == PlayMatch::Award) {
		++playAwardCnt;
		r_helper->GuiLogF_I(ReturnMsgEnum::ChaBeginAdd_I, playAwardCnt);
		CoreLog() << "Task.Challenge: Match Award " << playAwardCnt << "." << std::endl;
	}
	else {
		++playCnt;
		r_helper->GuiLogF_I(ReturnMsgEnum::ChaBegin_I, playCnt);
		CoreLog() << "Task.Challenge: Match " << playCnt << "." << std::endl;
	}

	// 等待结束。
	CoreLog() << "Task.Challenge: In Game, Waitting for End." << std::endl;
	if (-1 == r_handler->WaitFor(*temp_gameResult, 300.0_sec))
		r_helper->TaskError(ReturnMsgEnum::TaskErrChaTimeOut);

	// 点击，直到进入加载画面。
	CoreLog() << "Task.Challenge: Game End, Trying to Exit." << std::endl;
	pt = temp_gameResult->GetSpecialPointInResult(0);
	if (!r_handler->KeepClickingUntil(pt, *temp_loading, 60.0_sec, 0.1_sec))
		r_helper->TaskError(ReturnMsgEnum::TaskErrChaNoEnd);

	// 等待到挑战赛标签页出现。
	CoreLog() << "Task.Challenge: Game Exit, Waitting for Challenge Page." << std::endl;
	if (-1 == r_handler->WaitFor(*temp_chaBar, 60.0_sec))
		r_helper->TaskError(ReturnMsgEnum::TaskErrChaNoOver);
	r_helper->GuiLogF(ReturnMsgEnum::ChaOver);
}

void Task_Challenge::CheckForAwrad() {
	cv::Point pt;
	if (0 == r_handler->WaitFor(*temp_awardCha, 2.0_sec)) {
		CoreLog() << "Task.Challenge: Find Award." << std::endl;
		r_helper->GuiLogF(ReturnMsgEnum::ChaFindAdd);
		if (m_set.EnterAddition) { // 进入奖励挑战赛。
			if (target == PlayMatch::New) {
				pt = temp_awardCha->GetSpecialPointInResult(0);
				if (r_handler->KeepClickingUntil(pt, *temp_newFight, 10.0_sec, 2.0_sec)) {
					r_helper->GuiLogF(ReturnMsgEnum::ChaOpenedAdd);
					target = PlayMatch::Award;
					playAwardCnt = 0;
				}
				else {
					r_helper->TaskError(ReturnMsgEnum::TaskErrChaOpenAddFailed);
				}
			}
			else {
				r_helper->TaskError(ReturnMsgEnum::TaskErrChaAddNotSup);
			}
		}
		else { // 回到“推荐”栏。
			if (0 == r_handler->WaitFor(*temp_chaBar, 5.0_sec)) {
				pt = temp_chaBar->GetSpecialPointInResult(0);
				if (r_handler->KeepClickingUntilNo(pt, *temp_awardCha, 10.0_sec, 0.5_sec)) {
					r_helper->GuiLogF(ReturnMsgEnum::ChaIgnoredAdd);
				}
				else {
					r_helper->TaskError(ReturnMsgEnum::TaskErrChaIgnoreAddFailed);
				}
			}
		}
	}
	else {
		CoreLog() << "Task.Challenge: Not Find Award." << std::endl;
		r_helper->GuiLogF(ReturnMsgEnum::ChaNotFindAdd);
	}
}

}
