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
	public partial class FormMain : Form {

		#region ==========Members==========

		private readonly HelperWrapper m_helper = new();
		private bool m_btnMainIsStart = true;
		private Size m_label_transp_value_size = new();

		#endregion

		public FormMain() {
			InitializeComponent();
		}

		#region ==========Common===========

		public void Log(string msg) {
			bool scroll = listBox_Log.TopIndex == listBox_Log.Items.Count - (int)(listBox_Log.Height / listBox_Log.ItemHeight);
			listBox_Log.Items.Add(DateTime.Now.ToString("MM-dd HH:mm:ss") + '　' + msg);
			if (scroll)
				listBox_Log.TopIndex = listBox_Log.Items.Count - (int)(listBox_Log.Height / listBox_Log.ItemHeight);
		}

		public void Log() {
			bool scroll = listBox_Log.TopIndex == listBox_Log.Items.Count - (int)(listBox_Log.Height / listBox_Log.ItemHeight);
			listBox_Log.Items.Add("");
			if (scroll)
				listBox_Log.TopIndex = listBox_Log.Items.Count - (int)(listBox_Log.Height / listBox_Log.ItemHeight);
		}

		private void InitLoadSettings_Home() {
			radioBtn_GameNew.Checked = Settings.Core.Default.Cha_PlayNew;
			radioBtn_CtrlInput.Checked = Settings.Core.Default.CtrlSendInput;

			switch (Settings.Core.Default.Cha_Award) {
			case 1:
				radioBtn_AwardPlay.Checked = true;
				break;
			case 2:
				radioBtn_AwardIgnore.Checked = true;
				break;
			default:
				radioBtn_AwardNo.Checked = true;
				break;
			}
		}

		private void InitLoadSettings_Settings() {
#if DEBUG
			Settings.Core.Default.ShowCapture = true;
#endif
			chkBox_SetShow.Checked = Settings.Core.Default.ShowCapture;
			chkBox_SetHideToTray.Checked = Settings.GUI.Default.HideToTray;
			chkBox_SetNotify.Checked = Settings.GUI.Default.UseNotify;

			if (Settings.Core.Default.KeepAwake) {
				chkBox_SetAwake.Checked = true;
				chkBox_SetScreenOn.Enabled = true;
				chkBox_SetScreenOn.Checked = Settings.Core.Default.KeepScreenOn;
			}
			else {
				chkBox_SetAwake.Checked = false;
				chkBox_SetScreenOn.Enabled = false;
				chkBox_SetScreenOn.Checked = false;
			}
			chkBox_SetDisableClose.Checked = Settings.GUI.Default.DisableClose;

			tkBar_Trans.Value = Settings.GUI.Default.Transparent;
			m_label_transp_value_size = label_TransValue.Size;
			label_TransValue.Text = tkBar_Trans.Value.ToString() + "%";
		}

		private void InitLoadSettings() {
			InitLoadSettings_Home();
			InitLoadSettings_Settings();
			if (Settings.GUI.Default.LastPosition.X != -1 && Settings.GUI.Default.LastPosition.Y != -1)
				Location = Settings.GUI.Default.LastPosition;
		}

		private void DropSaveSettings() {
			Settings.GUI.Default.LastPosition = Location;
			Settings.GUI.Default.Save();
			Settings.Core.Default.Save();
		}

		private void WorkLock() {
			gpBox_GameSet.Enabled = false;
			gpBox_CtrlSet.Enabled = false;
			gpBox_AwardSet.Enabled = false;
		}

		private void WorkUnlock() {
			gpBox_GameSet.Enabled = true;
			gpBox_CtrlSet.Enabled = true;
			gpBox_AwardSet.Enabled = true;
			btn_Main.Text = Strings.Main.Btn_Main_Start;
		}

		#endregion

		#region ---------MainForm----------

		public void FormMain_Load(object sender, EventArgs e) {
			notifyIcon_Main.Text = Text;
			WorkUnlock();
			InitLoadSettings();
		}

		private void FormMain_Deactivate(object sender, EventArgs e) {
			if (WindowState == FormWindowState.Minimized && Settings.GUI.Default.HideToTray) {
				Hide();
			}
		}

		private void FormMain_FormClosing(object sender, FormClosingEventArgs e) {
			m_helper.AskForStop();
			DropSaveSettings();
			while (m_helper.IsRunning()) {
				Thread.Sleep(30);
			}
		}

		private void FormMain_FormClosed(object sender, FormClosedEventArgs e) {
			m_helper.Drop();
		}

		#endregion

		#region ------------Home------------

		private void Btn_Main_Click(object sender, EventArgs e) {
			btn_Main.Enabled = false;
			if (m_btnMainIsStart) { 
				WorkLock();
				listBox_Log.Items.Clear();
				if (!m_helper.Start()) {
					Log(Strings.LogEvent.Work_CanNotStartWork);
					WorkUnlock();
					return;
				}
				timer_Main.Enabled = true;
			}
			else {
				m_helper.AskForStop();
			}
		}

		private void RadioBtn_Game_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetChallengeForNewOrLast(radioBtn_GameNew.Checked);
			Settings.Core.Default.Cha_PlayNew = radioBtn_GameNew.Checked;
		}

		private void RadioBtn_Ctrl_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetMouseSendInputOrSendMessage(radioBtn_CtrlInput.Checked);
			Settings.Core.Default.CtrlSendInput = radioBtn_CtrlInput.Checked;
		}

		private void RadioBtn_Award_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetChallengeCheckAwardOrNot(!radioBtn_AwardNo.Checked);
			m_helper.SetChallengePlayAwardOrNot(radioBtn_AwardPlay.Checked);
			if (radioBtn_AwardNo.Checked) {
				Settings.Core.Default.Cha_Award = 0;
			}
			else if (radioBtn_AwardPlay.Checked) {
				Settings.Core.Default.Cha_Award = 1;
			}
			else {
				Settings.Core.Default.Cha_Award = 2;
			}
		}

		#endregion

		#region ----------Settings----------

		private void ChkBox_SetShow_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetShowCaptureOrNot(chkBox_SetShow.Checked);
			Settings.Core.Default.ShowCapture = chkBox_SetShow.Checked;
		}

		private void ChkBox_SetHideToTray_CheckedChanged(object sender, EventArgs e) {
			Settings.GUI.Default.HideToTray = chkBox_SetHideToTray.Checked;
		}

		private void ChkBox_SetNotify_CheckedChanged(object sender, EventArgs e) {
			Settings.GUI.Default.UseNotify = chkBox_SetNotify.Checked;
		}

		private void ChkBox_SetAwake_CheckedChanged(object sender, EventArgs e) {
			if (chkBox_SetAwake.Checked) {
				Settings.Core.Default.KeepAwake = true;
				chkBox_SetScreenOn.Enabled = true;
				m_helper.SetKeepAwakeOrNot(true);
			}
			else {
				Settings.Core.Default.KeepAwake = false;
				chkBox_SetScreenOn.Checked = false;
				chkBox_SetScreenOn.Enabled = false;
				m_helper.SetKeepAwakeOrNot(false);
			}
		}

		private void ChkBox_SetScreenOn_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetKeepScreenOnOrNot(chkBox_SetScreenOn.Checked);
			Settings.Core.Default.KeepScreenOn = chkBox_SetScreenOn.Checked;
		}

		private void ChkBox_SetDisableClose_CheckedChanged(object sender, EventArgs e) {
			SystemThings.SetCloseEnabled(Handle, !chkBox_SetDisableClose.Checked);
			Settings.GUI.Default.DisableClose = chkBox_SetDisableClose.Checked;
		}

		private void TkBar_Trans_ValueChanged(object sender, EventArgs e) {
			Opacity = 1.0 - tkBar_Trans.Value / 100.0;
			Settings.GUI.Default.Transparent = tkBar_Trans.Value;
			label_TransValue.Text = tkBar_Trans.Value.ToString() + "%";
		}

		private void Label_TransValue_SizeChanged(object sender, EventArgs e) {
			var newSize = label_TransValue.Size;
			var loc = label_TransValue.Location;
			loc.X += m_label_transp_value_size.Width - newSize.Width;
			label_TransValue.Location = loc;
			m_label_transp_value_size = newSize;
		}

		#endregion

		#region -----------Others-----------

		private void NotifyIcon_Main_MouseClick(object sender, MouseEventArgs e) {
			switch (e.Button) {
			case MouseButtons.Left:
				Show();
				WindowState = FormWindowState.Normal;
				Activate();
				break;
			case MouseButtons.Right:
				notifyIcon_Main.ContextMenuStrip?.Show();
				break;
			}
		}

		private void CtxtMenu_NotifyRExit_Click(object sender, EventArgs e) {
			Close();
		}

		private void Timer_Main_Tick(object sender, EventArgs e) {
			ReturnMessage m;
			while ((m = m_helper.GetMessage()) != ReturnMessage.None)
				switch (m) {
				case ReturnMessage.CMD_EmptyLine:
					Log();
					break;
				case ReturnMessage.CMD_Stopped:
					Log(Strings.LogEvent.Work_Stopped);
					WorkUnlock();
					timer_Main.Enabled = false;
					break;
				case ReturnMessage.CMD_BtnToStop:
					btn_Main.Text = Strings.Main.Btn_Main_Stop;
					btn_Main.Enabled = true;
					m_btnMainIsStart = false;
					break;
				case ReturnMessage.CMD_BtnToStart:
					btn_Main.Text = Strings.Main.Btn_Main_Start;
					btn_Main.Enabled = true;
					m_btnMainIsStart = true;
					break;

				case ReturnMessage.LOG_StartError_Running:
					Log(Strings.LogEvent.Work_AlreadyRunning);
					break;
				case ReturnMessage.LOG_Stopping:
					Log(Strings.LogEvent.Work_Stopping);
					break;
				case ReturnMessage.LOG_WorkError_NoWnd:
					Log(Strings.LogEvent.Work_CanNotFindWnd);
					break;
				case ReturnMessage.LOG_WorkError_FailedCapture:
					Log(Strings.LogEvent.Work_CanNotCapture);
					break;
				case ReturnMessage.LOG_WorkError_Exception:
					Log();
					Log(Strings.LogEvent.Work_Exception);
					if (Settings.GUI.Default.UseNotify)
						notifyIcon_Main.ShowBalloonTip(
							Settings.Param.Default.NotifyTime,
							Strings.LogEvent.Work_Error,
							Strings.LogEvent.Work_Exception,
							ToolTipIcon.Error
						);
					break;

				case ReturnMessage.LOG_TaskStop:
					Log(Strings.LogEvent.Task_Stop);
					break;
				case ReturnMessage.LOG_TaskError_Exception:
					Log(Strings.LogEvent.Task_Exception);
					if (Settings.GUI.Default.UseNotify)
						notifyIcon_Main.ShowBalloonTip(
							Settings.Param.Default.NotifyTime,
							Strings.LogEvent.Work_Error,
							Strings.LogEvent.Task_Exception,
							ToolTipIcon.Error
						);
					break;
				case ReturnMessage.LOG_TaskError:
					Log();
					m = m_helper.GetMessage();
					string text = "null";
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
					case ReturnMessage.STR_Task_Challenge_LowFP:
						text = Strings.LogStr.Task_Challenge_LowFP;
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
					default:
						text = string.Format(Strings.LogStr.UNKNOWN, m.ToString());
						break;
					}
					Log(Strings.LogEvent.Task_Error + ": " + text);
					if (Settings.GUI.Default.UseNotify)
						notifyIcon_Main.ShowBalloonTip(
							Settings.Param.Default.NotifyTime,
							Strings.LogEvent.Task_Error,
							text,
							ToolTipIcon.Info
						);
					break;
				case ReturnMessage.LOG_TaskOver:
					Log(Strings.LogEvent.TaskOver);
					if (Settings.GUI.Default.UseNotify)
						notifyIcon_Main.ShowBalloonTip(
							Settings.Param.Default.NotifyTime,
							Strings.LogEvent.TaskOver,
							Strings.LogEvent.TaskOver,
							ToolTipIcon.Info
						);
					break;

				case ReturnMessage.LOG_Challenge_Start:
					Log(Strings.LogEvent.Challenge_Start);
					break;
				case ReturnMessage.LOG_Challenge_BeginNum: // 挑战赛开始（下跟次数！）
					Log(string.Format(Strings.LogEvent.Challenge_BeginNum, m_helper.GetCode()));
					break;
				case ReturnMessage.LOG_Challenge_EnterLast:
					Log(Strings.LogEvent.Challenge_EnterLast);
					break;
				case ReturnMessage.LOG_Challenge_EnterNew:
					Log(Strings.LogEvent.Challenge_EnterNew);
					break;
				case ReturnMessage.LOG_Challenge_Play:
					Log(Strings.LogEvent.Challenge_Play);
					break;
				case ReturnMessage.LOG_Challenge_WaitForEnd:
					Log(Strings.LogEvent.Challenge_WaitForEnd);
					break;
				case ReturnMessage.LOG_Challenge_End:
					Log(Strings.LogEvent.Challenge_End);
					break;
				case ReturnMessage.LOG_Challenge_Quiting:
					Log(Strings.LogEvent.Challenge_Quiting);
					break;
				case ReturnMessage.LOG_Challenge_Over:
					Log(Strings.LogEvent.Challenge_Over);
					break;
				case ReturnMessage.LOG_Challenge_Exit:
					Log(Strings.LogEvent.Challenge_Exit);
					break;
				case ReturnMessage.LOG_Challenge_EnterAdd:
					Log(Strings.LogEvent.Challenge_EnterAdd);
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
			return;
		}

		#endregion


	}
}
