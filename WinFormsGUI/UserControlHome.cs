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
	public partial class UserControlHome : UserControl {

		private bool m_btnMainIsStart = true;
		public Action<string, string, ToolTipIcon> MyPopNotification = (x, y, z) => {};

		public UserControlHome() {
			InitializeComponent();

			userControlList.SetSelectedChangedTo = ChangeSettingCallback;

			Program.GuiLock += OnWorkLockAndUnlock;
		}

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

		private void ChangeSetting(uint id) {
			panel_Settings.Controls.Clear();
			switch ((TaskEnumWrap)id) {
			default:
			case TaskEnumWrap.None:
				panel_Settings.Controls.Add(new UserControlSetForDefault() {
					Dock = DockStyle.Fill,
				});
				break;
			case TaskEnumWrap.LegacyCha:
				panel_Settings.Controls.Add(new UserControlSetForLegacyCha() {
					Dock = DockStyle.Fill,
				});
				break;
			}

		}

		private void ChangeSettingCallback(ListItemUserData data) {
			if (InvokeRequired) {
				var r = BeginInvoke(new Action(() => {
					ChangeSetting(data.coreTaskEnum);
				}));
				EndInvoke(r);
			}
			else {
				ChangeSetting(data.coreTaskEnum);
			}
		}

		public void ClearLog() => userControlLogger.Clear();
		public void Log(string message, Color color) => userControlLogger.Log(message, color);
		public void Log(string message) => userControlLogger.Log(message);

		private void UserControlHome_Load(object sender, EventArgs e) {
			SetListMiddle();
		}

		public void OnClosing() {
			userControlList.OnClosing();
		}

		private void SetListMiddle() {
			userControlList.Left = (panel_leftCtrl.Width - userControlList.Width) / 2;
			button_Main.Left = (panel_leftCtrl.Width - button_Main.Width) / 2;
		}

		private void Panel_LeftCtrl_SizeChanged(object sender, EventArgs e) {
			SetListMiddle();
		}

		private void Button_Main_Click(object sender, EventArgs e) {
			button_Main.Enabled = false;
			if (m_btnMainIsStart) {
				
				Program.GuiLock.Invoke(null, true);

				Program.helper.SetTaskList([.. userControlList.GetEnabledList()]);

				ClearLog();
				if (!Program.helper.Start()) {
					Log(Strings.LogEvent.Work_CanNotStartWork);
					Program.GuiLock.Invoke(null, false);
					return;
				}
				timer_Main.Enabled = true;
			}
			else {
				Program.helper.AskForStop();
			}
		}

		private void Timer_Main_Tick(object sender, EventArgs e) {
			userControlLogger.LogProcessStatusChange(true);
			ReturnMessage m;
			while ((m = Program.helper.GetMessage()) != ReturnMessage.None) {
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
			userControlLogger.LogProcessStatusChange(false);
			return;
		}
	}
}
