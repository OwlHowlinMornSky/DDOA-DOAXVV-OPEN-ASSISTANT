using System.Drawing;
using System.Diagnostics;
using HelperKernel;
using System.Text.RegularExpressions;

namespace Helper {
	internal class WndHandler() {

		const string g_findCls = "DOAX VenusVacation"; // 查找doaxvv窗口的类的名字
		const string g_findWnd = "DOAX VenusVacation"; // 查找doaxvv窗口的名字
		const string g_finGWnd = "DOAX VenusVacation Launcher"; // 查找doaxvv launcher窗口的名字
		const string g_finDWnd = "DDOA-DEBUG"; // 查找调试窗口的名字

		internal enum State {
			Idle = 0,
			Launcher,
			Game,
			DebuggerGame,
			DebuggerLauncher,
		}

		private readonly EyeOnWnd m_eye = new();
		private readonly HandOnWnd m_hand = new();

		private State m_state;
		private CancellationToken r_ct;

		internal IEye Eye {
			get {
				return m_eye;
			}
		}

		internal IHand Hand {
			get {
				return m_hand;
			}
		}

		/**
		 * @brief 重设状态，清除目标窗口。
		 */
		internal void Reset() {
			m_state = State.Idle;
		}

		internal void SetCancellationToken(CancellationToken ct) {
			r_ct = ct;
		}

		/**
		 * @brief 设定目标窗口为DOAXVV的登录器窗口。
		 * @return “设定”操作的状态。
		 */
		internal bool SetForLauncher() {
			if (Settings.wndHandler.Debug_DebugHandler) {
				return SetForDebugger(true);
			}
			if (m_state == State.Game)
				return true;
			Reset();

			if (!m_hand.SetOnWnd(g_findCls, g_finGWnd)) {
				return false;
			}
			if (!m_eye.SetOnWnd(g_findCls, g_finGWnd)) {
				m_hand.Reset();
				return false;
			}

			if (Settings.wndHandler.UseHook && !Settings.wndHandler.UseSendInput)
				m_hand.SetUserCursorInterceptionEnabled(true);
			//if (!m_hand.SetUserCursorInterceptionEnabled(true))
			//	IHelper::instance()->GuiLogF(ReturnMsgEnum::HookFailed);
			m_state = State.Game;
			return true;
		}

		/**
		 * @brief 设定目标窗口为DOAXVV的游戏窗口。
		 * @return “设定”操作的状态。
		 */
		internal bool SetForGame() {
			if (Settings.wndHandler.Debug_DebugHandler) {
				return SetForDebugger(true);
			}
			if (m_state == State.Game)
				return true;
			Reset();

			if (!m_hand.SetOnWnd(g_findCls, g_findWnd)) {
				return false;
			}
			if (!m_eye.SetOnWnd(g_findCls, g_findWnd)) {
				m_hand.Reset();
				return false;
			}

			if (Settings.wndHandler.UseHook && !Settings.wndHandler.UseSendInput)
				m_hand.SetUserCursorInterceptionEnabled(true);
			//if (!m_hand.SetUserCursorInterceptionEnabled(true))
			//	IHelper::instance()->GuiLogF(ReturnMsgEnum::HookFailed);
			m_state = State.Game;
			return true;
		}

		/**
		 * @brief 设定目标窗口为DDOA调试器窗口。
		 * @param isGame 操作重定向类型。
		 * @return “设定”操作的状态。
		 */
		protected bool SetForDebugger(bool isGame) {
			if (Settings.wndHandler.Debug_DebugHandler) {
				return SetForDebugger(true);
			}
			if (m_state == State.DebuggerGame || m_state == State.DebuggerLauncher) {
				m_state = isGame ? State.DebuggerGame : State.DebuggerLauncher;
				return true;
			}
			Reset();

			if (!m_hand.SetOnWnd(null, g_finDWnd)) {
				return false;
			}
			if (!m_eye.SetOnWnd(null, g_finDWnd)) {
				m_hand.Reset();
				return false;
			}

			if (Settings.wndHandler.UseHook && !Settings.wndHandler.UseSendInput)
				m_hand.SetUserCursorInterceptionEnabled(true);
			//if (!m_hand.SetUserCursorInterceptionEnabled(true))
			//	IHelper::instance()->GuiLogF(ReturnMsgEnum::HookFailed);
			m_state = isGame ? State.DebuggerGame : State.DebuggerLauncher;
			return true;
		}

		/// <summary>
		/// 获取当前设定的目标。
		/// </summary>
		/// <returns>设定的目标。</returns>
		internal State GetState() {
			return m_state switch {
				State.DebuggerGame => State.Game,
				State.DebuggerLauncher => State.Launcher,
				_ => m_state
			};
		}

		/**
		 * @brief 对目前设定窗口截取一帧。
		 * @param store 保存这一帧的地方。
		 * @param maxTime 最大等待时间。
		 * @return true 则已获取，否则超时。
		 */
		internal bool WaitOneFrame(TimeSpan? timeout = null) {
			ExsureAbleToRun();
			timeout ??= TimeSpan.FromSeconds(10);

			m_eye.RequireRefresh();
			Stopwatch watch = new();
			watch.Restart();
			while (true) {
				r_ct.ThrowIfCancellationRequested();
				if (m_eye.SaveVision())
					break;
				if (timeout > TimeSpan.Zero && watch.Elapsed > timeout) // 应用超时
					return false;
				Thread.Sleep(TimeSpan.FromMilliseconds(30));
			}
			return true;
		}

		/// <summary>
		/// 等待画面出现模板。
		/// </summary>
		/// <param name="pattern">模板。</param>
		/// <param name="timeout">限时。</param>
		/// <returns>false为超时，true为匹配成功。</returns>
		internal bool WaitFor(Pattern pattern, TimeSpan? timeout = null) {
			ExsureAbleToRun();
			timeout ??= TimeSpan.FromSeconds(10);

			m_eye.RequireRefresh();
			Stopwatch watch = new();
			watch.Restart();
			while (true) {
				r_ct.ThrowIfCancellationRequested();
#if DEBUG
				if (m_eye.SaveVision()) {
					bool matchRes = pattern.TryMatch(m_eye);
					if (Settings.wndHandler.Debug_ShowCapture) {
						if (pattern.IsFloatingArea()) {
							m_eye.DrawRectangle(pattern.GetSearchRect(), Color.Blue); // 蓝线画寻找范围框
							m_eye.DrawRectangle(pattern.GetPreviousMatchedRect(), matchRes ? Color.Green : Color.Red); // 画最佳匹配框（满足阈值为绿，否则为红）
						}
						else {
							m_eye.DrawRectangle(pattern.GetSearchRect(), matchRes ? Color.Green : Color.Red); // 画寻找范围框（满足阈值为绿，否则为红）
						}
						m_eye.ShowDebugWindow();
					}
					if (matchRes)
						break;
				}
#else // !DEBUG
				if (m_eye.SaveVision() && pattern.TryMatch(m_eye))
					break;
#endif // DEBUG
				if (timeout > TimeSpan.Zero && watch.Elapsed > timeout) // 应用超时
					return false;
				Thread.Sleep(TimeSpan.FromMilliseconds(30));
			}
			return true;
		}

		/// <summary>
		/// 等待画面出现模板之一。
		/// </summary>
		/// <param name="patterns">模板列。</param>
		/// <param name="timeout">限时。</param>
		/// <returns>-1为超时，自然数则为匹配到的模板的序号。</returns>
		internal int WaitForMultiple(Pattern[] patterns, TimeSpan? timeout) {
			ExsureAbleToRun();
			timeout ??= TimeSpan.FromSeconds(10);

			m_eye.RequireRefresh();
			Stopwatch watch = new();
			int res = -1;
			watch.Restart();
			while (true) {
				r_ct.ThrowIfCancellationRequested();
				if (m_eye.SaveVision()) {
					int c = 0;
					foreach (var i in patterns) {
						if (i.TryMatch(m_eye)) {
							res = c;
							break;
						}
						c++;
					}
#if DEBUG
					if (Settings.wndHandler.Debug_ShowCapture) {
						foreach (var i in patterns) {
							if (i.IsFloatingArea()) {
								m_eye.DrawRectangle(i.GetSearchRect(), Color.Blue); // 蓝线画寻找范围框
								m_eye.DrawRectangle(i.GetPreviousMatchedRect(), Color.Red); // 画最佳匹配框（红）
							}
							else {
								m_eye.DrawRectangle(i.GetSearchRect(), Color.Red); // 画寻找范围框（红）
							}
						}
						if (res > -1) {
							Pattern i = patterns[res];
							if (i.IsFloatingArea()) {
								m_eye.DrawRectangle(i.GetSearchRect(), Color.Blue); // 蓝线画寻找范围框
								m_eye.DrawRectangle(i.GetPreviousMatchedRect(), Color.Green); // 画最佳匹配框（绿）
							}
							else {
								m_eye.DrawRectangle(i.GetSearchRect(), Color.Green); // 画寻找范围框（绿）
							}
						}
						m_eye.ShowDebugWindow();
					}
#endif // DEBUG
					if (res != -1)
						break;
				}
				if (timeout > TimeSpan.Zero && watch.Elapsed > timeout) // 应用超时
					return -1;
				Thread.Sleep(TimeSpan.FromMilliseconds(30));
			}
			return res;
		}

		/// <summary>
		/// 持续点击指定位置，直到画面出现目标。
		/// </summary>
		/// <param name="clkPt">指定点击位置，范围与 step_click 一致</param>
		/// <param name="pattern">目标模板</param>
		/// <param name="timeout">超时时间（小于等于0则为永久）</param>
		/// <param name="clkInterval">点击间隔（不会小于10毫秒）</param>
		/// <returns>true则已找到目标，false则为超时</returns>
		internal bool KeepClickingUntil(
			Point clkPt, Pattern pattern, TimeSpan? timeout = null, TimeSpan? clkInterval = null
		) {
			ExsureAbleToRun();

			timeout ??= TimeSpan.FromSeconds(10);
			clkInterval ??= TimeSpan.FromSeconds(1);

			if (clkInterval > timeout)
				clkInterval = timeout;
			if (clkInterval < TimeSpan.FromMilliseconds(10)) // 点击时间不能小于10毫秒（规定的）
				clkInterval = TimeSpan.FromMilliseconds(10);

			Stopwatch watch = new();
			watch.Restart();
			do {
				if (timeout > TimeSpan.Zero && watch.Elapsed >= timeout) // 应用超时
					return false;
				m_hand.ClickAt(clkPt); // 点击
				r_ct.ThrowIfCancellationRequested();
			} while (!WaitFor(pattern, clkInterval));

			return true;
		}

		/// <summary>
		/// 持续点击指定位置，直到画面没有目标。
		/// </summary>
		/// <param name="clkPt">指定点击位置，范围与 step_click 一致</param>
		/// <param name="pattern">目标模板</param>
		/// <param name="timeout">超时时间（小于等于0则为永久）</param>
		/// <param name="clkInterval">点击间隔（不会小于10毫秒）</param>
		/// <returns>true则已排除目标，false则为超时</returns>
		internal bool KeepClickingUntilNo(
			Point clkPt, Pattern pattern, TimeSpan? timeout = null, TimeSpan? clkInterval = null
		) {
			ExsureAbleToRun();

			timeout ??= TimeSpan.FromSeconds(10);
			clkInterval ??= TimeSpan.FromSeconds(1);

			if (clkInterval > timeout)
				clkInterval = timeout;
			if (clkInterval < TimeSpan.FromMilliseconds(10)) // 点击时间不能小于10毫秒（规定的）
				clkInterval = TimeSpan.FromMilliseconds(10);

			Stopwatch watch = new();
			watch.Restart();
			do {
				if (timeout > TimeSpan.Zero && watch.Elapsed >= timeout) // 应用超时
					return false;
				m_hand.ClickAt(clkPt); // 点击
				r_ct.ThrowIfCancellationRequested();
			} while (WaitFor(pattern, clkInterval));

			return true;
		}

		internal void ClickAt(Point target) {
			ExsureAbleToRun();
			m_hand.ClickAt(target);
		}

		private void ExsureAbleToRun() {
#if DEBUG
			if (m_state == State.Idle)
				throw new WndHandlerNotRunningException();
#endif
		}
	}
}
