﻿/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
* 
*     Copyright 2023-2025  Tyler Parret True
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
using System.Drawing;

namespace Helper.Step {
	internal class Challenge : IStep {

		~Challenge() {
			Dispose(false);
		}

		public void Dispose() {
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		private bool _disposed = false;
		protected void Dispose(bool disposing) {
			if (_disposed)
				return;
			_disposed = true;
			if (disposing) {
				temp_chaBar.Dispose();
				temp_lastFight.Dispose();
				temp_newFight.Dispose();
				temp_startGame.Dispose();
				temp_loading.Dispose();
				temp_lowFp.Dispose();
				temp_gameResult.Dispose();
				temp_awardCha.Dispose();
				m_camFp.Dispose();
				m_camFpDrink.Dispose();
				m_camFpDrinkComf.Dispose();
				m_camFpNo.Dispose();

				foreach (var p in m_camFpComf) {
					p.Dispose();
				}
				foreach (var p in m_act100pre) {
					p.Dispose();
				}
				foreach (var p in m_actSlevel) {
					p.Dispose();
				}
			}
		}

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

		private CancellationToken m_ct;

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

			temp_chaBar = PatternManager.CreatePattern("default");
			temp_lastFight = PatternManager.CreatePattern("lastFight");
			temp_newFight = PatternManager.CreatePattern("newFight");
			temp_startGame = PatternManager.CreatePattern("start");
			temp_loading = PatternManager.CreatePattern("loading");
			temp_lowFp = PatternManager.CreatePattern("fp");
			temp_gameResult = PatternManager.CreatePattern("result");
			temp_awardCha = PatternManager.CreatePattern("add");
			m_camFp = PatternManager.CreatePattern("UseFp");
			m_camFpNo = PatternManager.CreatePattern("cha/shotFpNo");

			m_camFpComf = [
				PatternManager.CreatePattern("UseFpComf0"),
				PatternManager.CreatePattern("UseFpComf1"),
			];

			m_camFpDrink = PatternManager.CreatePattern("cha/drink");
			m_camFpDrinkComf = PatternManager.CreatePattern("cha/drinkComf");

			m_act100pre = [
				PatternManager.CreatePattern("cha/act/l0"),
				PatternManager.CreatePattern("cha/act/l1"),
				PatternManager.CreatePattern("cha/act/l2"),
				PatternManager.CreatePattern("cha/act/l3"),
				PatternManager.CreatePattern("cha/act/l4"),
			];

			m_actSlevel = [
				PatternManager.CreatePattern("cha/act/r0"),
				PatternManager.CreatePattern("cha/act/r1"),
				PatternManager.CreatePattern("cha/act/r2"),
				PatternManager.CreatePattern("cha/act/r3"),
				PatternManager.CreatePattern("cha/act/r4"),
			];

			//CoreLog() << "Task.Challenge: Finish Load Templates." << std::endl;
			return;
		}

		public void Run(CancellationToken ct) {
			m_ct = ct;

			try {
				GUICallbacks.LockStepChallenge(true);
				//CoreLog() << "Task.Challenge: Start." << std::endl;

				IStep.Log(
					GUICallbacks.LogInfo.Type.Info,
					LogStr.StepChaEnter
				);

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
						if (Settings.challenge.CheckAddition)
							CheckForAwrad();
						m_loopSt = LoopStatus.End;
						break;
					case LoopStatus.End:
						//CoreLog() << "Task.Challenge: Loop End." << std::endl;
						IStep.TaskSleep(TimeSpan.FromSeconds(1), ct);
						m_loopSt = LoopStatus.Begin;
						break;
					}
				}
			}
			catch (StepErrorContinueException ex) {
				IStep.Log(
					GUICallbacks.LogInfo.Type.Error,
					string.Format(LogStr.StepErr_X, ex.Message)
					);
			}
			catch (StepCompleteException) {
				IStep.Log(
					GUICallbacks.LogInfo.Type.Info,
					LogStr.StepComplete
				);
			}
			finally {
				GUICallbacks.LockStepChallenge(false);
			}

			//CoreLog() << "Task.Challenge: Exit." << std::endl;
			IStep.Log(
				GUICallbacks.LogInfo.Type.Info,
				LogStr.StepChaExit
			);
			return;
		}

		private void SetHandler() {
			if (!WndHandler.SetForGame()) {
				/*case WndHandler::SetReturnValue::WndNotFound:
					CoreLog() << "Task.Challenge: Game Window Not Found." << std::endl;
					r_helper->TaskError(ReturnMsgEnum::TaskErrNoWnd);
					break;
				case WndHandler::SetReturnValue::CaptureFailed:
					CoreLog() << "Task.Challenge: Game Window Cannot Capture." << std::endl;
					r_helper->TaskError(ReturnMsgEnum::TaskErrNoCap);
					break;*/
				;
				throw new StepErrorContinueException("Cannot set handler");
			}
			//CoreLog() << "Task.Challenge: Window Handler Setted." << std::endl;
			return;
		}

		private void FirstNavigate() {
			bool res = Navigate.NavigateTo(Navigate.Page.Challenge);
			IStep.TaskSleep(TimeSpan.FromSeconds(3), m_ct);
			bool needManual = false;
			switch (Settings.challenge.PlayMatch) {
			case 1: // 新比赛
				if (!WndHandler.WaitFor(temp_newFight, TimeSpan.FromSeconds(1)))
					needManual = true;
				break;
			case 2: // 活动关卡
			{
				if (!res) {
					needManual = true;
					break;
				}
				if (!WndHandler.WaitFor(temp_chaBar, TimeSpan.FromSeconds(1))) {
					needManual = true;
					break;
				}
				// 到“活动页”
				WndHandler.ClickAt(temp_chaBar.GetSpecialPointInResultRect(3));

				IStep.TaskSleep(TimeSpan.FromSeconds(1), m_ct);

				// 滚动到最底部
				WndHandler.Hand.MoveCursorTo(new Point(920, 530));
				IStep.TaskSleep(TimeSpan.FromSeconds(0.5), m_ct);
				WndHandler.Hand.MoveMouseWheel(true, 12u);

				IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);

				bool got;
				int up, rank;
				// 寻找目标等级
				got = WndHandler.WaitOneFrame();
				HelperKernel.IEye mat = WndHandler.Eye;
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
					WndHandler.Hand.MoveMouseWheel(false, (uint)up);
				}
				IStep.TaskSleep(TimeSpan.FromSeconds(0.5), m_ct);
				WndHandler.ClickAt(m_act100pre[rank].GetSpecialPointInSearchRect(0));

				IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);
				// 已经进入目标等级

				// 滚动到最底部
				WndHandler.Hand.MoveCursorTo(new Point(920, 530));
				IStep.TaskSleep(TimeSpan.FromSeconds(0.5), m_ct);
				WndHandler.Hand.MoveMouseWheel(true, 12u);

				IStep.TaskSleep(TimeSpan.FromSeconds(0.5), m_ct);

				// 寻找目标关卡
				got = WndHandler.WaitOneFrame();
				if (!got) {
					needManual = true;
					break;
				}
				mat = WndHandler.Eye;
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
					WndHandler.Hand.MoveMouseWheel(false, (uint)up);
				}
				IStep.TaskSleep(TimeSpan.FromSeconds(0.5), m_ct);
				WndHandler.ClickAt(m_actSlevel[rank].GetSpecialPointInSearchRect(0));
				IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);
				break;
			}
			default: // 当前/上次
				switch (Navigate.TryToDeterminePage()) {
				case Navigate.Page.MatchConfirm:
				case Navigate.Page.MatchResult:
					break;
				default:
					if (!WndHandler.WaitFor(temp_lastFight, TimeSpan.FromSeconds(1)))
						needManual = true;
					break;
				}
				break;
			}
			if (needManual) {
				if (Settings.challenge.AskForManual) {
					WndHandler.Reset();
					IStep.Log(
						GUICallbacks.LogInfo.Type.Warn,
						LogStr.ManualChaPageNavigate
						);
					Worker.PauseForManual(m_ct);
					SetHandler();
				}
				else {
					//CoreLog() << "Task.Challenge: First Navigate Failed." << std::endl;
					throw new StepErrorContinueException("First Navigate Failed.");
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
				if (!WndHandler.WaitFor(temp_chaBar)) {
					//CoreLog() << "Task.Challenge: Navigate Failed: No ChaBar." << std::endl;
					throw new Exception();// TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
				}
				WndHandler.ClickAt(temp_chaBar.GetSpecialPointInResultRect(0));
				IStep.TaskSleep(TimeSpan.FromMilliseconds(500), m_ct);
				break;
			case Navigate.Page.MatchConfirm:
				//CoreLog() << "Task.Challenge: Navigate Detected: Match Confirm." << std::endl;
				m_loopSt = LoopStatus.Start;
				return;
			case Navigate.Page.MatchResult:
				//CoreLog() << "Task.Challenge: Navigate Detected: Match Result." << std::endl;
				m_loopSt = LoopStatus.Wait;
				return;
			default:
				//CoreLog() << "Task.Challenge: Navigate Detected: Others." << std::endl;
				if (!Navigate.NavigateTo(Navigate.Page.Challenge)) {
					//CoreLog() << "Task.Challenge: Navigate Failed." << std::endl;
					throw new Exception();// TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
				}
				IStep.TaskSleep(TimeSpan.FromSeconds(2.0), m_ct);
				if (!WndHandler.WaitFor(temp_chaBar)) {
					//CoreLog() << "Task.Challenge: Navigate Failed: No ChaBar." << std::endl;
					throw new Exception();// TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
				}
				WndHandler.ClickAt(temp_chaBar.GetSpecialPointInResultRect(0));
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
				if (!WndHandler.WaitFor(temp_lastFight))
					throw new StepErrorContinueException(LogStr.StepChaErrMatchNoPrevious);
				//CoreLog() << "Task.Challenge: Enter Game <Previous>." << std::endl;
				pt = new(900, temp_lastFight.GetPreviousMatchedRect().Y);
				break;
			case PlayMatch.New:
				if (!WndHandler.WaitFor(temp_newFight))
					throw new StepErrorContinueException(LogStr.StepChaErrMatchNoNew);
				//CoreLog() << "Task.Challenge: Enter Game <New>." << std::endl;
				pt = new(900, temp_newFight.GetPreviousMatchedRect().Y);
				break;
			case PlayMatch.Activity:
				if (!WndHandler.WaitFor(temp_lastFight))
					throw new StepErrorContinueException(LogStr.StepChaErrMatchNoPrevious);
				//CoreLog() << "Task.Challenge: Enter Game <Previous>." << std::endl;
				pt = new(900, temp_lastFight.GetPreviousMatchedRect().Y);
				break;
			case PlayMatch.Award:
				if (!WndHandler.WaitFor(temp_newFight))
					throw new StepErrorContinueException(LogStr.StepChaErrMatchNoNew);
				//CoreLog() << "Task.Challenge: Enter Game <Award>." << std::endl;
				pt = new(900, temp_newFight.GetPreviousMatchedRect().Y);
				break;
			default:
				goto case PlayMatch.Previous;
			}

			// 点击比赛，直到进入编队画面（找到挑战按钮）。
			if (!WndHandler.KeepClickingUntil(pt, temp_startGame))
				throw new StepErrorContinueException(LogStr.StepChaErrFailedEnterMatch);
		}

		private void StartMatch() {
			Point pt;
			//CoreLog() << "Task.Challenge: Search for Match Start Button." << std::endl;
			// 查找“挑战”按钮。
			bool triedFp = false;
			WndHandler.WaitFor(temp_startGame);
			//CoreLog() << "Task.Challenge: Play Game." << std::endl;
			for (int i = 0, n = 10; i < n; ++i) {
				//CoreLog() << "Task.Challenge: Start Match Loop: " << i << "." << std::endl;
				pt = temp_startGame.GetSpecialPointInResultRect(0);
				WndHandler.ClickAt(pt);
				switch (WndHandler.WaitForMultiple([temp_loading, temp_lowFp], TimeSpan.FromSeconds(2.0))) {
				default:
				case -1:
					//CoreLog() << "Task.Challenge: Start Match Loop: Not Found." << std::endl;
					if (i == n - 1) {
						//CoreLog() << "Task.Challenge: Failed to Start Match." << std::endl;
						throw new StepErrorContinueException(LogStr.StepChaErrMatchNoStart);
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
			if (!Settings.challenge.AutoUseCamFP && !Settings.challenge.AutoUseDrink) { // 使用cam补充fp
															  //CoreLog() << "Task.Challenge: Task Over: Setted No Use FP." << std::endl;
				throw new StepCompleteException();
			}
			switch (WndHandler.WaitForMultiple([m_camFp, m_camFpNo], TimeSpan.FromSeconds(2.0))) {
			case 0:
				//CoreLog() << "Task.Challenge: Try to Use FP: Available." << std::endl;
				pt = m_camFp.GetSpecialPointInResultRect(0);

				WndHandler.ClickAt(pt);
				IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);

				if (!WndHandler.WaitFor(m_camFpComf[0])) {
					//CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No 1st." << std::endl;
					throw new StepCompleteException();
				}
				pt = m_camFpComf[0].GetSpecialPointInResultRect(0);
				if (!WndHandler.KeepClickingUntil(pt, m_camFpComf[1], TimeSpan.FromSeconds(10.0), TimeSpan.FromSeconds(2.0))) {
					//CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No 2st." << std::endl;
					throw new StepCompleteException();
				}
				pt = m_camFpComf[1].GetSpecialPointInResultRect(0);

				WndHandler.ClickAt(pt);
				IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);
				if (!WndHandler.WaitFor(temp_startGame)) {
					//CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No Close." << std::endl;
					throw new StepCompleteException();
				}
				//CoreLog() << "Task.Challenge: Try to Use FP: OK." << std::endl;
				break;
			default:
				//CoreLog() << "Task.Challenge: No FP." << std::endl;
				if (!Settings.challenge.AutoUseDrink || !WndHandler.WaitFor(m_camFpDrink, TimeSpan.FromSeconds(2.0))) {
					//CoreLog() << "Task.Challenge: Task Over: No Use Drink." << std::endl;
					throw new StepCompleteException();
				}
				WndHandler.ClickAt(m_camFpDrink.GetSpecialPointInResultRect(0));
				IStep.TaskSleep(TimeSpan.FromMilliseconds(500), m_ct);
				WndHandler.ClickAt(m_camFpDrink.GetSpecialPointInResultRect(1));
				IStep.TaskSleep(TimeSpan.FromMilliseconds(500), m_ct);
				if (!WndHandler.WaitFor(m_camFpDrinkComf, TimeSpan.FromSeconds(2.0))) {
					//CoreLog() << "Task.Challenge: Task Over: Drink No Ok." << std::endl;
					throw new StepCompleteException();
				}
				if (!WndHandler.KeepClickingUntil(m_camFpDrinkComf.GetSpecialPointInResultRect(0), temp_startGame)) {
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
				IStep.Log(
					GUICallbacks.LogInfo.Type.Info,
					string.Format(LogStr.StepChaStartAwdMatchI, playAwardCnt)
					);
				//CoreLog() << "Task.Challenge: Match Award " << playAwardCnt << "." << std::endl;
			}
			else {
				++playCnt;
				IStep.Log(
					GUICallbacks.LogInfo.Type.Info,
					string.Format(LogStr.StepChaStartMatchI, playCnt)
					);
				//CoreLog() << "Task.Challenge: Match " << playCnt << "." << std::endl;
			}

			// 等待结束。
			//CoreLog() << "Task.Challenge: In Game, Waitting for End." << std::endl;
			if (!WndHandler.WaitFor(temp_gameResult, TimeSpan.FromSeconds(300.0)))
				throw new StepErrorContinueException(LogStr.StepChaErrGameTimeout);

			// 点击，直到进入加载画面。
			//CoreLog() << "Task.Challenge: Game End, Trying to Exit." << std::endl;
			pt = temp_gameResult.GetSpecialPointInResultRect(0);
			if (!WndHandler.KeepClickingUntil(pt, temp_loading, TimeSpan.FromSeconds(60.0), TimeSpan.FromSeconds(0.1)))
				throw new StepErrorContinueException(LogStr.StepChaErrMatchNoOver);

			// 等待到挑战赛标签页出现。
			//CoreLog() << "Task.Challenge: Game Exit, Waitting for Challenge Page." << std::endl;
			if (!WndHandler.WaitFor(temp_chaBar, TimeSpan.FromSeconds(60.0)))
				throw new StepErrorContinueException(LogStr.StepChaErrFailedExitMatch);

			IStep.Log(
				GUICallbacks.LogInfo.Type.Info,
				LogStr.StepChaMatchOver
				);
		}

		private void CheckForAwrad() {
			Point pt;
			if (!WndHandler.WaitFor(temp_awardCha, TimeSpan.FromSeconds(2.0))) {
				//CoreLog() << "Task.Challenge: Find Award." << std::endl;
				IStep.Log(
					GUICallbacks.LogInfo.Type.Info,
					LogStr.StepChaAwdFound
					);
				if (Settings.challenge.EnterAddition) { // 进入奖励挑战赛。
					if (target == PlayMatch.New) {
						pt = temp_awardCha.GetSpecialPointInResultRect(0);
						if (WndHandler.KeepClickingUntil(pt, temp_newFight, TimeSpan.FromSeconds(10.0), TimeSpan.FromSeconds(2.0))) {
							IStep.Log(
								GUICallbacks.LogInfo.Type.Info,
								LogStr.StepChaAwdOpened
								);
							target = PlayMatch.Award;
							playAwardCnt = 0;
						}
						else {
							throw new StepErrorContinueException(LogStr.StepChaErrAwdFailedOpen);
						}
					}
					else {
						throw new StepErrorContinueException(LogStr.StepChaErrAwdNotSup);
					}
				}
				else { // 回到“推荐”栏。
					if (WndHandler.WaitFor(temp_chaBar, TimeSpan.FromSeconds(5.0))) {
						pt = temp_chaBar.GetSpecialPointInResultRect(0);
						if (WndHandler.KeepClickingUntilNo(pt, temp_awardCha, TimeSpan.FromSeconds(10.0), TimeSpan.FromSeconds(0.5))) {
							IStep.Log(
								GUICallbacks.LogInfo.Type.Info,
								LogStr.StepChaAwdIgnored
								);
						}
						else {
							throw new StepErrorContinueException(LogStr.StepChaErrIgnoreAwdFailed);
						}
					}
				}
			}
			else {
				//CoreLog() << "Task.Challenge: Not Find Award." << std::endl;
				IStep.Log(
					GUICallbacks.LogInfo.Type.Info,
					LogStr.StepChaAwdNotFound
					);
			}
		}
	}
}
