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
				uint up, rank;
				// 寻找目标等级
				got = Global.WndHandler.WaitOneFrame();
				HelperKernel.IEye mat = Global.WndHandler.Eye;
				if (!got) {
					needManual = true;
					break;
				}
				up = 0;
				rank = 0;
				for (int i = 4; i >= 0; --i) {
					if (m_act100pre[i].TryMatch(mat)) {
						int abspos = i - Settings.challenge.SelectedActivityLevel + 1;
						if (abspos < 0) {
							up = (uint)-abspos;
							rank = 0;
						}
						else {
							up = 0;
							rank = (uint)abspos;
						}
						break;
					}
				}
				if (up == 0 || rank == 0 || rank > 4) {
					needManual = true;
					break;
				}
				if (up > 0) {
					Global.WndHandler.Hand.MoveMouseWheel(false, up);
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
				up = 0;
				rank = 0;
				for (int i = 4; i >= 0; --i) {
					if (m_actSlevel[i].TryMatch(mat)) {
						int abspos = i - Settings.challenge.SelectedActivityMatch + 1;
						if (abspos < 0) {
							up = (uint)-abspos;
							rank = 0;
						}
						else {
							up = 0;
							rank = (uint)abspos;
						}
						break;
					}
				}
				if (up == 0 || rank == 0 || rank > 4) {
					needManual = true;
					break;
				}
				if (up > 0) {
					Global.WndHandler.Hand.MoveMouseWheel(false, up);
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
					Global.Worker.TaskWaitForResume(ReturnMsgEnum::ManualNavigateToChallengePage);
					Global.WndHandler.SetForGame();
				}
				else {
					//CoreLog() << "Task.Challenge: First Navigate Failed." << std::endl;
					throw new TaskCanceledException();
				}
			}
			m_loopSt = LoopStatus.Begin;
		}

		private void InitNavigate() {
		}

		private void EnterConfirmPage() {
		}

		private void StartMatch() {
		}

		private void HandleLowFp() {
		}

		private void WaitingForEnd() {
		}

		private void CheckForAwrad() {
		}

	}
}
