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

		#region ==========Common===========

		public FormMain() {
			InitializeComponent();
		}

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

		#endregion

		#region ==========Events===========

		#region ---------MainForm----------

		public void FormMain_Load(object sender, EventArgs e) {
			notifyIcon_main.Text = Text;
			btn_Main.Text = Strings.Main.Main_Btn_Start;

			

#if DEBUG
			Settings.Main.Default.ShowCV = true;
#endif

			radioBtn_GameNew.Checked = Settings.Main.Default.Game_ForNew;
			radioBtn_CtrlInput.Checked = Settings.Main.Default.Ctrl_ForMouse;

			chkBox_SetShow.Checked = Settings.Main.Default.ShowCV;
			chkBox_SetHideToTray.Checked = Settings.Main.Default.HideToIcon;
			chkBox_SetNotify.Checked = Settings.Main.Default.UseNotify;
			if (Settings.Main.Default.PreventSleep) {
				chkBox_SetAwake.Checked = true;
				chkBox_SetScreenOn.Enabled = true;
				chkBox_SetScreenOn.Checked = Settings.Main.Default.KeepDisplay;
			}
			else {
				chkBox_SetAwake.Checked = false;
				chkBox_SetScreenOn.Enabled = false;
				chkBox_SetScreenOn.Checked = false;
			}

			chkBox_SetDisableClose.Checked = Settings.Main.Default.DisableClose;

			tkBar_Trans.Value = Settings.Main.Default.Transparant;
			m_label_transp_value_size = label_TransValue.Size;
			label_TransValue.Text = tkBar_Trans.Value.ToString() + "%";

			switch (Settings.Main.Default.Cha_Add) {
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

			if (Settings.Main.Default.LastPosition.X != -1 && Settings.Main.Default.LastPosition.Y != -1)
				Location = Settings.Main.Default.LastPosition;
			//if (Settings.Main.Default.LastClientSize.Width != 0 && Settings.Main.Default.LastClientSize.Height != 0)
			//	ClientSize = Settings.Main.Default.LastClientSize;
		}

		private void FormMain_Deactivate(object sender, EventArgs e) {
			if (WindowState == FormWindowState.Minimized &&
				Settings.Main.Default.HideToIcon) {
				Hide();
			}
		}

		private void FormMain_FormClosing(object sender, FormClosingEventArgs e) {
			m_helper.AskForStop();

			Settings.Main.Default.LastPosition = Location;
			//Settings.Main.Default.LastClientSize = ClientSize;

			Settings.Main.Default.Save();

			while (m_helper.IsRunning()) {
				Thread.Sleep(30);
			}
		}

		private void FormMain_FormClosed(object sender, FormClosedEventArgs e) {
			m_helper.Drop();
		}

		#endregion

		#region -----------Tab0------------

		private void btn_home_main_Click(object sender, EventArgs e) {
			gpBox_GameSet.Enabled = false;
			gpBox_CtrlSet.Enabled = false;
			gpBox_AwardSet.Enabled = false;
			btn_Main.Enabled = false;

			if (m_btnMainIsStart) {
				listBox_Log.Items.Clear();

				if (!m_helper.Start()) {
					Log(Strings.Main.Main_Log_CanNotStartWork);
					return;
				}
				timer_main.Enabled = true;
			}
			else {
				m_helper.AskForStop();
			}
		}

		private void radioBtn_home_game_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetSetting(HelperSet.Cha_PlayNew, radioBtn_GameNew.Checked ? 1 : 0);
			Settings.Main.Default.Game_ForNew = radioBtn_GameNew.Checked;
			/*if (radioBtn_home_gameNew.Checked) {
				radioBtn_home_addPlay.Enabled = true;
			}
			else {
				if (radioBtn_home_addPlay.Checked)
					radioBtn_home_addIgnore.Checked = true;
				radioBtn_home_addPlay.Enabled = false;
			}*/
		}

		private void radioBtn_home_ctrl_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetSetting(HelperSet.Ctrl_MouseInput, radioBtn_CtrlInput.Checked ? 1 : 0);
			Settings.Main.Default.Ctrl_ForMouse = radioBtn_CtrlInput.Checked;
		}

		private void radioBtn_home_add_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetSetting(HelperSet.Cha_CheckAdd, radioBtn_AwardNo.Checked ? 0 : 1);
			m_helper.SetSetting(HelperSet.Cha_PlayAdd, radioBtn_AwardPlay.Checked ? 1 : 0);
			if (radioBtn_AwardNo.Checked) {
				Settings.Main.Default.Cha_Add = 0;
			}
			else if (radioBtn_AwardPlay.Checked) {
				Settings.Main.Default.Cha_Add = 1;
			}
			else {
				Settings.Main.Default.Cha_Add = 2;
			}
		}

		#endregion

		#region -----------Tab1------------

		private void checkBox_settings_showCV_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetSetting(HelperSet.Ctrl_ShowCapture, chkBox_SetShow.Checked ? 1 : 0);
			Settings.Main.Default.ShowCV = chkBox_SetShow.Checked;
		}

		private void checkBox_settings_hideToIcon_CheckedChanged(object sender, EventArgs e) {
			Settings.Main.Default.HideToIcon = chkBox_SetHideToTray.Checked;
		}

		private void checkBox_settings_useNotify_CheckedChanged(object sender, EventArgs e) {
			Settings.Main.Default.UseNotify = chkBox_SetNotify.Checked;
		}
		private void checkBox_settings_preventFromSleeping_CheckedChanged(object sender, EventArgs e) {
			if (chkBox_SetAwake.Checked) {
				Settings.Main.Default.PreventSleep = true;
				chkBox_SetScreenOn.Enabled = true;
				m_helper.SetSetting(HelperSet.Ctrl_PreventFromSleep, 1);
			}
			else {
				Settings.Main.Default.PreventSleep = false;
				chkBox_SetScreenOn.Checked = false;
				chkBox_SetScreenOn.Enabled = false;
				m_helper.SetSetting(HelperSet.Ctrl_PreventFromSleep, 0);
			}
		}

		private void checkBox_settings_keepDisplay_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetSetting(
				HelperSet.Ctrl_KeepDisplay,
				chkBox_SetScreenOn.Checked ? 1 : 0
			);
			Settings.Main.Default.KeepDisplay = chkBox_SetScreenOn.Checked;
		}

		private void checkBox_settings_disableClose_CheckedChanged(object sender, EventArgs e) {
			SystemThings.SetCloseEnabled(Handle, !chkBox_SetDisableClose.Checked);
			Settings.Main.Default.DisableClose = chkBox_SetDisableClose.Checked;
		}

		private void trackBar_transparant_ValueChanged(object sender, EventArgs e) {
			Opacity = 1.0 - tkBar_Trans.Value / 100.0;
			Settings.Main.Default.Transparant = tkBar_Trans.Value;
			label_TransValue.Text = tkBar_Trans.Value.ToString() + "%";
		}
		private void label_transp_value_SizeChanged(object sender, EventArgs e) {
			var newSize = label_TransValue.Size;
			var loc = label_TransValue.Location;
			loc.X += m_label_transp_value_size.Width - newSize.Width;
			label_TransValue.Location = loc;
			m_label_transp_value_size = newSize;
		}

		#endregion

		#region -----------Others----------

		private void notifyIcon_main_MouseClick(object sender, MouseEventArgs e) {
			switch (e.Button) {
			case MouseButtons.Left:
				Show();
				WindowState = FormWindowState.Normal;
				Activate();
				break;
			case MouseButtons.Right:
				notifyIcon_main.ContextMenuStrip?.Show();
				break;
			}
		}

		private void ctxtMenu_notifyR_exit_Click(object sender, EventArgs e) {
			Close();
		}

		private void Timer_main_Tick(object sender, EventArgs e) {
			ReturnMessage m;
			while ((m = m_helper.GetMessage()) != ReturnMessage.None)
				switch (m) {
				case ReturnMessage.CMD_EmptyLine:
					Log();
					break;
				case ReturnMessage.CMD_Stopped:
					Log(Strings.Main.Main_Log_WorkStopped);
					gpBox_GameSet.Enabled = true;
					gpBox_CtrlSet.Enabled = true;
					gpBox_AwardSet.Enabled = true;
					timer_main.Enabled = false;
					break;
				case ReturnMessage.CMD_BtnToStop:
					btn_Main.Text = Strings.Main.Main_Btn_Stop;
					btn_Main.Enabled = true;
					m_btnMainIsStart = false;
					break;
				case ReturnMessage.CMD_BtnToStart:
					btn_Main.Text = Strings.Main.Main_Btn_Start;
					btn_Main.Enabled = true;
					m_btnMainIsStart = true;
					break;

				case ReturnMessage.LOG_StartError_Running:
					Log(Strings.Main.Main_Log_WorkAlreadyRunning);
					break;
				case ReturnMessage.LOG_Stopping:
					Log(Strings.Main.Main_Log_WorkStopping);
					break;
				case ReturnMessage.LOG_WorkError_NoWnd:
					Log(Strings.Main.Main_Log_CanNotFindWnd);
					break;
				case ReturnMessage.LOG_WorkError_FailedCapture:
					Log(Strings.Main.Main_Log_CanNotCapture);
					break;
				case ReturnMessage.LOG_WorkError_Exception:
					Log();
					Log(Strings.Main.Main_Log_ExceptionInWork);
					if (Settings.Main.Default.UseNotify)
						notifyIcon_main.ShowBalloonTip(
							Settings.Main.Default.NotifyTime,
							Strings.Main.Main_Log_WorkError,
							Strings.Main.Main_Log_ExceptionInWork,
							ToolTipIcon.Error
						);
					break;

				case ReturnMessage.LOG_TaskStop:
					Log(Strings.Main.Log_Task_Stop);
					break;
				case ReturnMessage.LOG_TaskError_Exception:
					Log(Strings.Main.Log_Task_Exception);
					if (Settings.Main.Default.UseNotify)
						notifyIcon_main.ShowBalloonTip(
							Settings.Main.Default.NotifyTime,
							Strings.Main.Main_Log_WorkError,
							Strings.Main.Log_Task_Exception,
							ToolTipIcon.Error
						);
					break;
				case ReturnMessage.LOG_TaskError:
					Log();
					m = m_helper.GetMessage();
					string text = "null";
					switch (m) {
					case ReturnMessage.STR_Task_Challenge_NoNew:
						text = Strings.Main.Log_Task_Challenge_NoNew;
						break;
					case ReturnMessage.STR_Task_Challenge_NoLast:
						text = Strings.Main.Log_Task_Challenge_NoLast;
						break;
					case ReturnMessage.STR_Task_Challenge_NoEnter:
						text = Strings.Main.Log_Task_Challenge_NoEnter;
						break;
					case ReturnMessage.STR_Task_Challenge_LowFP:
						text = Strings.Main.Log_Task_Challenge_LowFP;
						break;
					case ReturnMessage.STR_Task_Challenge_NoStart:
						text = Strings.Main.Log_Task_Challenge_NoStart;
						break;
					case ReturnMessage.STR_Task_Challenge_TimeOut:
						text = Strings.Main.Log_Task_Challenge_TimeOut;
						break;
					case ReturnMessage.STR_Task_Challenge_NoEnd:
						text = Strings.Main.Log_Task_Challenge_NoEnd;
						break;
					case ReturnMessage.STR_Task_Challenge_NoOver:
						text = Strings.Main.Log_Task_Challenge_NoOver;
						break;
					case ReturnMessage.STR_Task_Challenge_AddNotSup:
						text = Strings.Main.STR_Task_Challenge_AddNotSup;
						break;
					case ReturnMessage.STR_Task_Challenge_IgnoreAddFailed:
						text = Strings.Main.STR_Task_Challenge_IgnoreAddFailed;
						break;
					case ReturnMessage.STR_Task_Challenge_OpenAddFailed:
						text = Strings.Main.STR_Task_Challenge_OpenAddFailed;
						break;
					default:
						text = string.Format(Strings.Main.STR_UNKNOWN, m.ToString());
						break;
					}
					Log(Strings.Main.Main_Log_TaskError + ": " + text);
					if (Settings.Main.Default.UseNotify)
						notifyIcon_main.ShowBalloonTip(
							Settings.Main.Default.NotifyTime,
							Strings.Main.Main_Log_TaskError,
							text,
							ToolTipIcon.Info
						);
					break;

				case ReturnMessage.LOG_Challenge_Start:
					Log(Strings.Main.Main_Log_Challenge_Start);
					break;
				case ReturnMessage.LOG_Challenge_BeginNum: // 挑战赛开始（下跟次数！）
					Log(string.Format(Strings.Main.Main_Log_Challenge_BeginNum, m_helper.GetCode()));
					break;
				case ReturnMessage.LOG_Challenge_EnterLast:
					Log(Strings.Main.Main_Log_Challenge_EnterLast);
					break;
				case ReturnMessage.LOG_Challenge_EnterNew:
					Log(Strings.Main.Main_Log_Challenge_EnterNew);
					break;
				case ReturnMessage.LOG_Challenge_Play:
					Log(Strings.Main.Main_Log_Challenge_Play);
					break;
				case ReturnMessage.LOG_Challenge_WaitForEnd:
					Log(Strings.Main.Main_Log_Challenge_WaitForEnd);
					break;
				case ReturnMessage.LOG_Challenge_End:
					Log(Strings.Main.Main_Log_Challenge_End);
					break;
				case ReturnMessage.LOG_Challenge_Quiting:
					Log(Strings.Main.Main_Log_Challenge_Quiting);
					break;
				case ReturnMessage.LOG_Challenge_Over:
					Log(Strings.Main.Log_Challenge_Over);
					break;
				case ReturnMessage.LOG_Challenge_Exit:
					Log(Strings.Main.Log_Challenge_Exit);
					break;
				case ReturnMessage.LOG_Challenge_EnterAdd:
					Log(Strings.Main.LOG_Challenge_EnterAdd);
					break;
				case ReturnMessage.LOG_Challenge_IgnoredAdd:
					Log(Strings.Main.LOG_Challenge_IgnoredAdd);
					break;
				case ReturnMessage.LOG_Challenge_NotFindAdd:
					Log(Strings.Main.LOG_Challenge_NotFindAdd);
					break;
				case ReturnMessage.LOG_Challenge_FindAdd:
					Log(Strings.Main.LOG_Challenge_FindAdd);
					break;
				case ReturnMessage.LOG_Challenge_OpenedAdd:
					Log(Strings.Main.LOG_Challenge_OpenedAdd);
					break;
				default:
					Log(string.Format(Strings.Main.Log_UNKNOWN, m.ToString()));
					break;

				}
			return;
		}

		#endregion

		#endregion

	}
}
