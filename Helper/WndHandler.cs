/*
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
using System.Diagnostics;
using HelperKernel;

namespace Helper {
	internal static class WndHandler {

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

		private static readonly EyeOnWnd m_eye = new();
		private static IHand? m_hand = null;

		private static State m_state = State.Idle;
		private static CancellationToken r_ct;

		internal static IEye Eye {
			get {
				return m_eye;
			}
		}

		internal static IHand Hand {
			get {
				if (m_hand == null) {
					if (Settings.wndHandler.UseSendInput) {
						m_hand = new HandOnInput();
					}
					else {
						m_hand = new HandOnWnd();
					}
				}
				return m_hand;
			}
		}

		/**
		 * @brief 重设状态，清除目标窗口。
		 */
		internal static void Reset() {
			m_state = State.Idle;
			m_eye.Reset();
			m_hand?.Reset();
			m_hand = null;
		}

		internal static void SetCancellationToken(CancellationToken ct) {
			r_ct = ct;
		}

		internal static bool LaucherAvailable() {
			return WndHelper.WindowExist(g_findCls, g_finGWnd);
		}

		internal static bool GameWndAvailable() {
			return WndHelper.WindowExist(g_findCls, g_findWnd);
		}

		/**
		 * @brief 设定目标窗口为DOAXVV的登录器窗口。
		 * @return “设定”操作的状态。
		 */
		internal static bool SetForLauncher() {
			if (Settings.wndHandler.Debug_DebugHandler) {
				return SetForDebugger(true);
			}
			if (m_state == State.Launcher)
				return true;
			Reset();

			try {
				SetWindow(g_findCls, g_finGWnd);
			}
			catch {
				return false;
			}

			m_state = State.Game;
			return true;
		}

		/**
		 * @brief 设定目标窗口为DOAXVV的游戏窗口。
		 * @return “设定”操作的状态。
		 */
		internal static bool SetForGame() {
			if (Settings.wndHandler.Debug_DebugHandler) {
				return SetForDebugger(true);
			}
			if (m_state == State.Game)
				return true;
			Reset();

			try {
				SetWindow(g_findCls, g_findWnd);
			}
			catch {
				return false;
			}

			m_state = State.Game;
			return true;
		}

		/**
		 * @brief 设定目标窗口为DDOA调试器窗口。
		 * @param isGame 操作重定向类型。
		 * @return “设定”操作的状态。
		 */
		private static bool SetForDebugger(bool isGame) {
			if (Settings.wndHandler.Debug_DebugHandler) {
				return SetForDebugger(true);
			}
			if (m_state == State.DebuggerGame || m_state == State.DebuggerLauncher) {
				m_state = isGame ? State.DebuggerGame : State.DebuggerLauncher;
				return true;
			}
			Reset();

			try {
				SetWindow(null, g_finDWnd);
			}
			catch {
				return false;
			}

			m_state = isGame ? State.DebuggerGame : State.DebuggerLauncher;
			return true;
		}

		private static void SetWindow(string? className, string windowName) {
			if (m_hand == null) {
				if (Settings.wndHandler.UseSendInput) {
					m_hand = new HandOnInput();
				}
				else {
					m_hand = new HandOnWnd();
				}
			}
			switch (m_hand.SetOnWnd(className, windowName)) {
			case 1:
				throw new WndHandlerWndNotFoundException();
			default:
				break;
			}
			switch (m_eye.SetOnWnd(className, windowName)) {
			case 1:
				m_hand.Reset();
				throw new WndHandlerWndNotFoundException();
			case 2:
				m_hand.Reset();
				throw new WndHandlerCaptureFailedException();
			default:
				break;
			}

			if (Settings.wndHandler.UseHook && !Settings.wndHandler.UseSendInput) {
				string? errorText = m_hand.SetUserCursorInterceptionEnabled(true) switch {
					1 => "Window not found.",
					2 => "Failed to load hook module.",
					3 => "Hook procedure not found.",
					4 => "Failed to get target's pid.",
					5 => "Failed to set hook.",
					_ => null
				};
				if (errorText != null) {
					m_hand.Reset();
					m_eye.Reset();
					throw new WndHandlerHookFailedException(errorText);
				}
			}
		}

		/// <summary>
		/// 获取当前设定的目标。
		/// </summary>
		/// <returns>设定的目标。</returns>
		internal static State GetState() {
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
		internal static bool WaitOneFrame(TimeSpan? timeout = null) {
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
		internal static bool WaitFor(Pattern pattern, TimeSpan? timeout = null) {
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
						m_eye.BeginDebugDraw();
						if (pattern.IsFloatingArea()) {
							m_eye.DrawRectangle(pattern.GetSearchRect(), Color.Blue); // 蓝线画寻找范围框
							m_eye.DrawRectangle(pattern.GetPreviousMatchedRect(), matchRes ? Color.FromArgb(0, 255, 0) : Color.Red); // 画最佳匹配框（满足阈值为绿，否则为红）
						}
						else {
							m_eye.DrawRectangle(pattern.GetSearchRect(), matchRes ? Color.FromArgb(0, 255, 0) : Color.Red); // 画寻找范围框（满足阈值为绿，否则为红）
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
		internal static int WaitForMultiple(Pattern[] patterns, TimeSpan? timeout) {
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
						m_eye.BeginDebugDraw();
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
								m_eye.DrawRectangle(i.GetPreviousMatchedRect(), Color.FromArgb(0, 255, 0)); // 画最佳匹配框（绿）
							}
							else {
								m_eye.DrawRectangle(i.GetSearchRect(), Color.FromArgb(0, 255, 0)); // 画寻找范围框（绿）
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
		internal static bool KeepClickingUntil(
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

			if (m_hand == null) {
				if (Settings.wndHandler.UseSendInput) {
					m_hand = new HandOnInput();
				}
				else {
					m_hand = new HandOnWnd();
				}
			}

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
		internal static bool KeepClickingUntilNo(
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

			if (m_hand == null) {
				if (Settings.wndHandler.UseSendInput) {
					m_hand = new HandOnInput();
				}
				else {
					m_hand = new HandOnWnd();
				}
			}

			do {
				if (timeout > TimeSpan.Zero && watch.Elapsed >= timeout) // 应用超时
					return false;
				m_hand.ClickAt(clkPt); // 点击
				r_ct.ThrowIfCancellationRequested();
			} while (WaitFor(pattern, clkInterval));

			return true;
		}

		internal static void ClickAt(Point target) {
			ExsureAbleToRun();

			if (m_hand == null) {
				if (Settings.wndHandler.UseSendInput) {
					m_hand = new HandOnInput();
				}
				else {
					m_hand = new HandOnWnd();
				}
			}

			m_hand.ClickAt(target);
		}

		private static void ExsureAbleToRun() {
#if DEBUG
			if (m_state == State.Idle)
				throw new WndHandlerNotRunningException();
#endif
		}
	}
}
