using Wrapper;

namespace WinFormsGUI {
	public partial class FormMain : Form {

		#region ==========Members==========

		private HelperWrapper m_helper = new();
		private bool m_btnMainIsStart = true;

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
			btn_home_main.Text = Strings.str.Main_Btn_Start;


#if DEBUG
			Settings.main.Default.ShowCV = true;
#endif

			radioBtn_home_gameNew.Checked = Settings.main.Default.Game_ForNew;
			radioBtn_home_ctrlInput.Checked = Settings.main.Default.Ctrl_ForMouse;

			checkBox_settings_showCV.Checked = Settings.main.Default.ShowCV;
			checkBox_settings_hideToIcon.Checked = Settings.main.Default.HideToIcon;
			checkBox_settings_useNotify.Checked = Settings.main.Default.UseNotify;
		}

		private void FormMain_Deactivate(object sender, EventArgs e) {
			if (WindowState == FormWindowState.Minimized &&
				Settings.main.Default.HideToIcon) {
				Hide();
			}
		}

		private void FormMain_FormClosing(object sender, FormClosingEventArgs e) {
			m_helper.askForStop();

			Settings.main.Default.Save();

			while (m_helper.isRunning()) {
				Thread.Sleep(30);
			}
		}

		private void FormMain_FormClosed(object sender, FormClosedEventArgs e) {
			m_helper.drop();
		}

		#endregion

		#region -----------Tab0------------

		private void btn_home_main_Click(object sender, EventArgs e) {
			gpBox_home_gameSet.Enabled = false;
			gpBox_home_ctrlSet.Enabled = false;
			btn_home_main.Enabled = false;

			if (m_btnMainIsStart) {
				listBox_home.Items.Clear();

				if (!m_helper.start()) {
					Log(Strings.str.Main_Log_CanNotStartWork);
					return;
				}
				timer_main.Enabled = true;
			}
			else {
				m_helper.askForStop();
			}
		}

		private void radioBtn_home_game_CheckedChanged(object sender, EventArgs e) {
			m_helper.set(HelprSet.Cha_New, radioBtn_home_gameNew.Checked ? 1 : 0);
			Settings.main.Default.Game_ForNew = radioBtn_home_gameNew.Checked;
		}

		private void radioBtn_home_ctrl_CheckedChanged(object sender, EventArgs e) {
			m_helper.set(HelprSet.Ctrl_MouseInput, radioBtn_home_ctrlInput.Checked ? 1 : 0);
			Settings.main.Default.Ctrl_ForMouse = radioBtn_home_ctrlInput.Checked;
		}

		#endregion

		#region -----------Tab1------------

		private void checkBox_settings_showCV_CheckedChanged(object sender, EventArgs e) {
			m_helper.set(HelprSet.ShowCV, checkBox_settings_showCV.Checked ? 1 : 0);
		}

		private void checkBox_settings_hideToIcon_CheckedChanged(object sender, EventArgs e) {
			Settings.main.Default.HideToIcon = checkBox_settings_hideToIcon.Checked;
		}

		private void checkBox_settings_useNotify_CheckedChanged(object sender, EventArgs e) {
			Settings.main.Default.UseNotify = checkBox_settings_useNotify.Checked;
		}

		#endregion

		private void notifyIcon_main_MouseClick(object sender, MouseEventArgs e) {
			switch (e.Button) {
			case MouseButtons.Left:
				Show();
				WindowState = FormWindowState.Normal;
				Activate();
				break;
			case MouseButtons.Right:
				notifyIcon_main.ContextMenuStrip.Show();
				break;
			}
		}

		private void ctxtMenu_notifyR_exit_Click(object sender, EventArgs e) {
			Close();
		}

		private void timer_main_Tick(object sender, EventArgs e) {
			ReturnMessage m = m_helper.msgPop();
			switch (m) {
			case ReturnMessage.Stopped:
				Log(Strings.str.Main_Log_WorkStopped);
				gpBox_home_gameSet.Enabled = true;
				gpBox_home_ctrlSet.Enabled = true;
				timer_main.Enabled = false;
				break;
			case ReturnMessage.BtnToStop:
				btn_home_main.Text = Strings.str.Main_Btn_Stop;
				btn_home_main.Enabled = true;
				m_btnMainIsStart = false;
				break;
			case ReturnMessage.BtnToStart:
				btn_home_main.Text = Strings.str.Main_Btn_Start;
				btn_home_main.Enabled = true;
				m_btnMainIsStart = true;
				break;
			case ReturnMessage.Log_ErrorIsRunning:
				Log(Strings.str.Main_Log_WorkAlreadyRunning);
				break;
			case ReturnMessage.Log_Stopping:
				Log(Strings.str.Main_Log_WorkStopping);
				break;
			case ReturnMessage.Log_ErrorNotFindWnd:
				Log(Strings.str.Main_Log_CanNotFindWnd);
				break;
			case ReturnMessage.Log_ErrorCannotCapture:
				Log(Strings.str.Main_Log_CanNotCapture);
				break;
			case ReturnMessage.Log_ErrorInWork:
				Log();
				Log(Strings.str.Main_Log_ExceptionInWork);
				if (Settings.main.Default.UseNotify)
					notifyIcon_main.ShowBalloonTip(
						Settings.main.Default.NotifyTime,
						Strings.str.Main_Log_WorkError,
						Strings.str.Main_Log_ExceptionInWork,
						ToolTipIcon.Error
					);
				break;
			case ReturnMessage.Log_ErrorInTask:
				Log();
				m = m_helper.msgPop();
				string text = "null";
				switch (m) {
				case ReturnMessage.Log_Task_Challenge_NoNew:
					text = Strings.str.Log_Task_Challenge_NoNew;
					break;
				case ReturnMessage.Log_Task_Challenge_NoLast:
					text = Strings.str.Log_Task_Challenge_NoLast;
					break;
				case ReturnMessage.Log_Task_Challenge_NoEnter:
					text = Strings.str.Log_Task_Challenge_NoEnter;
					break;
				case ReturnMessage.Log_Task_Challenge_LowFP:
					text = Strings.str.Log_Task_Challenge_LowFP;
					break;
				case ReturnMessage.Log_Task_Challenge_NoStart:
					text = Strings.str.Log_Task_Challenge_NoStart;
					break;
				case ReturnMessage.Log_Task_Challenge_TimeOut:
					text = Strings.str.Log_Task_Challenge_TimeOut;
					break;
				case ReturnMessage.Log_Task_Challenge_NoEnd:
					text = Strings.str.Log_Task_Challenge_NoEnd;
					break;
				case ReturnMessage.Log_Task_Challenge_NoOver:
					text = Strings.str.Log_Task_Challenge_NoOver;
					break;
				}
				Log(Strings.str.Main_Log_TaskError + ": " + text);
				if (Settings.main.Default.UseNotify)
					notifyIcon_main.ShowBalloonTip(
						Settings.main.Default.NotifyTime,
						Strings.str.Main_Log_TaskError,
						text,
						ToolTipIcon.Info
					);
				break;

			case ReturnMessage.Log_Challenge_Start:
				Log(Strings.str.Main_Log_Challenge_Start);
				break;
			case ReturnMessage.Log_Challenge_BeginNum: // 挑战赛开始（下跟次数！）
				Log(string.Format(Strings.str.Main_Log_Challenge_BeginNum, m_helper.codePop()));
				break;
			case ReturnMessage.Log_Challenge_EnterLast:
				Log(Strings.str.Main_Log_Challenge_EnterLast);
				break;
			case ReturnMessage.Log_Challenge_EnterNew:
				Log(Strings.str.Main_Log_Challenge_EnterNew);
				break;
			case ReturnMessage.Log_Challenge_Play:
				Log(Strings.str.Main_Log_Challenge_Play);
				break;
			case ReturnMessage.Log_Challenge_WaitForEnd:
				Log(Strings.str.Main_Log_Challenge_WaitForEnd);
				break;
			case ReturnMessage.Log_Challenge_End:
				Log(Strings.str.Main_Log_Challenge_End);
				break;
			case ReturnMessage.Log_Challenge_Quiting:
				Log(Strings.str.Main_Log_Challenge_Quiting);
				break;
			case ReturnMessage.Log_Challenge_Over:
				Log(Strings.str.Log_Challenge_Over);
				break;
			case ReturnMessage.Log_Challenge_Exit:
				Log(Strings.str.Log_Challenge_Exit);
				break;

			case ReturnMessage.Log_Task_Stop:
				Log(Strings.str.Log_Task_Stop);
				break;
			case ReturnMessage.Log_Task_Exception:
				Log(Strings.str.Log_Task_Exception);
				if (Settings.main.Default.UseNotify)
					notifyIcon_main.ShowBalloonTip(
						Settings.main.Default.NotifyTime,
						Strings.str.Main_Log_WorkError,
						Strings.str.Log_Task_Exception,
						ToolTipIcon.Error
					);
				break;

			}
			return;
		}

		#endregion

	}
}
