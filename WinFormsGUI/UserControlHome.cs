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
			userControlList.SetSelectedChangedTo = ChangeSettingCallback;

			// 注册以在工作时锁定控件。
			Program.GuiLock += OnWorkLockAndUnlock;
		}

		/// <summary>
		/// 监听工作状态改变锁定控件的事件
		/// </summary>
		private void OnWorkLockAndUnlock(object sender, bool isLock) {
			if (isLock) {
				panel_Settings.Enabled = false;
				userControlList.Enabled = false;
				button_Main.Text = Strings.Main.Btn_Main_Start;
			}
			else {
				userControlList.Enabled = true;
				panel_Settings.Enabled = true;
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
			case TaskEnumWrap.LegacyCha:
				ctrl = new UserControlSetForLegacyCha();
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
				Program.GuiLock.Invoke(null, true); // 锁定GUI
				Program.helper.SetTaskList([.. userControlList.GetEnabledList()]); // 设置所选的任务
				ClearLog(); // 清空进度提示。
				if (!Program.helper.Start()) { // 启动失败
					Log(Strings.LogEvent.Work_CanNotStartWork); // 提示。
					Program.GuiLock.Invoke(null, false); // 解锁GUI
					return;
				}
				timer_Main.Enabled = true; // 启动Timer获取回执信息。
			}
			else { // 要求停止
				Program.helper.AskForStop();
			}
		}

		/// <summary>
		/// Timer读取回执信息。
		/// </summary>
		private void Timer_Main_Tick(object sender, EventArgs e) {
			bool setted = false;
			ReturnMessage m;
			while ((m = Program.helper.GetMessage()) != ReturnMessage.None) {
				if (!setted) {
					userControlLogger.LogProcessStatusChange(true);
					setted = true;
				}
				switch (m) {
				case ReturnMessage.CMD_EmptyLine:
					//Log();
					break;
				case ReturnMessage.CMD_Stopped:
					Program.GuiLock.Invoke(null, false);
					timer_Main.Enabled = false;
					break;
				case ReturnMessage.CMD_BtnToStop:
					button_Main.Text = Strings.Main.Btn_Main_Stop;
					button_Main.Enabled = true;
					m_btnMainIsStart = false;
					break;
				case ReturnMessage.CMD_BtnToStart:
					button_Main.Text = Strings.Main.Btn_Main_Start;
					button_Main.Enabled = true;
					m_btnMainIsStart = true;
					break;

				case ReturnMessage.LOG_StartError_Running:
					Log(Strings.LogEvent.Work_AlreadyRunning);
					break;
				case ReturnMessage.LOG_Stopping:
					Log(Strings.LogEvent.Work_Stopping);
					break;
				case ReturnMessage.LOG_Stopped:
					Log(Strings.LogEvent.Work_Stopped);
					break;
				case ReturnMessage.LOG_Complete:
					Log(Strings.LogEvent.Work_Complete);
					MyPopNotification(
						Strings.LogEvent.Work_Complete,
						Strings.LogEvent.Work_Complete_Describtion,
						ToolTipIcon.Info
					);
					break;

				case ReturnMessage.LOG_WorkError_ExceptionInternalError:
					//Log();
					Log(Strings.LogEvent.Work_Exception);
					MyPopNotification(
						Strings.LogEvent.Work_Error,
						Strings.LogEvent.Work_Exception,
						ToolTipIcon.Error
					);
					break;

				case ReturnMessage.LOG_TaskStop:
					Log(Strings.LogEvent.Task_Stop);
					break;
				case ReturnMessage.LOG_TaskComplete:
					Log(Strings.LogEvent.Task_Complete);
					break;
				case ReturnMessage.LOG_TaskError_Exception:
					Log(Strings.LogEvent.Task_Exception);
					MyPopNotification(
						Strings.LogEvent.Work_Error,
						Strings.LogEvent.Task_Exception,
						ToolTipIcon.Error
					);
					break;
				case ReturnMessage.LOG_TaskError:
					m = Program.helper.GetMessage();
					string text;
					switch (m) {
					case ReturnMessage.STR_Task_Challenge_NoNew:
						text = Strings.LogStr.Task_Challenge_NoNew;
						break;
					case ReturnMessage.STR_Task_Challenge_NoLast:
						text = Strings.LogStr.Task_Challenge_NoLast;
						break;
					case ReturnMessage.STR_Task_Challenge_NoEnter:
						text = Strings.LogStr.Task_Challenge_NoEnter;
						break;
					case ReturnMessage.STR_Task_Challenge_NoStart:
						text = Strings.LogStr.Task_Challenge_NoStart;
						break;
					case ReturnMessage.STR_Task_Challenge_TimeOut:
						text = Strings.LogStr.Task_Challenge_TimeOut;
						break;
					case ReturnMessage.STR_Task_Challenge_NoEnd:
						text = Strings.LogStr.Task_Challenge_NoEnd;
						break;
					case ReturnMessage.STR_Task_Challenge_NoOver:
						text = Strings.LogStr.Task_Challenge_NoOver;
						break;
					case ReturnMessage.STR_Task_Challenge_AddNotSup:
						text = Strings.LogStr.Task_Challenge_AddNotSup;
						break;
					case ReturnMessage.STR_Task_Challenge_IgnoreAddFailed:
						text = Strings.LogStr.Task_Challenge_IgnoreAddFailed;
						break;
					case ReturnMessage.STR_Task_Challenge_OpenAddFailed:
						text = Strings.LogStr.Task_Challenge_OpenAddFailed;
						break;
					case ReturnMessage.STR_Task_FailedToLoadTemplateFile:
						text = Strings.LogStr.Task_FailedToLoadTemplateFile;
						break;
					case ReturnMessage.STR_Task_Error_NoWnd:
						text = Strings.LogStr.Task_CanNotFindWnd;
						break;
					case ReturnMessage.STR_Task_Error_FailedCapture:
						text = Strings.LogStr.Task_CanNotCapture;
						break;
					default:
						text = string.Format(Strings.LogStr.UNKNOWN, m.ToString());
						break;
					}
					Log(Strings.LogEvent.Task_Error + ": " + text, Color.DarkRed);
					MyPopNotification(
						Strings.LogEvent.Task_Error,
						text,
						ToolTipIcon.Info
					);
					break;

				case ReturnMessage.LOG_Challenge_Start:
					Log(Strings.LogEvent.Challenge_Start);
					break;
				case ReturnMessage.LOG_Challenge_BeginNum: // 挑战赛开始（下跟次数！）
					Log(string.Format(Strings.LogEvent.Challenge_BeginNum, Program.helper.GetCode()));
					break;
				case ReturnMessage.LOG_Challenge_Over:
					Log(Strings.LogEvent.Challenge_Over);
					break;
				case ReturnMessage.LOG_Challenge_Exit:
					Log(Strings.LogEvent.Challenge_Exit);
					break;
				case ReturnMessage.LOG_Challenge_BeginAdd: // 奖励挑战赛开始（下跟次数！）
					Log(string.Format(Strings.LogEvent.Challenge_BeginAdd, Program.helper.GetCode()));
					break;
				case ReturnMessage.LOG_Challenge_IgnoredAdd:
					Log(Strings.LogEvent.Challenge_IgnoredAdd);
					break;
				case ReturnMessage.LOG_Challenge_NotFindAdd:
					Log(Strings.LogEvent.Challenge_NotFindAdd);
					break;
				case ReturnMessage.LOG_Challenge_FindAdd:
					Log(Strings.LogEvent.Challenge_FindAdd);
					break;
				case ReturnMessage.LOG_Challenge_OpenedAdd:
					Log(Strings.LogEvent.Challenge_OpenedAdd);
					break;
				default:
					Log(string.Format(Strings.LogEvent.UNKNOWN, m.ToString()));
					break;

				}
			}
			if (setted)
				userControlLogger.LogProcessStatusChange(false);
			return;
		}
	}
}
