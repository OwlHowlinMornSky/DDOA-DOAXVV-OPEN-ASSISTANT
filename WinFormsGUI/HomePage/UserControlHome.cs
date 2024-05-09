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
using Wrapper;

namespace WinFormsGUI {
	/// <summary>
	/// 主页。
	/// </summary>
	public partial class UserControlHome : UserControl {

		/// <summary>
		/// 当前主按钮状态
		/// </summary>
		private bool m_btnMainIsStart = true;
		/// <summary>
		/// 发托盘消息的回调，应由根窗口设置。
		/// </summary>
		public Action<string, string, ToolTipIcon> MyPopNotification = (x, y, z) => {};
		/// <summary>
		/// 当前展示的设置对应任务的id。
		/// </summary>
		private uint m_setIdNow = (uint)TaskEnumWrap.None;

		public UserControlHome() {
			InitializeComponent();
			// 设置左侧列表“设置小按钮”选择项改变的回调。
			userControlList.SetSelectedChangedTo += ChangeSettingCallback;
			// 注册以在工作时锁定控件。
			WorkStatusLocker.lockAction += OnWorkLockAndUnlock;
			if (WorkStatusLocker.Locked)
				OnWorkLockAndUnlock(true);
		}

		~UserControlHome() {
			WorkStatusLocker.lockAction -= OnWorkLockAndUnlock;
			userControlList.SetSelectedChangedTo -= ChangeSettingCallback;
		}

		/// <summary>
		/// 监听工作状态改变锁定控件的事件
		/// </summary>
		private void OnWorkLockAndUnlock(bool isLock) {
			if (isLock) {
				panel_Settings.Enabled = false;
				button_Main.Enabled = false;
			}
			else {
				panel_Settings.Enabled = true;
				button_Main.Enabled = true;
				button_Main.Text = Strings.Main.Btn_Main_Start;
			}
		}

		/// <summary>
		/// 修改展示的设置页
		/// </summary>
		/// <param name="id">内部任务id</param>
		private void ChangeSetting(uint id) {
			if (m_setIdNow == id) // 页面不改变
				return;
			panel_Settings.Controls.Clear(); // 清除当前页面
			Control ctrl;
			switch ((TaskEnumWrap)id) { // 选择页面
			default:
			case TaskEnumWrap.None:
				id = (uint)TaskEnumWrap.None;
				ctrl = new UserControlSetForDefault();
				break;
			//case TaskEnumWrap.StartUp:
			//	break;
			case TaskEnumWrap.Daily:
				ctrl = new UserControlSetForDaily();
				break;
			case TaskEnumWrap.Challenge:
				ctrl = new UserControlSetForChallenge();
				break;
			}
			ctrl.Dock = DockStyle.Fill;
			// 添加页面
			panel_Settings.Controls.Add(ctrl);
			m_setIdNow = id;
		}

		/// <summary>
		/// 改变设置页面的回调
		/// </summary>
		/// <param name="data">项数据</param>
		private void ChangeSettingCallback(uint data) {
			if (InvokeRequired) {
				var r = BeginInvoke(new Action(() => {
					ChangeSetting(data);
				}));
				EndInvoke(r);
			}
			else {
				ChangeSetting(data);
			}
		}

		/// <summary>
		/// 【转接】清空日志
		/// </summary>
		public void ClearLog() => userControlLogger.Clear();
		/// <summary>
		/// 【转接】添加日志
		/// </summary>
		/// <param name="message">文本内容</param>
		/// <param name="color">颜色</param>
		public void Log(string message, Color color) => userControlLogger.Log(message, color);
		/// <summary>
		/// 【转接】添加日志（默认颜色）
		/// </summary>
		/// <param name="message">文本内容</param>
		public void Log(string message) => userControlLogger.Log(message);

		/// <summary>
		/// 控件加载时
		/// </summary>
		private void UserControlHome_Load(object sender, EventArgs e) {
			SetListMiddle();
			button_Main.Text = Strings.Main.Btn_Main_Start;
		}

		/// <summary>
		/// 【需手动调用】尝试关闭时
		/// </summary>
		public void OnClosing() {
			userControlList.OnClosing();
		}

		/// <summary>
		/// 把左侧第一列内容在其panel中居中
		/// </summary>
		private void SetListMiddle() {
			userControlList.Left = (panel_leftCtrl.Width - userControlList.Width) / 2;
			button_Main.Left = (panel_leftCtrl.Width - button_Main.Width) / 2;
		}

		/// <summary>
		/// 左侧panel大小改变后
		/// </summary>
		private void Panel_LeftCtrl_SizeChanged(object sender, EventArgs e) {
			SetListMiddle(); // 重新居中
		}

		/// <summary>
		/// 点击主按钮
		/// </summary>
		private void Button_Main_Click(object sender, EventArgs e) {
			button_Main.Enabled = false;
			if (m_btnMainIsStart) { // Link Start！
				WorkStatusLocker.WorkLock(); // 锁定GUI
				uint[] list = [.. userControlList.GetEnabledList()];
				ClearLog(); // 清空进度提示。
				if (list.Length == 0) {
					Log(Strings.Main.TaskListNotSelected);
					WorkStatusLocker.WorkUnlock(); // 解锁GUI
					return;
				}
				Program.helper.SetTaskList(list); // 设置所选的任务
				if (!Program.helper.Start()) { // 启动失败
					Log(Strings.GuiLog.WorkCanNotStartWork); // 提示。
					WorkStatusLocker.WorkUnlock(); // 解锁GUI
					return;
				}
				timer_Main.Enabled = true; // 启动Timer获取回执信息。
			}
			else { // 要求停止
				Program.helper.AskForStop();
			}
		}

		private string GetLogStringFromResx(string name) {
			string res = Strings.GuiLog.ResourceManager.GetString(name);
			if (res == null) {
				res = name;
				/*MessageBox.Show(
					string.Format(Strings.Main.NoSuchLogString, name),
					Text,
					MessageBoxButtons.OK,
					MessageBoxIcon.Error
				);*/
			}
			return res;
		}

		private bool GetLogColorFromResx(string name, out Color clr) {
			string res = Strings.GuiLogClr.ResourceManager.GetString(name);
			if (res == null) {
				clr = Color.White;
				return false;
			}
			clr = Color.FromArgb(Convert.ToInt32(res, 16));
			return true;
		}

		private string GetTaskNameFromResx(int i) {
			string res = Strings.Main.ResourceManager.GetString("Task" + i.ToString("000"));
			if (res == null) {
				res = $"#{i}";
				/*MessageBox.Show(
					string.Format(Strings.Main.NoSuchTaskStr, res),
					Text,
					MessageBoxButtons.OK,
					MessageBoxIcon.Error
				);*/
			}
			return res;
		}

		/// <summary>
		/// Timer读取回执信息。
		/// </summary>
		private void Timer_Main_Tick(object sender, EventArgs e) {
			bool setted = false;
			ReturnCmd cmd;
			while ((cmd = Program.helper.GetCommand()) != ReturnCmd.None) {
				if (!setted) {
					userControlLogger.LogProcessStatusChange(true);
					setted = true;
				}

				switch (cmd) {
				case ReturnCmd.CMD_EmptyLine:
					//Log();
					break;
				case ReturnCmd.CMD_Stopped:
					WorkStatusLocker.WorkUnlock(); // 解锁GUI
					timer_Main.Enabled = false;
					break;
				case ReturnCmd.CMD_BtnToStop:
					button_Main.Text = Strings.Main.Btn_Main_Stop;
					button_Main.Enabled = true;
					m_btnMainIsStart = false;
					break;
				case ReturnCmd.CMD_BtnToStart:
					button_Main.Text = Strings.Main.Btn_Main_Start;
					button_Main.Enabled = true;
					m_btnMainIsStart = true;
					break;
				case ReturnCmd.LOG_Format: {
					var msg = Program.helper.GetMessage();
					switch (msg) {
					case ReturnMessage.WorkComplete:
						Log(Strings.GuiLog.WorkComplete);
						MyPopNotification(
							Strings.GuiLog.WorkComplete,
							Strings.GuiLog.WorkCompleteDescribtion,
							ToolTipIcon.Info
						);
						break;
					case ReturnMessage.WorkErrorInternalException:
						Log(Strings.GuiLog.WorkErrorInternalException);
						MyPopNotification(
							Strings.GuiLog.WorkError,
							Strings.GuiLog.WorkErrorInternalException,
							ToolTipIcon.Error
						);
						break;
					case ReturnMessage.TaskException:
						Log(Strings.GuiLog.TaskException);
						MyPopNotification(
							Strings.GuiLog.WorkError,
							Strings.GuiLog.TaskException,
							ToolTipIcon.Error
						);
						break;
					default:
						if (GetLogColorFromResx(msg.ToString(), out var color))
							Log(GetLogStringFromResx(msg.ToString()), color);
						else
							Log(GetLogStringFromResx(msg.ToString()));
						break;
					}
					break;
				}
				case ReturnCmd.LOG_Format_S: {
					var msg = Program.helper.GetMessage();
					var reason = Program.helper.GetMessage();
					string t;
					switch (msg) {
					case ReturnMessage.TaskErr_Format:
						t = GetLogStringFromResx(reason.ToString());
						Log(string.Format(Strings.GuiLog.TaskErr_Format, t), Color.DarkRed);
						MyPopNotification(Strings.GuiLog.TaskErr, t, ToolTipIcon.Error);
						break;
					default:
						t =
							string.Format(
								GetLogStringFromResx(msg.ToString()),
								GetLogStringFromResx(reason.ToString())
							);
						if (GetLogColorFromResx(msg.ToString(), out var color))
							Log(t, color);
						else
							Log(t);
						break;
					}
					break;
				}
				case ReturnCmd.LOG_Format_I: {
					var msg = Program.helper.GetMessage();
					var i = Program.helper.GetValueI();
					string t;
					switch (msg) {
					case ReturnMessage.TaskErr_Task: {
						t = GetTaskNameFromResx(i);
						Log(string.Format(Strings.GuiLog.TaskErr_Task, t), Color.DarkRed);
						MyPopNotification(Strings.GuiLog.TaskErr, t, ToolTipIcon.Error);
						break;
					}
					default: {
						t = string.Format(
							GetLogStringFromResx(msg.ToString()),
							i
						);
						if (GetLogColorFromResx(msg.ToString(), out var color))
							Log(t, color);
						else
							Log(t);
						break;
					}
					}
					break;
				}
				case ReturnCmd.LOG_Format_SI: {
					var msg = Program.helper.GetMessage();
					var s = Program.helper.GetMessage();
					var i = Program.helper.GetValueI();
					string t =
						string.Format(
							GetLogStringFromResx(msg.ToString()),
							GetLogStringFromResx(s.ToString()),
							i
						);
					if (GetLogColorFromResx(msg.ToString(), out var color))
						Log(t, color);
					else
						Log(t);
					break;
				}
				case ReturnCmd.LOG_Format_II: {
					var msg = Program.helper.GetMessage();
					var i0 = Program.helper.GetValueI();
					var i1 = Program.helper.GetValueI();
					string t =
						string.Format(
							GetLogStringFromResx(msg.ToString()),
							i0,
							i1
						);
					if (GetLogColorFromResx(msg.ToString(), out var color))
						Log(t, color);
					else
						Log(t);
					break;
				}
				default:
					break;
				}
			}
			if (setted)
				userControlLogger.LogProcessStatusChange(false);
			return;
		}

	}
}
