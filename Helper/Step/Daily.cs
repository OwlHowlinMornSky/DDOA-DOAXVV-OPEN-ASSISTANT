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
	internal class Daily : IStep {
		~Daily() {
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
				m_homeAct.Dispose();
				m_homeDailyBtn.Dispose();
				m_homeDailyDot.Dispose();
				m_checkBtn.Dispose();
				m_checkBdTitle.Dispose();
				m_checkOk.Dispose();

				m_shotEntrance.Dispose();
				m_shotDot.Dispose();
				m_shotBack.Dispose();
				m_shot.Dispose();
				m_homePage.Dispose();
			}
		}

		private readonly Pattern m_homeAct;
		private readonly Pattern m_homeDailyBtn;
		private readonly Pattern m_homeDailyDot;
		private readonly Pattern m_checkBtn;
		private readonly Pattern m_checkBdTitle;
		private readonly Pattern m_checkOk;

		private readonly Pattern m_shotEntrance;
		private readonly Pattern m_shotDot;
		private readonly Pattern m_shotBack;
		private readonly Pattern m_shot;
		private readonly Pattern m_homePage;

		private CancellationToken m_ct;

		public Daily() {
			m_homeAct = PatternManager.CreatePattern("daily/act");
			m_homeDailyBtn = PatternManager.CreatePattern("daily/checkEntrance");
			m_homeDailyDot = PatternManager.CreatePattern("daily/checkDotN");
			m_checkBtn = PatternManager.CreatePattern("daily/checkClk");
			m_checkBdTitle = PatternManager.CreatePattern("daily/chkBdTitle");
			m_checkOk = PatternManager.CreatePattern("daily/checkOK");
			//CoreLog() << "Task_Daily: Check: Load Templates Over." << std::endl;

			m_shotEntrance = PatternManager.CreatePattern("daily/shotEntranceN");
			m_shotDot = PatternManager.CreatePattern("daily/shotDotN");
			m_shotBack = PatternManager.CreatePattern("daily/shotBack");
			m_shot = PatternManager.CreatePattern("daily/shotShot");
			m_homePage = PatternManager.CreatePattern("homeSpec");
			//CoreLog() << "Task_Daily: Shot: Load Templates Over." << std::endl;
		}

		public void Run(CancellationToken ct) {
			m_ct = ct;

			try {
				GUICallbacks.LockStepDaily(true);
				//CoreLog() << "Task_Daily: Start." << std::endl;
				IStep.Log(
					GUICallbacks.LogInfo.Type.Notice,
					LogStr.StepDailyEnter
					);

				if (!WndHandler.SetForGame()) {
					/*case WndHandler::SetReturnValue::WndNotFound:
						h.TaskError(ReturnMsgEnum::TaskErrNoWnd);
						break;
					case WndHandler::SetReturnValue::CaptureFailed:
						h.TaskError(ReturnMsgEnum::TaskErrNoCap);
						break;*/
					throw new StepErrorContinueException("Failed to Capture");
				}
				//CoreLog() << "Task_Daily: Handler Setted." << std::endl;

				if (Settings.daily.DoCheck) {
					//CoreLog() << "Task_Daily: Try Check." << std::endl;
					DoCheck();
				}
				else {
					//CoreLog() << "Task_Daily: Setting No Check." << std::endl;
				}

				if (Settings.daily.DoShot) {
					//CoreLog() << "Task_Daily: Try Shot." << std::endl;
					DoShot();
				}
				else {
					//CoreLog() << "Task_Daily: Setting No Shot." << std::endl;
				}
			}
			catch (Exception) {
				IStep.Log(
					GUICallbacks.LogInfo.Type.Error,
					LogStr.StepDailyFailed
					);
			}
			finally {
				GUICallbacks.LockStepDaily(false);
			}


			IStep.Log(
				GUICallbacks.LogInfo.Type.Notice,
				LogStr.StepDailyExit
				);
			//CoreLog() << "Task_Daily: Exit." << std::endl;
			return;
		}


		private void DoCheck() {
			if (IsDailCheckDone()) {
				WndHandler.Hand.MoveCursorTo(new Point(0, 0));
				SwitchActPanel();
				//CoreLog() << "Task_Daily: Check: Exit: Done." << std::endl;
				return;
			}
			//CoreLog() << "Task_Daily: Check: Not Done." << std::endl;
			if (!OpenDailyCheckBoard()) {
				//CoreLog() << "Task_Daily: Check: Cannot Open." << std::endl;

				IStep.Log(
					GUICallbacks.LogInfo.Type.Error,
					LogStr.StepErr + " (1)"
					);
				//r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
				return;
			}
			if (!DoDailyCheckInBoard()) {
				//CoreLog() << "Task_Daily: Check: Cannot Check." << std::endl;
				IStep.Log(
					GUICallbacks.LogInfo.Type.Error,
					LogStr.StepErr + " (2)"
					);
				//r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
			}
			if (!CloseCheckBoard()) {
				//CoreLog() << "Task_Daily: Check: Cannot Close." << std::endl;
				IStep.Log(
					GUICallbacks.LogInfo.Type.Error,
					LogStr.StepErr + " (3)"
					);
				//r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
			}
			return;
		}

		private void DoShot() {
			if (IsShotDone()) {
				return;
			}
			if (!OpenShotPage()) {
				//CoreLog() << "Task_Daily: Shot: Cannot Open." << std::endl;
				IStep.Log(
					GUICallbacks.LogInfo.Type.Error,
					LogStr.StepErr + " (4)"
					);
				//r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
				return;
			}
			WndHandler.Hand.MoveCursorTo(new Point(0, 0));
			if (!DoShotInPage()) {
				//CoreLog() << "Task_Daily: Shot: Cannot Shot." << std::endl;
				IStep.Log(
					GUICallbacks.LogInfo.Type.Error,
					LogStr.StepErr + " (5)"
					);
				//r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
			}
			if (!CloseShotPage()) {
				//CoreLog() << "Task_Daily: Shot: Cannot Close." << std::endl;
				IStep.Log(
					GUICallbacks.LogInfo.Type.Error,
					LogStr.StepErr + " (6)"
					);
				//r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
			}
			return;
		}

		private bool SwitchActPanel() {
			if (!WndHandler.WaitFor(m_homeAct)) {
				// 超时
				return false;
			}

			WndHandler.ClickAt(m_homeAct.GetSpecialPointInResultRect(0));

			IStep.TaskSleep(TimeSpan.FromSeconds(1), m_ct);

			return true;
		}

		private bool IsDailCheckDone() {
			Navigate.NavigateTo(Navigate.Page.Home);

			if (!SwitchActPanel()) {
				return true;
			}
			if (!WndHandler.WaitFor(m_homeDailyBtn)) {
				// 超时
				return true;
			}

			Rectangle rect = new(m_homeDailyBtn.GetPreviousMatchedRect().Location, m_homeDailyDot.GetSearchRect().Size);

			WndHandler.WaitOneFrame();
			bool res = m_homeDailyDot.TryMatch(WndHandler.Eye, rect);
			return !res;

		}

		private bool OpenDailyCheckBoard() {
			Navigate.NavigateTo(Navigate.Page.Home);

			if (!WndHandler.WaitFor(m_homeDailyBtn)) {
				// 超时
				return false;
			}

			WndHandler.KeepClickingUntil(
				m_homeDailyBtn.GetSpecialPointInResultRect(0),
				m_checkBdTitle
			);

			WndHandler.Hand.MoveCursorTo(m_checkBdTitle.GetSpecialPointInSearchRect(0));

			IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);

			return true;
		}

		private bool DoDailyCheckInBoard() {
			if (!WndHandler.WaitFor(m_checkBtn)) {
				// 超时
				return false;
			}

			WndHandler.KeepClickingUntil(
				m_checkBtn.GetSpecialPointInResultRect(0),
				m_checkOk
			);
			WndHandler.KeepClickingUntil(
				m_checkOk.GetSpecialPointInResultRect(0),
				m_checkBdTitle
			);
			IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);

			return true;
		}

		private bool CloseCheckBoard() {
			return Navigate.NavigateTo(Navigate.Page.Home);
		}

		private bool IsShotDone() {
			Navigate.NavigateTo(Navigate.Page.Home);

			if (!WndHandler.WaitFor(m_shotEntrance)) {
				// 超时
				return false;
			}

			WndHandler.WaitOneFrame();
			bool res = m_shotDot.TryMatch(WndHandler.Eye);

			return !res;
		}

		private bool OpenShotPage() {
			Navigate.NavigateTo(Navigate.Page.Home);

			if (!WndHandler.WaitFor(m_shotEntrance)) {
				// 超时
				return false;
			}

			WndHandler.KeepClickingUntil(
				m_shotEntrance.GetSpecialPointInResultRect(0),
				m_shot,
				TimeSpan.FromSeconds(20.0),
				TimeSpan.FromSeconds(3.0)
			);
			IStep.TaskSleep(TimeSpan.FromSeconds(2.0), m_ct);

			return true;
		}

		private bool DoShotInPage() {
			if (!WndHandler.WaitFor(m_shot)) {
				// 超时
				return false;
			}

			WndHandler.ClickAt(m_shot.GetSpecialPointInResultRect(0));
			IStep.TaskSleep(TimeSpan.FromSeconds(2.0), m_ct);

			return true;
		}

		private bool CloseShotPage() {
			if (!WndHandler.WaitFor(m_shotBack)) {
				// 超时
				return false;
			}

			WndHandler.KeepClickingUntil(
				m_shotBack.GetSpecialPointInResultRect(0),
				m_homePage
			);
			IStep.TaskSleep(TimeSpan.FromSeconds(1.0), m_ct);

			return true;
		}
	}
}