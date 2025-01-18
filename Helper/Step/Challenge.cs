using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Helper.Settings;
using System.Drawing;

namespace Helper.Step {
	internal class Challenge : IStep {

		private readonly Settings.Challenge m_set; // 设置数据的副本
		private CancellationToken m_ct;

		private readonly Pattern temp_chaBar;
		private readonly Pattern temp_lastFight;
		private readonly Pattern temp_newFight;
		private readonly Pattern temp_startGame;
		private readonly Pattern temp_loading;
		private readonly Pattern temp_lowFp;
		private readonly Pattern temp_gameResult;
		private readonly Pattern temp_awardCha;
		private readonly Pattern m_camFp;
		private readonly Pattern m_camFpDrink;
		private readonly Pattern m_camFpDrinkComf;
		private readonly Pattern m_camFpNo;
		private readonly Pattern[] m_camFpComf; // 2
		private readonly Pattern[] m_act100pre; // 5
		private readonly Pattern[] m_actSlevel; // 5

		enum PlayMatch {
			Previous = 0,
			New,
			Activity,
			Award
		}
		PlayMatch target;

		int playCnt;
		int playAwardCnt;

		enum LoopStatus {
			Begin = 0,
			Navigate,
			Enter,
			Start,
			Wait,
			Check,
			End
		}
		LoopStatus m_loopSt;

		internal Challenge() {
			//CoreLog() << "Task.Challenge: Begin Load Templates." << std::endl;
			m_set = Settings.challenge;

			temp_chaBar = Global.PatternManager.CreatePattern("default") ?? throw new Exception();
			temp_lastFight = Global.PatternManager.CreatePattern("lastFight") ?? throw new Exception();
			temp_newFight = Global.PatternManager.CreatePattern("newFight") ?? throw new Exception();
			temp_startGame = Global.PatternManager.CreatePattern("start") ?? throw new Exception();
			temp_loading = Global.PatternManager.CreatePattern("loading") ?? throw new Exception();
			temp_lowFp = Global.PatternManager.CreatePattern("fp") ?? throw new Exception();
			temp_gameResult = Global.PatternManager.CreatePattern("result") ?? throw new Exception();
			temp_awardCha = Global.PatternManager.CreatePattern("add") ?? throw new Exception();
			m_camFp = Global.PatternManager.CreatePattern("UseFp") ?? throw new Exception();
			m_camFpNo = Global.PatternManager.CreatePattern("cha/shotFpNo") ?? throw new Exception();

			m_camFpComf = [
				Global.PatternManager.CreatePattern("UseFpComf0") ?? throw new Exception(),
				Global.PatternManager.CreatePattern("UseFpComf1") ?? throw new Exception(),
			];

			m_camFpDrink = Global.PatternManager.CreatePattern("cha/drink") ?? throw new Exception();
			m_camFpDrinkComf = Global.PatternManager.CreatePattern("cha/drinkComf") ?? throw new Exception();

			m_act100pre = [
				Global.PatternManager.CreatePattern("cha/act/l0") ?? throw new Exception(),
				Global.PatternManager.CreatePattern("cha/act/l1") ?? throw new Exception(),
				Global.PatternManager.CreatePattern("cha/act/l2") ?? throw new Exception(),
				Global.PatternManager.CreatePattern("cha/act/l3") ?? throw new Exception(),
				Global.PatternManager.CreatePattern("cha/act/l4") ?? throw new Exception(),
			];

			m_actSlevel = [
				Global.PatternManager.CreatePattern("cha/act/r0") ?? throw new Exception(),
				Global.PatternManager.CreatePattern("cha/act/r1") ?? throw new Exception(),
				Global.PatternManager.CreatePattern("cha/act/r2") ?? throw new Exception(),
				Global.PatternManager.CreatePattern("cha/act/r3") ?? throw new Exception(),
				Global.PatternManager.CreatePattern("cha/act/r4") ?? throw new Exception(),
			];

			//CoreLog() << "Task.Challenge: Finish Load Templates." << std::endl;
			return;
		}

		public void Run(CancellationToken ct) {
			m_ct = ct;
			try {
				//CoreLog() << "Task.Challenge: Start." << std::endl;
				//h.GuiLogF(ReturnMsgEnum::ChaStart);

				SetHandler();

				target = Settings.challenge.PlayMatch switch {
					1 => PlayMatch.New,
					2 => PlayMatch.Activity,
					_ => PlayMatch.Previous,
				};
				playCnt = 0; // 次数
				playAwardCnt = 0; // 奖励挑战赛次数

				m_loopSt = LoopStatus.Begin;
				FirstNavigate();
				while (true) {
					switch (m_loopSt) {
					default:
					case LoopStatus.Begin:
						//CoreLog() << "Task.Challenge: Loop Begin." << std::endl;
						m_loopSt = LoopStatus.Navigate;
						break;
					case LoopStatus.Navigate:
						InitNavigate();
						break;
					case LoopStatus.Enter:
						EnterConfirmPage();
						m_loopSt = LoopStatus.Start;
						break;
					case LoopStatus.Start:
						StartMatch();
						m_loopSt = LoopStatus.Wait;
						break;
					case LoopStatus.Wait:
						WaitingForEnd();
						m_loopSt = LoopStatus.Check;
						break;
					case LoopStatus.Check:
						// 检查是否有奖励挑战赛。
						if (m_set.CheckAddition)
							CheckForAwrad();
						m_loopSt = LoopStatus.End;
						break;
					case LoopStatus.End:
						//CoreLog() << "Task.Challenge: Loop End." << std::endl;
						IStep.TaskSleep(TimeSpan.FromSeconds(1), ct);
						m_loopSt = LoopStatus.Begin;
						break;
					}
					/*MatchComfirm:
						StartMatch();
					MatchEnd:
						WaitingForEnd();*/
				}
			}
			catch (StepCompleteException) {
				throw;
				//h.GuiLogF(ReturnMsgEnum::TaskComplete);
			}
			catch {
				throw;
			}
			//CoreLog() << "Task.Challenge: Exit." << std::endl;
			//h.GuiLogF(ReturnMsgEnum::ChaExit);
			return;
		}

		private void SetHandler() {
			if (!Global.WndHandler.SetForGame()) {
				/*case WndHandler::SetReturnValue::WndNotFound:
					CoreLog() << "Task.Challenge: Game Window Not Found." << std::endl;
					r_helper->TaskError(ReturnMsgEnum::TaskErrNoWnd);
					break;
				case WndHandler::SetReturnValue::CaptureFailed:
					CoreLog() << "Task.Challenge: Game Window Cannot Capture." << std::endl;
					r_helper->TaskError(ReturnMsgEnum::TaskErrNoCap);
					break;*/
				;
				throw new Exception();
			}
			//CoreLog() << "Task.Challenge: Window Handler Setted." << std::endl;
			return;
		}

		private void FirstNavigate() {
			bool res = Navigate.NavigateTo(Navigate.Page.Challenge);
			bool needManual = false;
			switch (Settings.challenge.PlayMatch) {
			case 1: // 新比赛
					//if (-1 == Global.WndHandler.WaitFor(*temp_newFight, milliseconds(1000)))
					//	needManual = true;
				break;
			case 2: // 活动关卡
			{
				if (m_act100pre is null || m_actSlevel is null)
					throw new Exception();

				if (!res) {
					needManual = true;
					break;
				}
				if (!Global.WndHandler.WaitFor(temp_chaBar ?? throw new Exception(), TimeSpan.FromSeconds(1))) {
					needManual = true;
					break;
				}
				// 到“活动页”
				Global.WndHandler.ClickAt(temp_chaBar.GetSpecialPointInResultRect(3));

				IStep.TaskSleep(TimeSpan.FromSeconds(1), m_ct);

				// 滚动到最底部
				Global.WndHandler.Hand.MoveCursorTo(new Point(920, 530));
				IStep.TaskSleep(TimeSpan.FromSeconds(0.5), m_ct);
				Global.WndHandler.Hand.MoveMouseWheel(true, 12u);

				IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);

				bool got;
				int up, rank;
				// 寻找目标等级
				got = Global.WndHandler.WaitOneFrame();
				HelperKernel.IEye mat = Global.WndHandler.Eye;
				if (!got) {
					needManual = true;
					break;
				}
				up = -1;
				rank = -1;
				for (int i = 4; i >= 0; --i) {
					if (m_act100pre[i].TryMatch(mat)) {
						int abspos = i - Settings.challenge.SelectedActivityLevel + 1;
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
					Global.WndHandler.Hand.MoveMouseWheel(false, (uint)up);
				}
				IStep.TaskSleep(TimeSpan.FromSeconds(0.5), m_ct);
				Global.WndHandler.ClickAt(m_act100pre[rank].GetSpecialPointInSearchRect(0));

				IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);
				// 已经进入目标等级

				// 滚动到最底部
				Global.WndHandler.Hand.MoveCursorTo(new Point(920, 530));
				IStep.TaskSleep(TimeSpan.FromSeconds(0.5), m_ct);
				Global.WndHandler.Hand.MoveMouseWheel(true, 12u);

				IStep.TaskSleep(TimeSpan.FromSeconds(0.5), m_ct);

				// 寻找目标关卡
				got = Global.WndHandler.WaitOneFrame();
				if (!got) {
					needManual = true;
					break;
				}
				mat = Global.WndHandler.Eye;
				up = -1;
				rank = -1;
				for (int i = 4; i >= 0; --i) {
					if (m_actSlevel[i].TryMatch(mat)) {
						int abspos = i - Settings.challenge.SelectedActivityMatch + 1;
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
					Global.WndHandler.Hand.MoveMouseWheel(false, (uint)up);
				}
				IStep.TaskSleep(TimeSpan.FromSeconds(0.5), m_ct);
				Global.WndHandler.ClickAt(m_actSlevel[rank].GetSpecialPointInSearchRect(0));
				IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);
				break;
			}
			default: // 当前/上次
				switch (Navigate.TryToDeterminePage()) {
				case Navigate.Page.MatchConfirm:
				case Navigate.Page.MatchResult:
					break;
				default:
					if (!Global.WndHandler.WaitFor(temp_lastFight, TimeSpan.FromSeconds(1)))
						needManual = true;
					break;
				}
				break;
			}
			if (needManual) {
				if (Settings.challenge.AskForManual) {
					Global.WndHandler.Reset();
					//

					throw new Exception();
					
					//Global.Worker.TaskWaitForResume(ReturnMsgEnum::ManualNavigateToChallengePage);
					Global.WndHandler.SetForGame();
				}
				else {
					//CoreLog() << "Task.Challenge: First Navigate Failed." << std::endl;
					
					throw new OperationCanceledException(m_ct);
				}
			}
			m_loopSt = LoopStatus.Begin;
		}

		private void InitNavigate() {
			// 检查导航位置
			switch (Navigate.TryToDeterminePage()) {
			case Navigate.Page.Challenge:
				//CoreLog() << "Task.Challenge: Navigate Detected: Challenge." << std::endl;
				IStep.TaskSleep(TimeSpan.FromSeconds(2.0), m_ct);
				if (!Global.WndHandler.WaitFor(temp_chaBar)) {
					//CoreLog() << "Task.Challenge: Navigate Failed: No ChaBar." << std::endl;
					throw new Exception();// TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
				}
				Global.WndHandler.ClickAt(temp_chaBar.GetSpecialPointInResultRect(0));
				IStep.TaskSleep(TimeSpan.FromMilliseconds(500), m_ct);
				break;
			case Navigate.Page.MatchConfirm:
				//CoreLog() << "Task.Challenge: Navigate Detected: Match Confirm." << std::endl;
				//goto MatchComfirm;
				m_loopSt = LoopStatus.Start;
				return;
			case Navigate.Page.MatchResult:
				//CoreLog() << "Task.Challenge: Navigate Detected: Match Result." << std::endl;
				//goto MatchEnd;
				m_loopSt = LoopStatus.Wait;
				return;
			default:
				//CoreLog() << "Task.Challenge: Navigate Detected: Others." << std::endl;
				if (!Navigate.NavigateTo(Navigate.Page.Challenge)) {
					//CoreLog() << "Task.Challenge: Navigate Failed." << std::endl;
					throw new Exception();// TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
				}
				IStep.TaskSleep(TimeSpan.FromSeconds(2.0), m_ct);
				if (!Global.WndHandler.WaitFor(temp_chaBar)) {
					//CoreLog() << "Task.Challenge: Navigate Failed: No ChaBar." << std::endl;
					throw new Exception();// TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
				}
				Global.WndHandler.ClickAt(temp_chaBar.GetSpecialPointInResultRect(0));
				IStep.TaskSleep(TimeSpan.FromMilliseconds(500), m_ct);
				break;
			}
			//CoreLog() << "Task.Challenge: Navigate Over." << std::endl;
			m_loopSt = LoopStatus.Enter;
			return;
		}

		private void EnterConfirmPage() {
			Point pt;
			//CoreLog() << "Task.Challenge: Search for Target Match Enter Button." << std::endl;
			// 查找目标比赛按钮。
			switch (target) {
			case PlayMatch.Previous:
				if (!Global.WndHandler.WaitFor(temp_lastFight))
					throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaNoPri);
										  //CoreLog() << "Task.Challenge: Enter Game <Previous>." << std::endl;
				pt = new(900, temp_lastFight.GetPreviousMatchedRect().Y);
				break;
			case PlayMatch.New:
				if (!Global.WndHandler.WaitFor(temp_newFight))
					throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaNoNew);
										  //CoreLog() << "Task.Challenge: Enter Game <New>." << std::endl;
				pt = new(900, temp_newFight.GetPreviousMatchedRect().Y);
				break;
			case PlayMatch.Activity:
				if (!Global.WndHandler.WaitFor(temp_lastFight))
					throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaNoPri);
										  //CoreLog() << "Task.Challenge: Enter Game <Previous>." << std::endl;
				pt = new(900, temp_lastFight.GetPreviousMatchedRect().Y);
				break;
			case PlayMatch.Award:
				if (!Global.WndHandler.WaitFor(temp_newFight))
					throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaNoNew);
										  //CoreLog() << "Task.Challenge: Enter Game <Award>." << std::endl;
				pt = new(900, temp_newFight.GetPreviousMatchedRect().Y);
				break;
			default:
				goto case PlayMatch.Previous;
			}

			// 点击比赛，直到进入编队画面（找到挑战按钮）。
			if (!Global.WndHandler.KeepClickingUntil(pt, temp_startGame))
				throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaNoEnter);
		}

		private void StartMatch() {
			Point pt;
			//CoreLog() << "Task.Challenge: Search for Match Start Button." << std::endl;
			// 查找“挑战”按钮。
			bool triedFp = false;
			Global.WndHandler.WaitFor(temp_startGame);
			//CoreLog() << "Task.Challenge: Play Game." << std::endl;
			for (int i = 0, n = 10; i < n; ++i) {
				//CoreLog() << "Task.Challenge: Start Match Loop: " << i << "." << std::endl;
				pt = temp_startGame.GetSpecialPointInResultRect(0);
				Global.WndHandler.ClickAt(pt);
				switch (Global.WndHandler.WaitForMultiple([temp_loading, temp_lowFp], TimeSpan.FromSeconds(2.0))) {
				default:
				case -1:
					//CoreLog() << "Task.Challenge: Start Match Loop: Not Found." << std::endl;
					if (i == n - 1) {
						//CoreLog() << "Task.Challenge: Failed to Start Match." << std::endl;
						throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaNoStart);
					}
					break;
				case 0:
					i = n;
					//CoreLog() << "Task.Challenge: Start Match Loop: OK." << std::endl;
					break;
				case 1:
					if (triedFp) {
						//CoreLog() << "Task.Challenge: Task Over: Fp Handle Failed." << std::endl;
						throw new StepCompleteException();
					}
					//CoreLog() << "Task.Challenge: Start Match Loop: Low FP." << std::endl;
					HandleLowFp();
					triedFp = true;
					break;
				}
			}
			//CoreLog() << "Task.Challenge: Match Started." << std::endl;
		}

		private void HandleLowFp() {
			Point pt;
			if (!m_set.AutoUseCamFP && !m_set.AutoUseDrink) { // 使用cam补充fp
															  //CoreLog() << "Task.Challenge: Task Over: Setted No Use FP." << std::endl;
				throw new StepCompleteException();
			}
			switch (Global.WndHandler.WaitForMultiple([m_camFp, m_camFpNo], TimeSpan.FromSeconds(2.0))) {
			case 0:
				//CoreLog() << "Task.Challenge: Try to Use FP: Available." << std::endl;
				pt = m_camFp.GetSpecialPointInResultRect(0);

				Global.WndHandler.ClickAt(pt);
				IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);

				if (!Global.WndHandler.WaitFor(m_camFpComf[0])) {
					//CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No 1st." << std::endl;
					throw new StepCompleteException();
				}
				pt = m_camFpComf[0].GetSpecialPointInResultRect(0);
				if (!Global.WndHandler.KeepClickingUntil(pt, m_camFpComf[1], TimeSpan.FromSeconds(10.0), TimeSpan.FromSeconds(2.0))) {
					//CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No 2st." << std::endl;
					throw new StepCompleteException();
				}
				pt = m_camFpComf[1].GetSpecialPointInResultRect(0);

				Global.WndHandler.ClickAt(pt);
				IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);
				if (!Global.WndHandler.WaitFor(temp_startGame)) {
					//CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No Close." << std::endl;
					throw new StepCompleteException();
				}
				//CoreLog() << "Task.Challenge: Try to Use FP: OK." << std::endl;
				break;
			default:
				//CoreLog() << "Task.Challenge: No FP." << std::endl;
				if (!m_set.AutoUseDrink || !Global.WndHandler.WaitFor(m_camFpDrink, TimeSpan.FromSeconds(2.0))) {
					//CoreLog() << "Task.Challenge: Task Over: No Use Drink." << std::endl;
					throw new StepCompleteException();
				}
				Global.WndHandler.ClickAt(m_camFpDrink.GetSpecialPointInResultRect(0));
				IStep.TaskSleep(TimeSpan.FromMilliseconds(500), m_ct);
				Global.WndHandler.ClickAt(m_camFpDrink.GetSpecialPointInResultRect(1));
				IStep.TaskSleep(TimeSpan.FromMilliseconds(500), m_ct);
				if (!Global.WndHandler.WaitFor(m_camFpDrinkComf, TimeSpan.FromSeconds(2.0))) {
					//CoreLog() << "Task.Challenge: Task Over: Drink No Ok." << std::endl;
					throw new StepCompleteException();
				}
				if (!Global.WndHandler.KeepClickingUntil(m_camFpDrinkComf.GetSpecialPointInResultRect(0), temp_startGame)) {
					//CoreLog() << "Task.Challenge: Task Over: Try to Use Drink: No Close." << std::endl;
					throw new StepCompleteException();
				}
				//CoreLog() << "Task.Challenge: Try to Use Drink: OK." << std::endl;
				break;
			}
			return;
		}

		private void WaitingForEnd() {
			Point pt;

			if (target == PlayMatch.Award) {
				++playAwardCnt;
				//Global.WndHandler.GuiLogF_I(ReturnMsgEnum::ChaBeginAdd_I, playAwardCnt);
				////CoreLog() << "Task.Challenge: Match Award " << playAwardCnt << "." << std::endl;
			}
			else {
				++playCnt;
				//Global.WndHandler.GuiLogF_I(ReturnMsgEnum::ChaBegin_I, playCnt);
				////CoreLog() << "Task.Challenge: Match " << playCnt << "." << std::endl;
			}

			// 等待结束。
			////CoreLog() << "Task.Challenge: In Game, Waitting for End." << std::endl;
			if (!Global.WndHandler.WaitFor(temp_gameResult, TimeSpan.FromSeconds(300.0)))
				throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaTimeOut);

			// 点击，直到进入加载画面。
			////CoreLog() << "Task.Challenge: Game End, Trying to Exit." << std::endl;
			pt = temp_gameResult.GetSpecialPointInResultRect(0);
			if (!Global.WndHandler.KeepClickingUntil(pt, temp_loading, TimeSpan.FromSeconds(60.0), TimeSpan.FromSeconds(0.1)))
				throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaNoEnd);

			// 等待到挑战赛标签页出现。
			////CoreLog() << "Task.Challenge: Game Exit, Waitting for Challenge Page." << std::endl;
			if (!Global.WndHandler.WaitFor(temp_chaBar, TimeSpan.FromSeconds(60.0)))
				throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaNoOver);
			//Global.WndHandler.GuiLogF(ReturnMsgEnum::ChaOver);
		}

		private void CheckForAwrad() {
			Point pt;
			if (!Global.WndHandler.WaitFor(temp_awardCha, TimeSpan.FromSeconds(2.0))) {
				////CoreLog() << "Task.Challenge: Find Award." << std::endl;
				//Global.WndHandler.GuiLogF(ReturnMsgEnum::ChaFindAdd);
				if (m_set.EnterAddition) { // 进入奖励挑战赛。
					if (target == PlayMatch.New) {
						pt = temp_awardCha.GetSpecialPointInResultRect(0);
						if (Global.WndHandler.KeepClickingUntil(pt, temp_newFight, TimeSpan.FromSeconds(10.0), TimeSpan.FromSeconds(2.0))) {
							//Global.WndHandler.GuiLogF(ReturnMsgEnum::ChaOpenedAdd);
							target = PlayMatch.Award;
							playAwardCnt = 0;
						}
						else {
							throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaOpenAddFailed);
						}
					}
					else {
						throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaAddNotSup);
					}
				}
				else { // 回到“推荐”栏。
					if (Global.WndHandler.WaitFor(temp_chaBar, TimeSpan.FromSeconds(5.0))) {
						pt = temp_chaBar.GetSpecialPointInResultRect(0);
						if (Global.WndHandler.KeepClickingUntilNo(pt, temp_awardCha, TimeSpan.FromSeconds(10.0), TimeSpan.FromSeconds(0.5))) {
							//Global.WndHandler.GuiLogF(ReturnMsgEnum::ChaIgnoredAdd);
						}
						else {
							throw new Exception();// Global.WndHandler.TaskError(ReturnMsgEnum::TaskErrChaIgnoreAddFailed);
						}
					}
				}
			}
			else {
				////CoreLog() << "Task.Challenge: Not Find Award." << std::endl;
				//Global.WndHandler.GuiLogF(ReturnMsgEnum::ChaNotFindAdd);
			}
		}

	}
}
