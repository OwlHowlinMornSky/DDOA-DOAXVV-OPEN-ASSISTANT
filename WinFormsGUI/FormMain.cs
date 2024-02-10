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
			bool scroll = listBox_home.TopIndex == listBox_home.Items.Count - (int)(listBox_home.Height / listBox_home.ItemHeight);
			listBox_home.Items.Add(msg);
			if (scroll)
				listBox_home.TopIndex = listBox_home.Items.Count - (int)(listBox_home.Height / listBox_home.ItemHeight);
		}

		public void Log() {
			bool scroll = listBox_home.TopIndex == listBox_home.Items.Count - (int)(listBox_home.Height / listBox_home.ItemHeight);
			listBox_home.Items.Add("");
			if (scroll)
				listBox_home.TopIndex = listBox_home.Items.Count - (int)(listBox_home.Height / listBox_home.ItemHeight);
		}

		#endregion

		#region ==========Events===========

		#region ---------MainForm----------

		public void FormMain_Load(object sender, EventArgs e) {
			notifyIcon_main.Text = Text;
			btn_home_main.Text = Strings.Main.Main_Btn_Start;

#if DEBUG
			Settings.Main.Default.ShowCV = true;
#endif

			radioBtn_home_gameNew.Checked = Settings.Main.Default.Game_ForNew;
			radioBtn_home_ctrlInput.Checked = Settings.Main.Default.Ctrl_ForMouse;

			checkBox_settings_showCV.Checked = Settings.Main.Default.ShowCV;
			checkBox_settings_hideToIcon.Checked = Settings.Main.Default.HideToIcon;
			checkBox_settings_useNotify.Checked = Settings.Main.Default.UseNotify;
			if (Settings.Main.Default.PreventSleep) {
				checkBox_settings_preventFromSleeping.Checked = true;
				checkBox_settings_keepDisplay.Enabled = true;
				checkBox_settings_keepDisplay.Checked = Settings.Main.Default.KeepDisplay;
			}
			else {
				checkBox_settings_preventFromSleeping.Checked = false;
				checkBox_settings_keepDisplay.Enabled = false;
				checkBox_settings_keepDisplay.Checked = false;
			}

			checkBox_settings_disableClose.Checked = Settings.Main.Default.DisableClose;

			trackBar_transparant.Value = Settings.Main.Default.Transparant;
			m_label_transp_value_size = label_transp_value.Size;
			label_transp_value.Text = trackBar_transparant.Value.ToString() + "%";
		}

		private void FormMain_Deactivate(object sender, EventArgs e) {
			if (WindowState == FormWindowState.Minimized &&
				Settings.Main.Default.HideToIcon) {
				Hide();
			}
		}

		private void FormMain_FormClosing(object sender, FormClosingEventArgs e) {
			m_helper.AskForStop();

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
			gpBox_home_gameSet.Enabled = false;
			gpBox_home_ctrlSet.Enabled = false;
			btn_home_main.Enabled = false;

			if (m_btnMainIsStart) {
				listBox_home.Items.Clear();

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
			m_helper.SetSetting(HelperSet.Cha_PlayNew, radioBtn_home_gameNew.Checked ? 1 : 0);
			Settings.Main.Default.Game_ForNew = radioBtn_home_gameNew.Checked;
		}

		private void radioBtn_home_ctrl_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetSetting(HelperSet.Ctrl_MouseInput, radioBtn_home_ctrlInput.Checked ? 1 : 0);
			Settings.Main.Default.Ctrl_ForMouse = radioBtn_home_ctrlInput.Checked;
		}

		#endregion

		#region -----------Tab1------------

		private void checkBox_settings_showCV_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetSetting(HelperSet.Ctrl_ShowCapture, checkBox_settings_showCV.Checked ? 1 : 0);
			Settings.Main.Default.ShowCV = checkBox_settings_showCV.Checked;
		}

		private void checkBox_settings_hideToIcon_CheckedChanged(object sender, EventArgs e) {
			Settings.Main.Default.HideToIcon = checkBox_settings_hideToIcon.Checked;
		}

		private void checkBox_settings_useNotify_CheckedChanged(object sender, EventArgs e) {
			Settings.Main.Default.UseNotify = checkBox_settings_useNotify.Checked;
		}
		private void checkBox_settings_preventFromSleeping_CheckedChanged(object sender, EventArgs e) {
			if (checkBox_settings_preventFromSleeping.Checked) {
				Settings.Main.Default.PreventSleep = true;
				checkBox_settings_keepDisplay.Enabled = true;
				m_helper.SetSetting(HelperSet.Ctrl_PreventFromSleep, 1);
			}
			else {
				Settings.Main.Default.PreventSleep = false;
				checkBox_settings_keepDisplay.Checked = false;
				checkBox_settings_keepDisplay.Enabled = false;
				m_helper.SetSetting(HelperSet.Ctrl_PreventFromSleep, 0);
			}
		}

		private void checkBox_settings_keepDisplay_CheckedChanged(object sender, EventArgs e) {
			m_helper.SetSetting(
				HelperSet.Ctrl_KeepDisplay,
				checkBox_settings_keepDisplay.Checked ? 1 : 0
			);
			Settings.Main.Default.KeepDisplay = checkBox_settings_keepDisplay.Checked;
		}

		private void checkBox_settings_disableClose_CheckedChanged(object sender, EventArgs e) {
			SystemThings.SetCloseEnabled(Handle, !checkBox_settings_disableClose.Checked);
			Settings.Main.Default.DisableClose = checkBox_settings_disableClose.Checked;
		}

		private void trackBar_transparant_ValueChanged(object sender, EventArgs e) {
			Opacity = 1.0 - trackBar_transparant.Value / 100.0;
			Settings.Main.Default.Transparant = trackBar_transparant.Value;
			label_transp_value.Text = trackBar_transparant.Value.ToString() + "%";
		}
		private void label_transp_value_SizeChanged(object sender, EventArgs e) {
			var newSize = label_transp_value.Size;
			var loc = label_transp_value.Location;
			loc.X += m_label_transp_value_size.Width - newSize.Width;
			label_transp_value.Location = loc;
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
				case ReturnMessage.CMD_Stopped:
					Log(Strings.Main.Main_Log_WorkStopped);
					gpBox_home_gameSet.Enabled = true;
					gpBox_home_ctrlSet.Enabled = true;
					timer_main.Enabled = false;
					break;
				case ReturnMessage.CMD_BtnToStop:
					btn_home_main.Text = Strings.Main.Main_Btn_Stop;
					btn_home_main.Enabled = true;
					m_btnMainIsStart = false;
					break;
				case ReturnMessage.CMD_BtnToStart:
					btn_home_main.Text = Strings.Main.Main_Btn_Start;
					btn_home_main.Enabled = true;
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

				}
			return;
		}

		#endregion

		#endregion

	}
}
